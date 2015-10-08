//
//  PBDefines.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 14/09/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#ifndef PB_EXTERN
#  ifdef __cplusplus
#    define PB_EXTERN extern "C" __attribute__((visibility ("default")))
#  else
#    define PB_EXTERN extern __attribute__((visibility ("default")))
#  endif
#endif

#define PB_EXTERN_CLASS __attribute__((visibility("default")))

#if !__has_feature(nullability)
#  define __nullable
#  define __nonnull
#  define __null_unspecified
#endif

#if !__has_feature(assume_nonnull)
#  ifndef NS_ASSUME_NONNULL_BEGIN
#    define NS_ASSUME_NONNULL_BEGIN
#  endif
#  ifndef NS_ASSUME_NONNULL_END
#    define NS_ASSUME_NONNULL_END
#  endif
#endif

#if __has_feature(objc_generics)
#  define PBGeneric(Type, ...) Type<__VA_ARGS__>
#else
#  define PBGeneric(Type, ...) Type
#endif

typedef NS_OPTIONS(unsigned int, PBPebbleKitLogFlag) {
  PBPebbleKitLogFlagError      = (1 << 0), // 0...00001
  PBPebbleKitLogFlagWarning    = (1 << 1), // 0...00010
  PBPebbleKitLogFlagInfo       = (1 << 2), // 0...00100
  PBPebbleKitLogFlagDebug      = (1 << 3), // 0...01000
  PBPebbleKitLogFlagVerbose    = (1 << 4)  // 0...10000
};

typedef NS_ENUM(unsigned int, PBPebbleKitLogLevel) {
  PBPebbleKitLogLevelOff       = 0,
  PBPebbleKitLogLevelError     = (PBPebbleKitLogFlagError),                                // 0...00001
  PBPebbleKitLogLevelWarning   = (PBPebbleKitLogLevelError   | PBPebbleKitLogFlagWarning), // 0...00011
  PBPebbleKitLogLevelInfo      = (PBPebbleKitLogLevelWarning | PBPebbleKitLogFlagInfo),    // 0...00111
  PBPebbleKitLogLevelDebug     = (PBPebbleKitLogLevelInfo    | PBPebbleKitLogFlagDebug),   // 0...01111
  PBPebbleKitLogLevelVerbose   = (PBPebbleKitLogLevelDebug   | PBPebbleKitLogFlagVerbose), // 0...11111
  PBPebbleKitLogLevelAll       = 0xffffffff                                                // 1...11111 (PBLogLevelVerbose plus any other flags)
};
