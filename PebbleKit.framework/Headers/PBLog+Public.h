//
//  PBLog+Public.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 15/09/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef PB_LOG_PUBLIC_H
#define PB_LOG_PUBLIC_H

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, PBPebbleKitLogFlag) {
  PBPebbleKitLogFlagError      = (1 << 0), // 0...00001
  PBPebbleKitLogFlagWarning    = (1 << 1), // 0...00010
  PBPebbleKitLogFlagInfo       = (1 << 2), // 0...00100
  PBPebbleKitLogFlagDebug      = (1 << 3), // 0...01000
  PBPebbleKitLogFlagVerbose    = (1 << 4)  // 0...10000
};

typedef NS_ENUM(NSUInteger, PBPebbleKitLogLevel) {
  PBPebbleKitLogLevelOff       = 0,
  PBPebbleKitLogLevelError     = (PBPebbleKitLogFlagError),                                // 0...00001
  PBPebbleKitLogLevelWarning   = (PBPebbleKitLogLevelError   | PBPebbleKitLogFlagWarning), // 0...00011
  PBPebbleKitLogLevelInfo      = (PBPebbleKitLogLevelWarning | PBPebbleKitLogFlagInfo),    // 0...00111
  PBPebbleKitLogLevelDebug     = (PBPebbleKitLogLevelInfo    | PBPebbleKitLogFlagDebug),   // 0...01111
  PBPebbleKitLogLevelVerbose   = (PBPebbleKitLogLevelDebug   | PBPebbleKitLogFlagVerbose), // 0...11111
  PBPebbleKitLogLevelAll       = 0xffffffff                                                // 1...11111 (PBLogLevelVerbose plus any other flags)
};

/**
 * A logging callback invoked whenever PebbleKit wants to add some message to
 * the log.
 *
 * It’s important to notice that your logging callback should not block if
 * possible, unless the asynchronous flag is NO, in which case blocking is
 * allowed.
 *
 * @note See CocoaLumberjack documentation for more information about the
 *       usage of the paramaters and what they exactly mean:
 *       https://github.com/CocoaLumberjack/CocoaLumberjack/tree/master/Documentation
 *
 * @param asynchronous YES if the logging is done async, NO if you want to force sync
 * @param level        the log level
 * @param flag         the log flag
 * @param context      the context (if any is defined)
 * @param file         the current file
 * @param function     the current function
 * @param line         the current code line
 * @param tag          potential tag
 * @param format       the log format
 * @param args         the arguments list as a va_list
 */
typedef void (^PBPebbleKitLoggingCallback)(BOOL asynchronous,
                                           PBPebbleKitLogLevel level,
                                           PBPebbleKitLogFlag flag,
                                           NSInteger context,
                                           const char *file,
                                           const char *function,
                                           NSUInteger line,
                                           id __nullable tag,
                                           NSString *format,
                                           va_list args);

/**
 * Every log produced by PebbleKit will be sent through this type.
 *
 * By default the logs are simply sent to `NSLog`, but the callback can be
 * overriden to send the logs to another logging facility.
 *
 * The maximum log level can be also modified. The default callback handles
 * the log level automatically, but any customized logging callbacks will need
 * to handle the log level themselves.
 *
 * It is advised to call these methods before making any other calls to
 * PebbleKit, for example in your AppDelegate's
 * `application:willFinishLaunchingWithOptions:` before state restoration
 * happens.
 */
PB_EXTERN_CLASS @interface PBPebbleKitLogging : NSObject

/**
 * Configures which events should be logged.
 *
 * @param logLevel One of the values in PBPebbleKitLogLevel, which will be the
 *                 maximum level that will be logged. You can use
 *                 `PBPebbleKitLogLevelOff` to disable all logging.
 */
+ (void)setLogLevel:(PBPebbleKitLogLevel)logLevel;

/**
 * Sets a new logging callback that will be invoked for each of the log records
 * emitted by PebbleKit.
 *
 * @param loggingCallback A block that will be invoked for each of the log
 *                        records emitted by PebbleKit. Set this value to nil
 *                        to return to the default `NSLog` logging.
 */
+ (void)setLoggingCallback:(nullable PBPebbleKitLoggingCallback)loggingCallback;

/**
 * @note You should not create instances of this type.
 */
+ (instancetype)new NS_UNAVAILABLE;

/**
 * @note You should not create instances of this type.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif
