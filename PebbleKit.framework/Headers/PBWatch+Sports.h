//
//  PBWatch+Sports.h
//  PebbleKit
//
//  Created by Martijn The on 2/7/13.
//  Copyright (c) 2013 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PBDefines.h"
#import "PBWatch.h"

NS_ASSUME_NONNULL_BEGIN

@class UIImage;



/**
 * The UUID of the Sports watch app.
 */
PB_EXTERN NSUUID *PBSportsUUID;

// The documentation for these keys is in -[PBWatch sportsAppUpdate:onSent:].
PB_EXTERN NSNumber *PBSportsTimeKey;
PB_EXTERN NSNumber *PBSportsDistanceKey;
PB_EXTERN NSNumber *PBSportsDataKey;
PB_EXTERN NSNumber *PBSportsActivityStateKey;
PB_EXTERN NSNumber *PBSportsIsPaceKey;
PB_EXTERN NSNumber *PBSportsHeartBPMKey;
PB_EXTERN NSNumber *PBSportsCustomLabelKey;
PB_EXTERN NSNumber *PBSportsCustomValueKey;

/**
 * The state of the Sports activity.
 *
 * @see -[PBWatch sportsAppAddReceiveUpdateHandler:]
 */
typedef NS_ENUM(uint8_t, SportsAppActivityState) {
  SportsAppActivityStateInit = 0x00,
  SportsAppActivityStateRunning = 0x01,
  SportsAppActivityStatePaused = 0x02,
  SportsAppActivityStateEnd = 0x03,
};

/**
 * The unit system available for the Sports app.
 *
 * @see -[PBWatch(Sports) sportsAppSetUnitSystem:onSent:]
 */
typedef NS_ENUM(NSInteger, PBUnitSystem) {
  /// The metric system. Use kilometers, kilometers per hour and minutes per
  /// kilometer.
  PBUnitSystemMetric,
  /// The imperial system. Use miles, miles per hour and minutes per mile.
  PBUnitSystemImperial,
};

/**
 * Packages a UI update of the sports app.
 *
 * This container class includes new values of time, distance, pace or
 * speed, heart rate, and a custom label/value. To send the values to the
 * watch use -[PBSportsUpdate updateWatch:completion:].
 *
 * The class is mutable, so consumers can update the values and send the same
 * instance again. Modifying the values of this class will not send the values.
 * The consumer needs to invoke -[PBSportsUpdate updateWatch:completion:] every
 * time the UI needs to be updated.
 */
PB_EXTERN_CLASS @interface PBSportsUpdate : NSObject

/**
 * The current time in seconds.
 *
 * The possible range is currently limited from -35999 to 35999,
 * inclusive (±9h 59min 59sec). Values larger or smaller than the limits will
 * be transformed into the maximum or minimum, respectively.
 *
 * It will be presented as a duration string in the UI. Hours, minutes and
 * seconds will be separated by colons. The hours value will only appear if
 * the value is more than 1 hour. The decimal part will be discarded for the
 * presentation.
 */
@property (nonatomic) NSTimeInterval time;

/**
 * The current distance in kilometers or miles.
 *
 * The possible range is currently limited from -99.9 to 99.9, inclusive. Values
 * larger or smaller than the limits will be transformed into the maximum or
 * minimum, respectively.
 *
 * It will be presented as a decimal number in the UI. The decimal part will be
 * rounded to one digit.
 *
 * The unit of distance is dependent on the current unit setting.
 *
 * @see -[PBWatch sportsAppSetMetric:onSent:]
 */
@property (nonatomic) float distance;

/**
 * The current pace in seconds per kilometer or seconds per mile.
 *
 * The possible range is currently limited from -3599 to 3599,
 * inclusive (±59min 59sec). Values larger or smaller than the limits will be
 * transformed into the maximum or minimum, respectively.
 *
 * It will be presented as a duration string in the UI. Minutes and seconds will
 * be separated by colons. The decimal part will be discarded for the
 * presentation.
 *
 * Currently pace and speed cannot be presented at the same time. Setting speed
 * will discard the value set through pace.
 */
@property (nonatomic) NSTimeInterval pace;

/**
 * The current speed in kilometers per hour or miles per hour.
 *
 * The possible range is currently limited from -99.9 to 99.9, inclusive. Values
 * larger or smaller than the limits will be transformed into the maximum or
 * minimum, respectively.
 *
 * It will be presented as a decimal number in the UI. The decimal part will be
 * rounded to one digit.
 *
 * Currently pace and speed cannot be presented at the same time. Setting pace
 * will discard the value set through speed.
 */
@property (nonatomic) float speed;

/**
 * The current heart rate in beats per minute.
 *
 * Currently there’s no way to stop sending heart rate values if one heart rate
 * value was sent. The last value will be shown in the UI.
 *
 * If the heart rate has never been set before, this property will return zero.
 */
@property (nonatomic) uint8_t heartRate;

/**
 * A custom label to show in the sports UI.
 *
 * The maximum number of characters is ~10, but this maximum is not enforced.
 * The label will be sent in upper case to the watch.
 *
 * To be sent, both customLabel and customValue have to be set to non-nil values.
 */
@property (nonatomic, copy, nullable) NSString *customLabel;

/**
 * A custom value to show in the sports UI.
 *
 * The maximum number of characters is ~8, but the maximum is not enforced.
 *
 * To be sent, both customValue and customLabel have to be set to non-nil values.
 */
@property (nonatomic, copy, nullable) NSString *customValue;

/**
 * Creates an update dictionary from the receiver, that can be used with
 * `-[PBWatch sportsAppUpdate:onSent:]`.
 *
 * You should prefer using `-[PBSportsUpdate updateWatch:completion:]`.
 *
 * @see -[PBWatch sportsAppUpdate:onSent:]
 */
@property (nonatomic, readonly) NSDictionary<NSNumber *, id> *appMessageDictionary;

/**
 * Sends an update to the watch.
 *
 * The method tries to send the minimal set of changes since the last time the
 * method was used, to try to minimize communication with the watch.
 *
 * @param watch The watch to send the update to.
 * @param completion Block that will be called when the update either succeeds
 *                   or fails.
 *
 *                   - `error`: `nil` if the operation was successful, or else an
 *                     `NSError` with more information on why it failed.
 */
- (void)updateWatch:(PBWatch *)watch completion:(void (^__nullable)(NSError *__nullable error))completion;

/**
 * Creates a formatted time string from a total seconds value, formatted as
 * "h:mm:ss".
 *
 * For example, supplying the value 3930.0f seconds will return @"1:05:30".
 *
 * @param seconds The number of seconds from which to create the time string.
 *
 * @return Formatted time as "h:mm:ss"
 */
+ (NSString *)timeStringFromSeconds:(NSTimeInterval)seconds;

/**
 * Creates a formatted decimal string with one decimal number.
 *
 * For example, supplying the value 13.42f will return @"13.4".
 *
 * @param decimal The decimal number to format as a string.
 *
 * @return The formatted decimal number.
 */
+ (NSString *)decimalStringFromFloat:(float)decimal;

@end


@interface PBWatch (Sports)

/**
 * Queries the watch whether Sports Messages are supported.
 *
 * Must be called from the main thread.
 *
 * @param fetchedBlock The block that will be called when the inquiry has
 *                     finished. The block will be called asynchronously
 *                     on the queue that was originally used when calling this
 *                     method.
 *
 *                     - `watch`: the recipient of the query.
 *                     - `isSportsSupported`: `YES` if Sports API is supported,
 *                       `NO` otherwise.
 */
- (void)sportsGetIsSupported:(void(^)(PBWatch *watch, BOOL isSportsSupported))fetchedBlock;

/**
 * Send a command to launch the sports app on the watch that the receiver represents.
 *
 * Must be called from the main thread, and before sportsAppSetMetric:onSent:
 * or sportsAppUpdate:onSent:.
 *
 * @param onSent The handler that will be called when the launch command has
 *               been sent or timed out (after 1.5 secs).
 *
 *               - `watch`: the recipient of the command.
 *               - `error`: `nil` if the operation was successful, or else an
 *                 `NSError` with more information on why it failed.
 */
- (void)sportsAppLaunch:(void(^ __nullable)(PBWatch *watch, NSError *__nullable error))onSent;

/**
 * Send a command to kill the sports app on the watch that the receiver represents.
 *
 * Must be called from the main thread.
 *
 * @param onSent The handler that will be called when the kill command has been
 *               sent or timed out (after 1.5 secs).
 *
 *               - `watch`: the recipient of the command.
 *               - `error`: nil if the operation was successful, or else an
 *                 `NSError` with more information on why it failed.
 */
- (void)sportsAppKill:(void(^ __nullable)(PBWatch *watch, NSError *__nullable error))onSent;

/**
 * Send a command to the sports app on the watch that the receiver represents,
 * to set the preferred unit system.
 *
 * Must be called from the main thread.
 *
 * @param unitSystem `PBUnitSystemMetric` to request metric units or
 *                   `PBUnitSystemImperial` to request imperial units.
 * @param onSent The handler that will be called when the unit command has been
 *               sent or timed out (after 1.5 secs).
 *
 *               - `watch`: the recipient of the command.
 *               - `error`: `nil` if the operation was successful, or else an
 *                 `NSError` with more information on why it failed.
 */
- (void)sportsAppSetUnitSystem:(PBUnitSystem)unitSystem onSent:(void(^ __nullable)(PBWatch *watch, NSError *__nullable error))onSent;

/**
 * Send a command to the sports app on the watch that the receiver represents,
 * to set the state of the sports activity. Currently only
 * `SportsAppActivityStateRunning` and `SportsAppActivityStatePaused` are
 * supported.
 *
 * Must be called from the main thread.
 *
 * @param state The new sports activity state
 * @param onSent The handler that will be called when the unit command has been
 *               sent or timed out (after 1.5 secs).
 *
 *               - `watch`: the recipient of the command.
 *               - `error`: `nil` if the operation was successful, or else an
 *                 `NSError` with more information on why it failed.
 */
- (void)sportsAppSetActivityState:(SportsAppActivityState)state onSent:(void(^ __nullable)(PBWatch *watch, NSError *__nullable error))onSent;

/**
 * Sends the update to the sports app on the watch that the receiver represents.
 *
 * Must be called from the main thread.
 *
 * The valid keys and values for the dictionary are the following:
 *
 * - `PBSportsTimeKey`: the string representing the time. The value must be an
 *   `NSString`. The maximum number of characters is about 8.
 * - `PBSportsDistanceKey`: the string representing the distance. The value must
 *   be an `NSString`. The maximum number of characters is about 5.
 * - `PBSportsDataKey`: the string representing the pace or the speed. The value
 *   must be an `NSString`. The maximum number of characters is about 5.
 * - `PBSportsActivityStateKey`: the state of the activity. The value must be an
 *   `NSNumber` created using +[NSNumber(stdint) pb_numberWithUint8:]. The value
 *    must be one of the values from the enum SportsAppActivityState.
 * - `PBSportsIsPaceKey`: whether the value sent in `PBSportsDataKey` is the
 *    pace (use value 1) or the speed (use value 0). You don't need to
 *    continously send this value. The value must be an `NSNumber` created using
 *   +[NSNumber(stdin) pb_numberWithUint8:].
 * - `PBSportsHeartBPMKey`: the current heart rate in beats per minute. The
 *   value must be an `NSNumber` created using
 *   +[NSNumber(stdin) pb_numberWithUint8:].
 * - `PBSportsCustomLabelKey`: the string to show as a custom label. The value
 *   must be an `NSString`. The maximum number of characters is about 10. The
 *   string will be transformed into upper case before being sent to the watch.
 * - `PBSportsCustomValueKey`: the string to show as a custom value. The value
 *   must be an `NSString`. The maximum number of characters is about 8.
 *
 * @param update The update to send.
 * @param onSent The handler that will be called when the unit command has been
 *               sent or timed out (after 1.5 secs).
 *
 *               - `watch`: the recipient of the command.
 *               - `error`: `nil` if the operation was successful, or else an
 *                 `NSError` with more information on why it failed.
 */
- (void)sportsAppUpdate:(NSDictionary *)update onSent:(void(^__nullable)(PBWatch *watch, NSError *__nullable error))onSent;

/**
 * Add a receive handler for incoming Sports updates that are send by the
 * Sports watch application.
 *
 * Must be called from the main thread.
 *
 * @param onReceive The block that will be called every time a new update
 *                  message arrives.
 *
 *                  - `watch`: The watch that has sent the update.
 *                  - `state`: The new sports activity state as set by the
 *                    watch.
 *
 * @return An opaque handle object representing the installed receive handler,
 *         that can be used in sportsAppRemoveUpdateHandler:.
 *
 * @see SportsAppActivityState
 * @see sportsAppRemoveUpdateHandler:
 */
- (id)sportsAppAddReceiveUpdateHandler:(BOOL(^)(PBWatch *watch, SportsAppActivityState state))onReceive;

/**
 * Removes a receive handler that was previously installed using
 * sportsAppAddReceiveUpdateHandler:.
 *
 * Must be called from the main thread.
 *
 * @param opaqueHandle The handle object as returned by
 *                     sportsAppAddReceiveUpdateHandler:
 *
 * @see sportsAppAddReceiveUpdateHandler:
 */
- (void)sportsAppRemoveUpdateHandler:(id)opaqueHandle;

/**
 * Assigns a custom title and icon to the sports app on the watch.
 *
 * Must be called from the main thread.
 *
 * @discussion It is recommended to perform this as the first call after
 *             sportsGetIsSupported: to avoid changing the title
 *             and icon while it is being displayed in the menu as to avoid
 *             confusion.
 *
 * @param title The custom title (max. 20 bytes of UTF-8 string)
 * @param icon The custom icon (max. 32x32 pixels, black/white only). This
 *             image cannot be `nil`.
 * @param onSent The handler that will be called when the title and icon have
 *               been set or timed out.
 *
 *               - `watch`: the recipient of the custom title and icon.
 *               - `error`: `nil` if the operation was successful, or else an
 *                 `NSError` with more information on why it failed.
 */
- (void)sportsSetTitle:(NSString *)title icon:(UIImage *)icon onSent:(void(^ __nullable)(PBWatch *watch, NSError *__nullable error))onSent;

@end


@interface PBSportsUpdate (Deprecated)

/**
 * General purpose data variable.
 *
 * @note The original property design is very broken and it has been deprecated
 *       in favor of both pace and speed. This value will act as pace from now
 *       on.
 *
 * The possible range is currently limited from -3599 to 3599,
 * inclusive (±59min 59sec). Values larger or smaller than the limits will be
 * transformed into the maximum or minimum, respectively.
 *
 * It will be presented as a duration string in the UI. Minutes and seconds will
 * be separated by colons. The decimal part will be discarded for the
 * presentation.
 *
 * Setting a value in either pace or speed will discard the value set through
 * data.
 *
 * @see -[PBWatch sportsAppSetLabel:onSent:]
 *
 * @deprecated Prefer either `pace` or `speed`.
 */
@property (nonatomic) float data __attribute__((deprecated("Prefer either `pace` or `speed`")));

/**
 * Creates a new `PBSportsUpdate` with the given time, distance and data.
 *
 * @param time The current time in seconds.
 * @param distance The current distance in kilometers or miles.
 * @param data General purpose data variable.
 *
 * @return A new `PBSportsUpdate` with the given time, distance and data.
 *
 * @deprecated Prefer -[PBSportsUpdate init] and filling the properties.
 */
+ (instancetype)updateWithTime:(NSTimeInterval)time distance:(float)distance data:(float)data __attribute__((deprecated("Prefer `[[PBSportsUpdate alloc] init]` and then filling the properties")));

/**
 * Creates an update dictionary from the receiver that can be used with
 * `-[PBWatch sportsAppUpdate:onSent:]`.
 *
 * @see -[PBWatch sportsAppUpdate:onSent:]
 *
 * @deprecated Prefer using -[PBSportsUpdate appMessageDictionary].
 */
- (NSDictionary *)dictionary __attribute__((deprecated("Prefer using `appMessageDictionary`")));

/**
 * Creates a formatted time string from a total seconds value, formatted as
 * "h:mm:ss".
 *
 * For example, supplying the value 3930.0f seconds will return @"1:05:30".
 *
 * @param seconds The number of seconds from which to create the time string.
 *
 * @return Formatted time as "h:mm:ss"
 *
 * @deprecated Prefer +[PBSportsUpdate timeStringFromSeconds:].
 */
+ (NSString *)timeStringFromFloat:(float)seconds __attribute__((deprecated("Prefer `+[PBSportsUpdate timeStringFromSeconds:]`")));

@end


@interface PBWatch (SportsDeprecated)

/**
 * Send a command to the sports app on the watch that the receiver represents,
 * to set the preferred data label (either PACE or SPEED) and corresponding
 * units.
 *
 * Must be called from the main thread.
 *
 * @param isPace `YES` to request the pace label or `NO` to request the speed
 *               label.
 * @param onSent The handler that will be called when the unit command has been
 *               sent or timed out (after 1.5 secs).
 *
 *               - `watch`: the recipient of the command.
 *               - `error`: `nil` if the operation was successful, or else an
 *                 `NSError` with more information on why it failed.
 *
 * @deprecated Prefer using [PBSportsUpdate pace] or [PBSportsUpdate speed].
 */
- (void)sportsAppSetLabel:(BOOL)isPace onSent:(void(^ __nullable)(PBWatch *watch, NSError *__nullable error))onSent __attribute__((deprecated("Prefer using `[PBSportsUpdate pace]` or `[PBSportsUpdate speed]`")));

/**
 * Send a command to the sports app on the watch that the receiver represents,
 * to set the preferred unit system, either metric or imperial.
 *
 * Must be called from the main thread.
 *
 * @param isMetric `YES` to request metric units or `NO` to request imperial
 *                 units.
 * @param onSent The handler that will be called when the unit command has been
 *               sent or timed out (after 1.5 secs).
 *
 *               - `watch`: the recipient of the command.
 *               - `error`: `nil` if the operation was successful, or else an
 *                 `NSError` with more information on why it failed.
 *
 * @deprecated Prefer using [PBWatch(Sports) sportsAppSetUnitSystem:onSent:]
 */
- (void)sportsAppSetMetric:(BOOL)isMetric onSent:(void(^ __nullable)(PBWatch *watch, NSError *__nullable error))onSent __attribute__((deprecated("Prefer using `[PBWatch sportsAppSetUnitSystem:onSent:]`")));

@end

NS_ASSUME_NONNULL_END
