//
//  PBWatch+Version.h
//  PebbleKit
//
//  Created by Martijn The on 9/17/12.
//  Copyright (c) 2012 Pebble Technology. All rights reserved.
//

#import <PebbleKit/PBWatch.h>
#import <PebbleKit/PBVersionInfo.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^PBVersionInfoCompletionBlock)(PBWatch *watch, PBVersionInfo *versionInfo);

PB_EXTERN NSTimeInterval const PBVersionInfoResponseTimeout;


/**
 *  Instances of PBFirmwareMetadata describe a firmware in terms of
 *  its version, whether it is a recovery firmware and its intended hardware
 *  platform.
 *  @see PBVersionInfo
 */
@interface PBWatch (Version)

/**
 *  Requests the version info from the receiver.
 *  Must be called from the main thread.
 *  @param handler The handler that will be called when the version info response has been received.
 *  @param onTimeout The handler that will be called if the watch did not respond within 5 seconds.
 *  @param watch The watch for which the version info was requested.
 *  @param versionInfo The version info response.
 *  @discussion The <PBVersionInfo> response will be cached. The latest version info can be
 *  accessed through the <versionInfo> property of <PBWatch>.
 */
- (void)getVersionInfo:(PBVersionInfoCompletionBlock)handler onTimeout:(void (^ __nullable)(PBWatch *watch))onTimeout;

@end

NS_ASSUME_NONNULL_END
