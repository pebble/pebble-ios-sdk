//
//  PBWatch+AppMessages.h
//  PebbleKit
//
//  Created by Martijn The on 3/20/13.
//  Copyright (c) 2013 Pebble Technology. All rights reserved.
//

#import <PebbleKit/PBWatch.h>
#import <PebbleKit/PBDefines.h>

NS_ASSUME_NONNULL_BEGIN

@interface PBWatch (AppMessages)

/**
 *  Queries the watch whether AppMessages are supported.
 *  Must be called from the main thread.
 *  @param fetchedBlock The block that will be called whenthe inquiry has finished. The fetchedBlock will be called
 *  asynchronously on the queue that was originally used when calling this method.
 *  @param watch The watch on which the query was performed.
 *  @param isAppMessagesSupported YES if AppMessages are supported, NO if not.
 */
- (void)appMessagesGetIsSupported:(void(^)(PBWatch *watch, BOOL isAppMessagesSupported))fetchedBlock __deprecated_msg("Method deprecated. Use `getVersionInfo:onTimeout:` and `versionInfo.appMessagesSupported` instead.");

/**
 *  Pushes an update to the watch application with UUID as set using
 *  -[PBPebbleCentral setAppUUID:]
 *  Must be called from the main thread.
 *  @param dictionary Contains the key/value pairs to update. The dictionary can only contain items with an NSNumber
 *  key and only contain NSString, NSNumber or NSData values. Use the methods in the NSNumber (stdint) category to
 *  create NSNumbers with specific types standard integer types.
 *  @param onSent The block that will be called when the message was accepted, rejected or timed out.
 *  @param watch The watch to which the update was sent.
 *  @param update The dictionary that was sent.
 *  @param error If there was a problem, this will contain information about the underlying problem. See PBError.h for error codes.
 */
- (void)appMessagesPushUpdate:(PBGeneric(NSDictionary, NSNumber*, id) *)dictionary onSent:(void(^ __nullable)(PBWatch *watch, NSDictionary *update, NSError * __nullable error))onSent;

/**
 *  Pushes an update to the watch application with the specified UUID.
 *  Must be called from the main thread.
 *  @param dictionary Contains the key/value pairs to update. The dictionary can only contain items with an NSNumber
 *  key and only contain NSString, NSNumber or NSData values. Use the methods in the NSNumber (stdint) category to
 *  create NSNumbers with specific types standard integer types.
 *  @param appUUID The UUID of the watchapp to which the update should be sent.
 *  @param onSent The block that will be called when the message was accepted, rejected or timed out.
 *  @param watch The watch to which the update was sent.
 *  @param update The dictionary that was sent.
 *  @param error If there was a problem, this will contain information about the underlying problem. See PBError.h for error codes.
 */
- (void)appMessagesPushUpdate:(PBGeneric(NSDictionary, NSNumber*, id) *)dictionary withUUID:(NSUUID *)appUUID onSent:(void(^ __nullable)(PBWatch *watch, NSDictionary *update, NSError * __nullableerror))onSent;

/**
 *  Add a receive handler for incoming updates that are send by the watch application with UUID as set using
 *  -[PBPebbleCentral setAppUUID:]
 *  Must be called from the main thread.
 *  @param onReceive The block that will be called every time a new update message arrives.
 *  @param watch The watch that has sent the update.
 *  @param update The dictionary containing the values sent by the watch.
 *  @return An opaque handle object representing the installed receive handler, that can be used in -appMessagesRemoveUpdateHandler:
 *  @see -appMessagesRemoveUpdateHandler:
 */
- (id)appMessagesAddReceiveUpdateHandler:(BOOL(^)(PBWatch *watch, PBGeneric(NSDictionary, NSNumber*, id) *update))onReceive;

/**
 *  Add a receive handler for incoming updates that are send by the watch application with the specified UUID.
 *  Must be called from the main thread.
 *  @param onReceive The block that will be called every time a new update message arrives. You should always return YES so than an ACK is sent to the watch.
 *  @param watch The watch that has sent the update.
 *  @param update The dictionary containing the values sent by the watch.
 *  @param appUUID The UUID of the watchapp for which sent messages should be handled by the onReceive block.
 *  @return An opaque handle object representing the installed receive handler, that can be used in -appMessagesRemoveUpdateHandler:
 *  @see -appMessagesRemoveUpdateHandler:
 */
- (id)appMessagesAddReceiveUpdateHandler:(BOOL(^)(PBWatch *watch, PBGeneric(NSDictionary, NSNumber*, id) *update))onReceive withUUID:(NSUUID *)appUUID;

/**
 *  Removes a receive handler that was previously installed using -appMessagesAddReceiveUpdateHandler:
 *  Must be called from the main thread.
 *  @param opaqueHandle The handle object as returned by -appMessagesAddReceiveUpdateHandler:
 *  @see -appMessagesAddReceiveUpdateHandler:
 */
- (void)appMessagesRemoveUpdateHandler:(id)opaqueHandle;

/**
 *  Sends a command to launch the watch application with UUID as set using
 *  -[PBPebbleCentral setAppUUID:]
 *  Must be called from the main thread.
 *  @param onSent The block that will be called after the launch command has been
 *  sent to the watch.
 *  @param watch The watch to which the command was sent.
 *  @param error If there was a problem, this will contain information about the underlying problem. See PBError.h for error codes.
 */
- (void)appMessagesLaunch:(void(^ __nullable)(PBWatch *watch, NSError * __nullable error))onSent;

/**
 *  Sends a command to launch the watch application with the specified UUID.
 *  Must be called from the main thread.
 *  @param onSent The block that will be called after the launch command has been
 *  sent to the watch.
 *  @param watch The watch to which the command was sent.
 *  @param error If there was a problem, this will contain information about the underlying problem. See PBError.h for error codes.
 *  @param appUUID The UUID of the watch application to launch.
 */
- (void)appMessagesLaunch:(void(^ __nullable)(PBWatch *watch, NSError * __nullable error))onSent withUUID:(NSUUID *)appUUID;

/**
 *  Sends a command to kill the watch application with UUID as set using
 *  -[PBPebbleCentral setAppUUID:]
 *  Must be called from the main thread.
 *  @param onSent The block that will be called after the kill command has been
 *  sent to the watch.
 *  @param watch The watch to which the command was sent.
 *  @param error If there was a problem, this will contain information about the underlying problem. See PBError.h for error codes.
 */
- (void)appMessagesKill:(void(^ __nullable)(PBWatch *watch, NSError * __nullable error))onSent;

/**
 *  Sends a command to kill the watch application with the specified UUID.
 *  Must be called from the main thread.
 *  @param onSent The block that will be called after the kill command has been
 *  sent to the watch.
 *  @param watch The watch to which the command was sent.
 *  @param error If there was a problem, this will contain information about the underlying problem. See PBError.h for error codes.
 *  @param appUUID The UUID of the watch application to launch.
 */
- (void)appMessagesKill:(void(^ __nullable)(PBWatch *watch, NSError * __nullable error))onSent withUUID:(NSUUID *)appUUID;

@end

NS_ASSUME_NONNULL_END
