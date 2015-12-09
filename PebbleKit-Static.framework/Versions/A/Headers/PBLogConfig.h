//
//  PBLogConfig.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 15/09/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import <PebbleKit/PBDefines.h>

PB_EXTERN int const PBKitContext;

/**
 *  All logging will be sent through this function.
 *  The default implementation will log this on NSLog if (level & flag) != 0.
 *  @discussion The parameters match the `LOG_MACRO` parameters of CocoaLumberjack 1.x
 */
PB_EXTERN void PBLog(BOOL synchronous, PBPebbleKitLogLevel level, PBPebbleKitLogFlag flag, int context, const char *file, const char *function, int line, id tag, NSString *format, ...) __attribute__ ((format (__NSString__, 9, 10)));
