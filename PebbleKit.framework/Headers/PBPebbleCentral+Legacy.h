//
//  PBPebbleCentral+Legacy.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 09/09/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import "PBPebbleCentral.h"

NS_ASSUME_NONNULL_BEGIN

@interface PBPebbleCentral (Legacy)

/**
 * Indicates if the central has been correctly configured with an app UUID.
 *
 * @deprecated Use `appUUID != nil` instead.
 */
- (BOOL)hasValidAppUUID __attribute__((deprecated("Use `appUUID != nil` instead.")));

/**
 * Enables or disables debug logging for PebbleKit.
 *
 * @deprecated Use `+[PBPebbleKitLogging setLogLevel:]` instead.
 *
 * @param logsEnabled Whether logging should be enabled or not.
 */
+ (void)setDebugLogsEnabled:(BOOL)logsEnabled __attribute__((deprecated("Use `+[PBPebbleKitLogging setLogLevel:]` instead.")));

/**
 * Configures which events should be logged.
 *
 * @deprecated Use `+[PBPebbleKitLogging setLogLevel:]` instead.
 *
 * @param logLevel One of the values in PBPebbleKitLogLevel, which will be the
 *                 maximum level that will be logged. You can use
 *                 `PBPebbleKitLogLevelOff` to disable all logging.
 */
+ (void)setLogLevel:(PBPebbleKitLogLevel)logLevel __attribute__((deprecated("Use `+[PBPebbleKitLogging setLogLevel:]` instead.")));

/**
 * @deprecated Use `dataLoggingServiceForAppUUID:` instead.
 */
@property (nonatomic, readonly) PBDataLoggingService *__nullable dataLoggingService __attribute__((deprecated("Use `dataLoggingServiceForAppUUID:` instead.")));

@end

NS_ASSUME_NONNULL_END
