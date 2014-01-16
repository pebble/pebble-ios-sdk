//
//  NSURLConnectionVCR.m
//
//  Created by Martijn Thé on 19-02-12.
//  Copyright (c) 2012 martijnthe.nl All rights reserved.
//

#import "NSURLConnectionVCR.h"
#import <CommonCrypto/CommonDigest.h>
#import <objc/runtime.h>
#import <objc/objc.h>

#ifdef __IPHONE_6_0
#define CAST_TO_BLOCK id
#else
#define CAST_TO_BLOCK __bridge void *
#endif

NSString* NSURLConnectionVCRErrorDomain = @"NSURLConnectionVCRErrorDomain";
struct objc_class;
__strong static NSString* casettesPath;
static IMP *origImps;
static const unsigned char swizzleCount;
static SEL swizzleSelectors[];
static id poseImplementationBlockForSelector(SEL sel);

#pragma mark - Private Interfaces

@interface VCRCache : NSObject <NSCoding>
@property (nonatomic, readwrite, strong) NSURLResponse* response;
@property (nonatomic, readwrite, strong) NSData* responseBody;
+ (VCRCache*)loadCacheForRequest:(NSURLRequest*)request;
+ (VCRCache*)storeResponse:(NSURLResponse*)response withResponseBody:(NSData*)data forRequest:(NSURLRequest*)request success:(out BOOL*)outSuccess;
+ (BOOL)deleteCacheForRequest:(NSURLRequest*)request error:(NSError *__autoreleasing *)error;
+ (BOOL)hasCacheForRequest:(NSURLRequest*)request;
@end

@class VCRConnectionDelegate;

@interface NSURLConnectionVCR ()
@property (nonatomic, retain, readwrite) NSURLConnection* connection;
@property (nonatomic, retain, readwrite) VCRConnectionDelegate* delegate;
@end

@interface VCRConnectionDelegate : NSObject
@property (nonatomic, retain, readwrite) id realDelegate;
@property (nonatomic, retain, readwrite) NSURLConnectionVCR *vcr;
@property (nonatomic, retain, readwrite) NSURLRequest* request;
@property (nonatomic, retain, readonly) NSURLResponse* response;
@property (nonatomic, retain, readonly) NSData* responseData;
@end

@interface VCRCache (Private)
+ (NSString*)hashForRequest:(NSURLRequest*)request;
+ (NSString*)filePathForRequest:(NSURLRequest*)request;
@end


#pragma mark - NSURLConnectionVCR Implementation

@implementation NSURLConnectionVCR {
    NSURLConnection* connection;
    VCRConnectionDelegate* delegate;
}

#pragma mark General stuff
@synthesize connection;
@synthesize delegate;

- (void)dealloc {
    connection = nil;
    delegate = nil;
}

+ (BOOL)setPath:(NSString*)path error:(NSError *__autoreleasing *)error {
    if (path != nil) {
        NSFileManager* fm = [NSFileManager defaultManager];
        BOOL isDirectory;
        BOOL fileExists = [fm fileExistsAtPath:path isDirectory:&isDirectory];
        if (fileExists == NO) {
            NSError* createDirError = nil;
            BOOL didCreateDir = [fm createDirectoryAtPath:path withIntermediateDirectories:YES attributes:nil error:&createDirError];
            if (didCreateDir == NO) {
                if (error) {
                    NSDictionary* userInfo = [NSDictionary dictionaryWithObjectsAndKeys:createDirError, NSUnderlyingErrorKey, nil];
                    *error = [NSError errorWithDomain:NSURLConnectionVCRErrorDomain code:NSURLConnectionVCRErrorCouldNotCreateDirectory userInfo:userInfo];
                }
                return NO;
            }
        } else if (isDirectory == NO) {
            if (error) {
                *error = [NSError errorWithDomain:NSURLConnectionVCRErrorDomain code:NSURLConnectionVCRErrorPathIsNotADirectory userInfo:nil];
            }
            return NO;
        }
    }
    casettesPath = path;
    return YES;
}

+ (NSString*)path {
    return casettesPath;
}

+ (BOOL)deleteCacheForRequest:(NSURLRequest*)request error:(NSError *__autoreleasing *)error {
    return [VCRCache deleteCacheForRequest:request error:error];
}

+ (BOOL)hasCacheForRequest:(NSURLRequest*)request {
    return [VCRCache hasCacheForRequest:request];
}

+ (BOOL)startVCRWithPath:(NSString*)path error:(NSError *__autoreleasing *)error {
    if ([self isVCRStarted]) {
        if (error) {
            *error = [NSError errorWithDomain:NSURLConnectionVCRErrorDomain code:NSURLConnectionVCRErrorAlreadyStarted userInfo:nil];
        }
        return NO;
    } else {
        if ([self setPath:path error:error] == NO) {
            // We're not wrapping the error, would be overkill.
            return NO;
        } else {
            // Swizzle the class methods we want to intercept (instance methods of the metaClasses):
            Class theClass = objc_getMetaClass("NSURLConnection");
            Method origMethod;
            IMP poseImplementation;
            SEL theSelector;
            origImps = (IMP*)malloc(swizzleCount * sizeof(IMP));
            
            for (unsigned char i = 0; i < swizzleCount; ++i) {
                theSelector = swizzleSelectors[i];
                origMethod = class_getInstanceMethod(theClass, theSelector);
                origImps[i] = method_getImplementation(origMethod);

                // Depending on your SDK, you might need a bridged cast here:
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
                poseImplementation = imp_implementationWithBlock((CAST_TO_BLOCK)poseImplementationBlockForSelector(theSelector));
#else
                poseImplementation = imp_implementationWithBlock(poseImplementationBlockForSelector(theSelector));
#endif
                
                class_replaceMethod(theClass, theSelector, poseImplementation, method_getTypeEncoding(origMethod));
            }
            return YES;
        }
    }
}

+ (BOOL)stopVCRWithError:(NSError**)error {
    if ([self isVCRStarted] == NO) {
        if (error) {
            *error = [NSError errorWithDomain:NSURLConnectionVCRErrorDomain code:NSURLConnectionVCRErrorAlreadyStopped userInfo:nil];
        }
        return NO;
    } else {
        Method theMethod;
        SEL theSelector;
        Class theClass = objc_getMetaClass("NSURLConnection");
        IMP previousImp;

        for (unsigned char i = 0; i < swizzleCount; ++i) {
            theSelector = swizzleSelectors[i];
            theMethod = class_getInstanceMethod(theClass, theSelector);
            previousImp = class_replaceMethod(theClass, theSelector, origImps[i], method_getTypeEncoding(theMethod));
            imp_removeBlock(previousImp);
            origImps[i] = NULL;
        }
        free(origImps);
        origImps = NULL;
        casettesPath = nil;
        return YES;
    }
}

+ (BOOL)isVCRStarted {
    return (origImps != NULL);
}

- (void)sendVCRCachedResultFor:(NSURLRequest *)request to:(id)realDelegate {
  VCRCache* cache = [VCRCache loadCacheForRequest:request];

  NSOperationQueue* queue = [NSOperationQueue currentQueue];
  if (!queue) {
    queue = [[NSOperationQueue alloc] init];
  }
  [queue addOperationWithBlock:^{
    // yes, we want self and realDelegate to be retained by this block...
    // it's perhaps a bit unnatural to call these delegate methods right after each other, but let's see if it is sufficient.
    [realDelegate connection:(NSURLConnection*)self didReceiveResponse:cache.response];
    NSUInteger loc = 0;
    NSUInteger len = 256u * 1024u;
    NSUInteger totalLen = [cache.responseBody length];
    do {
      if (len + loc > totalLen) {
        len = totalLen - loc;
      }
      NSData* subData = [cache.responseBody subdataWithRange:NSMakeRange(loc, len)];
      [realDelegate connection:(NSURLConnection*)self didReceiveData:subData];
      loc += len;
    } while (loc < totalLen);
    [realDelegate connectionDidFinishLoading:(NSURLConnection*)self];
  }];
}

#pragma mark Class posing / Swizzle bizz

static const unsigned char swizzleCount = 3;
static SEL swizzleSelectors[swizzleCount] = {NULL, NULL, NULL};

+ (void)initialize {
    @autoreleasepool {
      swizzleSelectors[0] = @selector(alloc);
      swizzleSelectors[1] = @selector(sendSynchronousRequest:returningResponse:error:);
      swizzleSelectors[2] = @selector(sendAsynchronousRequest:queue:completionHandler:);
    }
}

static IMP *origImps = NULL;

static id poseImplementationBlockForSelector(SEL sel) {
    if (sel == @selector(alloc)) {
        return (id)^(id _self) __attribute__((ns_returns_retained)) { /* the ns_returns_retained attribute is important here, because the +alloc method is expected to return +1 */
            NSURLConnectionVCR *vcr = [NSURLConnectionVCR alloc];
            // This call to the original +alloc IMP is wrapped in objc_retainedObject, because ARC gets confused otherwise...
            id connection = objc_retainedObject((__bridge objc_objectptr_t)origImps[0](_self, sel));
            vcr.connection = connection;
            return vcr;
        };
    } else if (sel == @selector(sendSynchronousRequest:returningResponse:error:)) {
        return (id)^(id _self, NSURLRequest* request, NSURLResponse *__autoreleasing *response, NSError *__autoreleasing *error) {
            VCRCache *cache = [VCRCache loadCacheForRequest:request];
            if (cache == nil) {
                __autoreleasing NSURLResponse *theResponse = nil;
                __autoreleasing NSError *theError = nil;
                BOOL success;
                NSData *theResponseBody = (NSData*)origImps[1](_self, sel, request, &theResponse, &theError);
                cache = [VCRCache storeResponse:theResponse withResponseBody:theResponseBody forRequest:request success:&success];
                if (error && theError) {
                    *error = theError;
                } else if (error && success == NO) { /* If the previous condition was true, this next condition is not very interesting any more, hence `else if`: */
                    *error = [NSError errorWithDomain:NSURLConnectionVCRErrorDomain code:NSURLConnectionVCRErrorStorageFailed userInfo:nil];
                }
            }
            if (response) {
                *response = cache.response;
            }
            return cache.responseBody;
        };
    } else if (sel == @selector(sendAsynchronousRequest:queue:completionHandler:)) {
        return (id)^(id _self, NSURLRequest *request, NSOperationQueue *queue, void (^handler)(NSURLResponse*, NSData*, NSError*) ) {
            __block VCRCache *cache = [VCRCache loadCacheForRequest:request];
            if (cache == nil) {
                origImps[2](_self, sel, request, queue, ^(NSURLResponse *response, NSData *data, NSError *error){
                    cache = [VCRCache storeResponse:response withResponseBody:data forRequest:request success:NULL];
                    handler(cache.response, cache.responseBody, error);
                });
            } else {
                handler(cache.response, cache.responseBody, nil);
            }
        };
    } else {
        return nil;
    }
}

- (BOOL)respondsToSelector:(SEL)aSelector {
    return [connection respondsToSelector:aSelector];
}

+ (BOOL)instancesRespondToSelector:(SEL)aSelector {
    return [NSURLConnection instancesRespondToSelector:aSelector];
}

- (id)forwardingTargetForSelector:(SEL)aSelector {
    return connection;
}

- (id)initWithRequest:(NSURLRequest *)request delegate:(id)realDelegate startImmediately:(BOOL)startImmediately {
    VCRCache* cache = [VCRCache loadCacheForRequest:request];
    if (cache && startImmediately) {
        [self sendVCRCachedResultFor:request to:realDelegate];
        return [self init];
    } else {
        // NSURLConnection retains its delegate until done loading --> VCRConnectionDelegate retains realDelegate, vcr, request until done loading
        delegate = [[VCRConnectionDelegate alloc] init];
        delegate.realDelegate = realDelegate;
        delegate.request = request;
        delegate.vcr = self;

        if (!cache) {
          if ([connection initWithRequest:request delegate:delegate startImmediately:startImmediately]) {};  // wrapped in if() to silence `Expression result unused` compiler warning
        }
        return [self init];
    }
}

- (id)initWithRequest:(NSURLRequest *)request delegate:(id)realDelegate {
    return [self initWithRequest:request delegate:delegate startImmediately:YES];
}

- (id)delegate {
    return [delegate realDelegate];
}

- (void)start {
  VCRCache* cache = [VCRCache loadCacheForRequest:delegate.request];
  if (cache) {
    [self sendVCRCachedResultFor:delegate.request to:delegate.realDelegate];
  } else {
    [connection start];
  }
}

@end

@protocol NSURLConnectionDataDelegate;
@protocol NSURLConnectionDownloadDelegate;

@implementation VCRConnectionDelegate {
    // Depending on your SDK, you might need one of these 2 lines:
    //__strong NSObject<NSURLConnectionDelegate, NSObject>* realDelegate;    
    __strong NSObject<NSURLConnectionDelegate, NSURLConnectionDataDelegate, NSURLConnectionDownloadDelegate, NSObject>* realDelegate;    
    NSURLConnectionVCR* vcr;
    NSURLRequest* request;
    NSURLResponse* response;
    NSMutableData* responseData;
}
@synthesize realDelegate;
@synthesize vcr;
@synthesize response;
@synthesize responseData;
@synthesize request;

- (BOOL)respondsToSelector:(SEL)aSelector {
    return [realDelegate respondsToSelector:aSelector];
}

+ (BOOL)instancesRespondToSelector:(SEL)aSelector {
//    return [theClass instancesRespondToSelector:aSelector];
    return YES;
}

- (id)forwardingTargetForSelector:(SEL)aSelector {
    return realDelegate;
}

- (void)releaseChildren {
    realDelegate = nil;
    vcr.connection = nil;
    vcr = nil;
    request = nil;
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)theError {
    [realDelegate connection:connection didFailWithError:theError];
    [self releaseChildren];
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)theResponse {
    response = theResponse;
    [realDelegate connection:connection didReceiveResponse:theResponse];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    if (responseData == nil) {
        long long expectedContentLength = [response expectedContentLength];
        responseData = [NSMutableData dataWithCapacity:expectedContentLength];
    }
    [responseData appendData:data];
    [realDelegate connection:connection didReceiveData:data];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
    [VCRCache storeResponse:response withResponseBody:responseData forRequest:request success:NULL];
    [realDelegate connectionDidFinishLoading:connection];
    [self releaseChildren];
}

- (void)connectionDidFinishDownloading:(NSURLConnection *)connection destinationURL:(NSURL *) destinationURL {
    [VCRCache storeResponse:response withResponseBody:[NSData dataWithContentsOfURL:destinationURL] forRequest:request success:NULL];
    [realDelegate connectionDidFinishDownloading:connection destinationURL:destinationURL];
    [self releaseChildren];
}

@end


#pragma mark - VCRCache (Tape) Implementation

@implementation VCRCache
@synthesize response;
@synthesize responseBody;

+ (VCRCache*)loadCacheForRequest:(NSURLRequest*)request {
    if (request == nil) {
        return nil;
    }
    VCRCache* cache = [NSKeyedUnarchiver unarchiveObjectWithFile:[self filePathForRequest:request]];
    return cache;
}

+ (VCRCache*)storeResponse:(NSURLResponse*)response withResponseBody:(NSData*)data forRequest:(NSURLRequest*)request success:(out BOOL*)outSuccess {
    BOOL success;
    VCRCache* cache = nil;
    if (request == nil) {
        success = NO;
    } else {
        cache = [[VCRCache alloc] init];
        cache.response = response;
        cache.responseBody = data;
        NSString* filePath = [self filePathForRequest:request];
        success = [NSKeyedArchiver archiveRootObject:cache toFile:filePath];
//        if (success) {
//            // Trigger Spotlight to create metadata, so one can see what request URL the cache file belongs to
//            MDItemCreate(NULL, (__bridge CFStringRef)filePath);
//        }
    }
    if (outSuccess) {
        *outSuccess = success;
    }
    return cache;
}

+ (BOOL)deleteCacheForRequest:(NSURLRequest*)request error:(NSError *__autoreleasing *)error {
    NSString* filePath = [self filePathForRequest:request];
    NSFileManager* fm = [NSFileManager defaultManager];
    // We're not wrapping the error, would be overkill.
    return [fm removeItemAtPath:filePath error:error];
}

+ (BOOL)hasCacheForRequest:(NSURLRequest*)request {
    return [[NSFileManager defaultManager] fileExistsAtPath:[VCRCache filePathForRequest:request]];
}

- (id)initWithCoder:(NSCoder *)coder {
    if (self) {
        self.response = [coder decodeObjectForKey:@"response"];
        self.responseBody = [coder decodeObjectForKey:@"responseBody"];
    }
    return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
    [aCoder encodeObject:response forKey:@"response"];
    [aCoder encodeObject:responseBody forKey:@"responseBody"];
}

@end


@implementation VCRCache (Private)

static CFStringRef SKUtilsCreateStringHexadecimalRepresentationOfBytes(const UInt8* bytes, CFIndex length) {
    UInt8 hexMap[] = "000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9FA0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBFC0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDFE0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";
    
    UInt8 *c = (UInt8 *)malloc(length * 2);
    UInt16 *ptr = (UInt16*) c;
    UInt16 *last = (UInt16*) (c + (length * 2));
    for (;;) {
        *ptr = ((UInt16*)hexMap)[*bytes];
        ++ptr;
        ++bytes;
        if (ptr == last) {
            return (__bridge_retained CFStringRef)[[NSString alloc] initWithBytesNoCopy:c length:length * 2 encoding:NSUTF8StringEncoding freeWhenDone:YES];
            
            // Not implemented in Cocotron:
            //            return CFStringCreateWithBytesNoCopy(NULL, c, length * 2, kCFStringEncodingUTF8, false, kCFAllocatorMalloc);
        }
    }
}

+ (NSString*)hashForRequest:(NSURLRequest*)request {
    NSData* data = [NSKeyedArchiver archivedDataWithRootObject:request];
    unsigned char md5[CC_MD5_DIGEST_LENGTH];
    CC_MD5([data bytes], (CC_LONG)[data length], md5);
    NSString* md5String = (__bridge_transfer NSString*)SKUtilsCreateStringHexadecimalRepresentationOfBytes(md5, CC_MD5_DIGEST_LENGTH);
    return md5String;
}

+ (NSString*)filePathForRequest:(NSURLRequest*)request {
    NSString* fileName = [[self hashForRequest:request] stringByAppendingPathExtension:@"vcr"];
    NSString* filePath = [[NSURLConnectionVCR path] stringByAppendingPathComponent:fileName];
    return filePath;
}

@end
