//
//  NSJSONSerialization+PBJSONHelpers.m
//  PebbleVendor
//
//  Created by matth on 9/17/13.
//  Copyright (c) 2013 Pebble Technology Corp. All rights reserved.
//


#import "NSJSONSerialization+PBJSONHelpers.h"
#import "PBVendorLog.h"

@implementation NSJSONSerialization (PBJSONHelpers)

+ (id)ensureObjectForKey:(NSString *)key inDictionary:(NSDictionary *)dictionary hasExpectedType:(Class)cls nullAllowed:(BOOL)nullAllowed
{
  id object = [dictionary objectForKey:key];
  id extractedObject = object;
  if ([object isEqual:[NSNull null]])
  {
    if (nullAllowed)
    {
      extractedObject = [NSNull null];
    }
    else
    {
      extractedObject = nil;
    }
  }
  else if (object == nil)
  {
    extractedObject = nil;
  }
  else if (![object isKindOfClass:cls])
  {
    VendorLogError(@"Unexpected type when extracting key %@\nExpected type %@ but instead got %@", key, NSStringFromClass(cls), NSStringFromClass([object class]));
    extractedObject = nil;
  }
  return extractedObject;
}

@end
