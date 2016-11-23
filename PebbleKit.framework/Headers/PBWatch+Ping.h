//
//  PBWatch+Ping.h
//  PebbleKit
//
//  Created by Martijn The on 9/14/12.
//  Copyright (c) 2012 Pebble Technology. All rights reserved.
//

#import "PBWatch.h"

NS_ASSUME_NONNULL_BEGIN

@interface PBWatch (Ping)

/**
 * Sends a ping to the watch.
 *
 * Must be called from the main thread.
 *
 * @param cookie A number identifying the ping.
 * @param onPong The block handler that will be called when the "pong" reply from the watch has been received.
 * @param onTimeout The block handler that will be called when the watch failed to reply in time.
 */
- (void)pingWithCookie:(uint32_t)cookie onPong:(void(^ __nullable)(PBWatch *watch, uint32_t cookie))onPong onTimeout:(void(^ __nullable)(PBWatch *watch, uint32_t cookie))onTimeout;

@end

NS_ASSUME_NONNULL_END
