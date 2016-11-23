//
//  PBPebbleCentral.h
//  PebbleSDK-iOS
//
//  Created by Martijn Thé on 4/24/12.
//  Copyright (c) 2012 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PBDefines.h"
#import "PBLog+Public.h"

@class PBWatch;
@class PBDataLoggingService;
@protocol PBPebbleCentralDelegate;


NS_ASSUME_NONNULL_BEGIN

/**
 PebbleCentral plays the central role for client iOS apps (e.g. RunKeeper).
 */
PB_EXTERN_CLASS @interface PBPebbleCentral : NSObject

/**
 The watches that are currently connected. Do not cache the array because it can change over time.
 */
@property (nonatomic, readonly, copy) NSArray<PBWatch *> *connectedWatches;

/**
 The watches that are stored in the user preferences of the application.
 */
@property (nonatomic, readonly, copy) NSArray<PBWatch *> *registeredWatches;

/**
 The central's delegate.
 */
@property (nonatomic, readwrite, weak) id<PBPebbleCentralDelegate> __nullable delegate;

/**
 * Identifier of the watch application this companion app communicates with.
 *
 * The identifier is used to make sure that app message and data logging
 * communications arrive to the right companion watch app in the watch (and not
 * to another app).
 *
 * For most app message methods there is are two variants: one that does not
 * take an UUID parameter and one that does (for example,
 * -appMessagesAddReceiveUpdateHandler: vs
 * -appMessagesAddReceiveUpdateHandler:withUUID:). The methods that do not take
 * an UUID, will use the UUID as set prior to this property.
 *
 * @note The UUID needs to be set before using either app message or data logging.
 */
@property (nonatomic, copy) NSUUID * __nullable appUUID;

/**
 * The list of App-UUIDs this PebbleCentral wants to talk to.
 * @see addAppUUID:
 */
@property (nonatomic, copy) NSSet<NSUUID *> *appUUIDs;

/**
 * Registers a new App-UUID with appUUIDs.
 *
 * @param appUUID The app UUID to register.
 *
 * @see appUUIDs
 */
- (void)addAppUUID:(NSUUID *)appUUID;

/**
 Registers and announces internal Bluetooth services. Might cause a dialog to allow this
 app to talk to other devices.
 */
- (void)run;

/**
 Determines if the Pebble iOS app is installed in the device.

 @note Since iOS 9.0 you have to add “pebble” to `LSApplicationQueriesSchemes`
       in your application `Info.plist` or this method will return `NO` all the
       time.

 @return `YES` if the Pebble iOS app is installed, `NO` if it is not installed.
 */
- (BOOL)isMobileAppInstalled;

/**
 Redirects to Pebble in the App Store, so the user can install the app.
 */
- (void)installMobileApp;

/**
 Wipes out the data associated with the registered watches, that is stored on the phone.
 */
- (void)unregisterAllWatches;

/**
 Returns the most recently connected watch from the -registeredWatches array.
 */
- (PBWatch * __nullable)lastConnectedWatch;

/**
 * Returns the DataLoggingService for a (previously registered) appUUID
 *
 * @param appUUID The app UUID to recover the data logging service.
 */
- (PBDataLoggingService *__nullable)dataLoggingServiceForAppUUID:(NSUUID *)appUUID;

@end


@protocol PBPebbleCentralDelegate <NSObject>
@optional

/**
 @param central The Pebble Central responsible for calling the delegate method.
 @param watch The PBWatch object representing the watch that was connected.
 @param isNew YES if the watch has been connected for the first time since the app has been installed or NO if not.
 */
- (void)pebbleCentral:(PBPebbleCentral*)central watchDidConnect:(PBWatch*)watch isNew:(BOOL)isNew;

/**
 @param central The Pebble Central responsible for calling the delegate method.
 @param watch The PBWatch object representing the watch that was disconnected.
 */
- (void)pebbleCentral:(PBPebbleCentral*)central watchDidDisconnect:(PBWatch*)watch;

@end


@interface PBPebbleCentral (Unavailable)

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END
