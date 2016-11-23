//
//  PBVersionInfo.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 20/08/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "PBDefines.h"
#import "PBFirmwareVersion.h"
#import "PBFirmwareMetadata.h"
#import "PBResourceMetadata.h"


typedef NS_OPTIONS(uint64_t, PBRemoteProtocolCapabilitiesFlags) {
  PBRemoteProtocolCapabilitiesFlagsAppRunState                      = 1 << 0,
  PBRemoteProtocolCapabilitiesFlagsInfiniteLogDumping               = 1 << 1, // unused
  PBRemoteProtocolCapabilitiesFlagsUpdateMusicProtocol              = 1 << 2, // unused
  PBRemoteProtocolCapabilitiesFlagsExtendedNotificationService      = 1 << 3, // unused
  PBRemoteProtocolCapabilitiesFlagsLanguagePacksSupported           = 1 << 4, // unused
  PBRemoteProtocolCapabilitiesFlagsAppMessage8kSupported            = 1 << 5,
  PBRemoteProtocolCapabilitiesFlagsInsightsSupport                  = 1 << 6,
  PBRemoteProtocolCapabilitiesFlagsThirdPartyVoiceSupported         = 1 << 7,
  PBRemoteProtocolCapabilitiesFlagsSendTextSupported                = 1 << 8,
  PBRemoteProtocolCapabilitiesFlagsNotificationsFilteringSupported  = 1 << 9,
  PBRemoteProtocolCapabilitiesFlagsUnreadCoredumpSupport            = 1 << 10, // unused
  PBRemoteProtocolCapabilitiesFlagsWeatherApp2                      = 1 << 11,
  PBRemoteProtocolCapabilitiesFlagsReminderApp                      = 1 << 12,
  PBRemoteProtocolCapabilitiesFlagsWorkoutApp                       = 1 << 13,
                                                                        // 14 not used in the FW
                                                                        // 15 not used in the FW
  PBRemoteProtocolCapabilitiesFlagsJSBytecodeVersionAppended        = 1 << 16,
};


NS_ASSUME_NONNULL_BEGIN

/**
 * An instance of PBVersionInfo describes all the different system software (Pebble OS)
 * on a Pebble watch and other auxiliary information.
 * @see PBWatch
 */
PB_EXTERN_CLASS @interface PBVersionInfo : NSObject

/**
 * The metadata of the firmware that is running.
 */
@property (nonatomic, readonly, strong, nullable) PBFirmwareMetadata *runningFirmwareMetadata;

/**
 * The metadata of the recovery firmware that is in storage.
 */
@property (nonatomic, readonly, strong, nullable) PBFirmwareMetadata *recoveryFirmwareMetadata;

/**
 * The metadata of the system resources.
 */
@property (nonatomic, readonly, strong) PBResourceMetadata *systemResources;

/**
 * The version of the bootloader.
 */
@property (nonatomic, readonly) UInt32 bootloaderVersion;

/**
 * The version of the hardware.
 */
@property (nonatomic, readonly, strong) NSString *hardwareVersion;

/**
 * The serial number.
 */
@property (nonatomic, readonly, strong) NSString *serialNumber;

/**
 * The current Bluetooth device address.
 */
@property (nonatomic, readonly, strong) NSData *deviceAddress;

/**
 * Flags for the supported protocol features of the watch.
 */
@property (nonatomic, readonly, assign) PBRemoteProtocolCapabilitiesFlags remoteProtocolCapabilitiesFlags;

/**
 * Indicates if the previous connection for the watch was to this device.
 *
 * If the watch has been connected to this device, but connects to other
 * device before connecting again to this device, the value will be YES.
 */
@property (nonatomic, readonly, assign) BOOL hasBeenUnfaithful;

/**
 * YES if valid recovery firmware is installed, NO if not.
 */
- (BOOL)hasRecoveryFirmware;

/**
 * YES if valid system resources are installed, NO if not.
 */
- (BOOL)hasSystemResources;

/**
 * YES if app messages are supported, NO if not.
 */
- (BOOL)appMessagesSupported;

@end

NS_ASSUME_NONNULL_END
