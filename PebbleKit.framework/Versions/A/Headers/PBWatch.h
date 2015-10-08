//
//  PBWatch.h
//  PebbleSDK-iOS
//
//  Created by Martijn Thé on 4/24/12.
//  Copyright (c) 2012 Pebble Technology. All rights reserved.
//

#import <PebbleKit/PBDefines.h>
#import <Foundation/Foundation.h>

@protocol PBWatchDelegate;
@class PBPebbleCentral;
@class PBVersionInfo;
@class PBDataLoggingService;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Represents a Pebble watch.
 *
 *  On iOS, there is the notion of a "communication session" between an app and
 *  the Pebble watch. You can imagine this as a "data pipe" directly from the
 *  watch to your app. However, there is only one session for 3rd party apps.
 *  This one session has to be shared among all 3rd party apps that want to
 *  communicate with Pebble (excluding the official Pebble iOS app).
 *
 *  Unfortunately, the session can only be opened from the phone app. This means
 *  that the iOS app has to start talking to the watch first to open the
 *  communications channel; the other way around is not possible.
 *  Most methods in the PBWatch categories (Ping), (Version), (Sports), (Golf)
 *  and (AppMessages) all implicitly open the shared communication session.
 *
 *  Lastly, iOS provides no good way to manage how the one shared session is
 *  accessed or used. Simply, the last iOS app to try to open it, wins and gets
 *  to use it. Therefore, it is important that your iOS app does **not** try
 *  communicate when a Pebble is connected.
 *
 *  When the user has stopped using your app (e.g. when going to the background
 *  or when explicitely stopping a certain activity in the app) your iOS app
 *  should close the communication session using the -closeSession: method.
 */
PB_EXTERN_CLASS @interface PBWatch : NSObject

/**
 *  The central that is managing this watch.
 *  @discussion This property is KVO-compliant.
 */
@property (nonatomic, weak, readonly) PBPebbleCentral *central;

/**
 *  YES if the receiver it's the first time that watch has been seen.
 *  @discussion This property is KVO-compliant.
 */
@property (nonatomic, readonly, getter=isNew) BOOL new;

/**
 *  YES if the receiver is connected and NO if the receiver is disconnected.
 *  @discussion This property is KVO-compliant.
 */
@property (nonatomic, assign, readonly, getter=isConnected) BOOL connected;

/**
 *  The human-friendly name of the receiver.
 *  This is the same name as the user will see in the iOS Bluetooth Settings.
 */
@property (nonatomic, copy, readonly) NSString *name;

/**
 *  The serial number of the receiver.
 */
@property (nonatomic, copy, readonly) NSString *serialNumber;

/**
 *  The versionInfo of the receiver.
 *  @see PBVersionInfo
 */
@property (nonatomic, strong, readonly) PBVersionInfo * __nullable versionInfo;

/**
 *  The delegate of the watch that will be notified of disconnections and errors.
 *  @see PBWatchDelegate
 */
@property (nonatomic, weak) id<PBWatchDelegate> __nullable delegate;

/**
 *  The userInfo property can be used to associate application specific data
 *  with the watch. Note that the application itself is responsible for persisting
 *  the information if neccessary.
 */
@property (nonatomic, strong) id __nullable userInfo;

/**
 *  The date when the watch was last known to be connected.
 *  This date will be updated automatically when the watch connects and
 *  disconnects. While the watch is being connected, this date will not be updated.
 */
@property (nonatomic, strong, readonly) NSDate *lastConnectedDate;

/**
 *  Developer-friendly debugging description of the watch.
 *  @return localized, user-friendly summary of the receiver, including
 *  software and hardware version information, if available.
 */
- (NSString*)friendlyDescription;

/** @abstract Releases the shared session to the watch (if one exists).
 *  @discussion Depending on availability a per-app dedicated Bluetooth LE
 *  based session (CoreBluetooth.framework) will be used to talk to the watch.
 *  In other cases a Bluetooth Classic based session (ExternalAccessory.framework)
 *  will be used that is shared between all 3rd party iOS apps.
 *  Once the user is done using the app/watch-integration, the shared sessions
 *  has to be released using this method so it can be used by other apps.
 */
- (void)releaseSharedSession;

@end

@protocol PBWatchDelegate <NSObject>
@optional

/**
 *  Called when the watch got disconnected.
 */
- (void)watchDidDisconnect:(PBWatch*)watch;

/**
 *  Called when the watch caught an error.
 */
- (void)watch:(PBWatch*)watch handleError:(NSError*)error;

/**
 *  Called when an internal session is about to be reset.
 */
- (void)watchWillResetSession:(PBWatch*)watch;

/**
 *  Called when an internal session is opened
 */
- (void)watchDidOpenSession:(PBWatch*)watch;

/**
 *  Called when an internal EASession is closed
 */
- (void)watchDidCloseSession:(PBWatch*)watch;

@end

NS_ASSUME_NONNULL_END
