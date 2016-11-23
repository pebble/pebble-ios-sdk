//
//  PBWatch.h
//  PebbleSDK-iOS
//
//  Created by Martijn Thé on 4/24/12.
//  Copyright (c) 2012 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PBDefines.h"

@protocol PBWatchDelegate;
@class PBPebbleCentral;
@class PBVersionInfo;
@class PBDataLoggingService;

NS_ASSUME_NONNULL_BEGIN

/**
 * Represents a Pebble watch.
 */
PB_EXTERN_CLASS @interface PBWatch : NSObject

/**
 * The central that is managing this watch.
 * @discussion This property is KVO-compliant.
 */
@property (nonatomic, weak, readonly) PBPebbleCentral *central;

/**
 * YES if the receiver it's the first time that watch has been seen.
 * @discussion This property is KVO-compliant.
 */
#ifdef __cplusplus
- (BOOL)isNew;
#else
@property (nonatomic, readonly, getter=isNew) BOOL new;
#endif

/**
 * YES if the receiver is connected and NO if the receiver is disconnected.
 * @discussion This property is KVO-compliant.
 */
@property (nonatomic, assign, readonly, getter=isConnected) BOOL connected;

/**
 * The human-friendly name of the receiver.
 * This is the same name as the user will see in the iOS Bluetooth Settings.
 */
@property (nonatomic, copy, readonly) NSString *name;

/**
 * The serial number of the receiver.
 */
@property (nonatomic, copy, readonly) NSString *serialNumber;

/**
 * The versionInfo of the receiver.
 * @see PBVersionInfo
 */
@property (nonatomic, strong, readonly) PBVersionInfo * __nullable versionInfo;

/**
 * The delegate of the watch that will be notified of disconnections and errors.
 * @see PBWatchDelegate
 */
@property (nonatomic, weak) id<PBWatchDelegate> __nullable delegate;

/**
 * The userInfo property can be used to associate application specific data
 * with the watch. Note that the application itself is responsible for persisting
 * the information if neccessary.
 */
@property (nonatomic, strong) id __nullable userInfo;

/**
 * The date when the watch was last known to be connected.
 * This date will be updated automatically when the watch connects and
 * disconnects. While the watch is being connected, this date will not be updated.
 */
@property (nonatomic, strong, readonly) NSDate *lastConnectedDate;

/**
 * Developer-friendly debugging description of the watch.
 * @return developer-friendly summary of the receiver, including
 * software and hardware version information, if available.
 */
- (NSString *)friendlyDescription;

/**
 * Releases the shared session to the watch (if one exists).
 *
 * Depending on availability a per-app dedicated Bluetooth LE based session
 * (CoreBluetooth.framework) will be used to talk to the watch. In other cases
 * a Bluetooth Classic based session (ExternalAccessory.framework) will be used
 * that is shared between all 3rd party iOS apps.
 *
 * Once the user is done using the app/watch-integration, the shared sessions
 * has to be released using this method so it can be used by other apps.
 *
 * @deprecated Remove usages of this method. The implementation is empty.
 */
- (void)releaseSharedSession __attribute__((deprecated("Remove. The implementation is empty.")));

@end

@protocol PBWatchDelegate <NSObject>
@optional

/**
 * Called when the watch got disconnected.
 *
 * @param watch The watch that was disconnected.
 */
- (void)watchDidDisconnect:(PBWatch *)watch;

/**
 * Called when the watch caught an error.
 *
 * @param watch The watch that caught the error.
 * @param error The error catch by the watch.
 */
- (void)watch:(PBWatch *)watch handleError:(NSError *)error;

/**
 * Called when an internal session is about to be reset.
 *
 * @param watch The watch that will reset its session.
 */
- (void)watchWillResetSession:(PBWatch *)watch;

/**
 * Called when an internal session is opened
 *
 * @param watch The watch that opened a session.
 */
- (void)watchDidOpenSession:(PBWatch *)watch;

/**
 * Called when an internal EASession is closed
 *
 * @param watch The watch that closed its session.
 */
- (void)watchDidCloseSession:(PBWatch *)watch;

@end

NS_ASSUME_NONNULL_END
