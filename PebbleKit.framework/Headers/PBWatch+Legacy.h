//
//  PBWatch+Legacy.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 09/09/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import <PebbleKit/PBWatch.h>

NS_ASSUME_NONNULL_BEGIN

@interface PBWatch (Legacy)

/**
 *  Closes the communication session with the watch.
 *  Since there is only one, shared session for all 3rd party iOS apps,
 *  an app should close the session after the user is done using the app/watch-integration,
 *  so it can be used by other apps.
 *  The communication session is implicitely opened automatically when needed.
 *  @param onDone Callback block that will be called after the closing of the session
 *  has completed. If there is no open session, the onDone block will (also) be executed
 *  asynchronously on the calling queue.
 */
- (void)closeSession:(void(^ __nullable)(void))onDone __deprecated_msg("Method deprecated. Use `releaseSharedSession`");

@end

NS_ASSUME_NONNULL_END
