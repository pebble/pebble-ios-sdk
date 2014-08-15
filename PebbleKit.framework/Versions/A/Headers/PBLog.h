//
//  PBLog.h
//  PebbleApp
//
//  Created by Martijn The on 11/29/12.
//  Copyright (c) 2012 Pebble Technology. All rights reserved.
//

#import <PebbleVendor/DDLog.h>

extern int PBLogLevel;

extern int const PBKitContext;
extern int const PBWSContext;



#define LogError(frmt, ...)   LOG_OBJC_MAYBE(LOG_ASYNC_ERROR,   PBLogLevel, LOG_FLAG_ERROR,   PBKitContext, frmt, ##__VA_ARGS__)
#define LogWarn(frmt, ...)    LOG_OBJC_MAYBE(LOG_ASYNC_WARN,    PBLogLevel, LOG_FLAG_WARN,    PBKitContext, frmt, ##__VA_ARGS__)
#define LogInfo(frmt, ...)    LOG_OBJC_MAYBE(LOG_ASYNC_INFO,    PBLogLevel, LOG_FLAG_INFO,    PBKitContext, frmt, ##__VA_ARGS__)
#define LogDebug(frmt, ...)   LOG_OBJC_MAYBE(LOG_ASYNC_DEBUG,   PBLogLevel, LOG_FLAG_DEBUG,   PBKitContext, frmt, ##__VA_ARGS__)
#define LogVerbose(frmt, ...) LOG_OBJC_MAYBE(LOG_ASYNC_VERBOSE, PBLogLevel, LOG_FLAG_VERBOSE, PBKitContext, frmt, ##__VA_ARGS__)

#define LogCError(frmt, ...)   LOG_C_MAYBE(LOG_ASYNC_ERROR,   PBLogLevel, LOG_FLAG_ERROR,   PBKitContext, frmt, ##__VA_ARGS__)
#define LogCWarn(frmt, ...)    LOG_C_MAYBE(LOG_ASYNC_WARN,    PBLogLevel, LOG_FLAG_WARN,    PBKitContext, frmt, ##__VA_ARGS__)
#define LogCInfo(frmt, ...)    LOG_C_MAYBE(LOG_ASYNC_INFO,    PBLogLevel, LOG_FLAG_INFO,    PBKitContext, frmt, ##__VA_ARGS__)
#define LogCDebug(frmt, ...)   LOG_C_MAYBE(LOG_ASYNC_DEBUG,   PBLogLevel, LOG_FLAG_DEBUG,   PBKitContext, frmt, ##__VA_ARGS__)
#define LogCVerbose(frmt, ...) LOG_C_MAYBE(LOG_ASYNC_VERBOSE, PBLogLevel, LOG_FLAG_VERBOSE, PBKitContext, frmt, ##__VA_ARGS__)

#define WSLogError(frmt, ...)   LOG_OBJC_MAYBE(LOG_ASYNC_ERROR,   PBLogLevel, LOG_FLAG_ERROR,   PBWSContext, frmt, ##__VA_ARGS__)
#define WSLogWarn(frmt, ...)    LOG_OBJC_MAYBE(LOG_ASYNC_WARN,    PBLogLevel, LOG_FLAG_WARN,    PBWSContext, frmt, ##__VA_ARGS__)
#define WSLogInfo(frmt, ...)    LOG_OBJC_MAYBE(LOG_ASYNC_INFO,    PBLogLevel, LOG_FLAG_INFO,    PBWSContext, frmt, ##__VA_ARGS__)
#define WSLogDebug(frmt, ...)   LOG_OBJC_MAYBE(LOG_ASYNC_DEBUG,   PBLogLevel, LOG_FLAG_DEBUG,   PBWSContext, frmt, ##__VA_ARGS__)
#define WSLogVerbose(frmt, ...) LOG_OBJC_MAYBE(LOG_ASYNC_VERBOSE, PBLogLevel, LOG_FLAG_VERBOSE, PBWSContext, frmt, ##__VA_ARGS__)

