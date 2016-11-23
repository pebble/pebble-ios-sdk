//
//  PBDefines.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 14/09/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#ifndef PB_DEFINES_H
#define PB_DEFINES_H

#import <Foundation/Foundation.h>

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

#endif
