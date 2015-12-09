//
//  PBPebbleCentral+Legacy.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 09/09/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import <PebbleKit/PBPebbleCentral.h>

NS_ASSUME_NONNULL_BEGIN

@interface PBPebbleCentral (Legacy)

/**
 *  Verifies the currently set application UUID.
 *  @return YES if the currently set UUID is valid, NO if it is not.
 *  @see -setAppUuid:
 */
- (BOOL)hasValidAppUUID __deprecated_msg("Method deprecated. Use `appUUID != nil`");

/**
 *  Enables debug logs. The logs will be printed via NSLog. It is advised to
 *  call this before making any other calls to PebbleKit.
 */
+ (void)setDebugLogsEnabled:(BOOL)logsEnabled __deprecated_msg("Method deprecated. Use `setLogLevel:`");

@property (nonatomic, readonly) PBDataLoggingService * __nullable dataLoggingService __deprecated_msg("Method deprecated. Use `dataLoggingServiceForAppUUID:`");

@end

NS_ASSUME_NONNULL_END
