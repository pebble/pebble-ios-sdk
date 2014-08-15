//
//  PBVendorLog.h
//  PebbleVendor
//
//  Copyright (c) 2013 Pebble Technology Corp. All rights reserved.
//

#import <PebbleVendor/DDLog.h>

extern int PBVendorLogLevel;

#define VendorLogError(frmt, ...)   LOG_OBJC_MAYBE(LOG_ASYNC_ERROR,   PBVendorLogLevel, LOG_FLAG_ERROR,   0, frmt, ##__VA_ARGS__)
#define VendorLogWarn(frmt, ...)    LOG_OBJC_MAYBE(LOG_ASYNC_WARN,    PBVendorLogLevel, LOG_FLAG_WARN,    0, frmt, ##__VA_ARGS__)
#define VendorLogInfo(frmt, ...)    LOG_OBJC_MAYBE(LOG_ASYNC_INFO,    PBVendorLogLevel, LOG_FLAG_INFO,    0, frmt, ##__VA_ARGS__)
#define VendorLogVerbose(frmt, ...) LOG_OBJC_MAYBE(LOG_ASYNC_VERBOSE, PBVendorLogLevel, LOG_FLAG_VERBOSE, 0, frmt, ##__VA_ARGS__)

#define VendorLogCError(frmt, ...)   LOG_C_MAYBE(LOG_ASYNC_ERROR,   PBVendorLogLevel, LOG_FLAG_ERROR,   0, frmt, ##__VA_ARGS__)
#define VendorLogCWarn(frmt, ...)    LOG_C_MAYBE(LOG_ASYNC_WARN,    PBVendorLogLevel, LOG_FLAG_WARN,    0, frmt, ##__VA_ARGS__)
#define VendorLogCInfo(frmt, ...)    LOG_C_MAYBE(LOG_ASYNC_INFO,    PBVendorLogLevel, LOG_FLAG_INFO,    0, frmt, ##__VA_ARGS__)
#define VendorLogCVerbose(frmt, ...) LOG_C_MAYBE(LOG_ASYNC_VERBOSE, PBVendorLogLevel, LOG_FLAG_VERBOSE, 0, frmt, ##__VA_ARGS__)
