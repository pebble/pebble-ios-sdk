//
//  PBVersionInfo.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 20/08/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import <PebbleKit/PBDefines.h>
#import <Foundation/Foundation.h>

#import <PebbleKit/PBFirmwareVersion.h>
#import <PebbleKit/PBFirmwareMetadata.h>
#import <PebbleKit/PBResourceMetadata.h>


typedef NS_OPTIONS(NSUInteger, PBRemoteProtocolCapabilitiesFlags) {
  PBRemoteProtocolCapabilitiesFlagsAppRunState                 = 1 << 0,
  PBRemoteProtocolCapabilitiesFlagsInfiniteLogDumping          = 1 << 1, // unused
  PBRemoteProtocolCapabilitiesFlagsUpdateMusicProtocol         = 1 << 2, // unused
  PBRemoteProtocolCapabilitiesFlagsExtendedNotificationService = 1 << 3, // unused
  PBRemoteProtocolCapabilitiesFlagsLanguagePacksSupported      = 1 << 4, // unused
  PBRemoteProtocolCapabilitiesFlagsAppMessage8kSupported       = 1 << 5,
  PBRemoteProtocolCapabilitiesFlagsDismissFromPhoneSupported   = 1 << 6,
  PBRemoteProtocolCapabilitiesFlagsThirdPartyVoiceSupported    = 1 << 7,
};


NS_ASSUME_NONNULL_BEGIN

/**
 *  An instance of PBVersionInfo describes all the different system software (Pebble OS)
 *  on a Pebble watch and other auxiliary information.
 *  @see PBWatch
 */
PB_EXTERN_CLASS @interface PBVersionInfo : NSObject

/**
 *  The metadata of the firmware that is running.
 */
@property (nonatomic, readonly, strong) PBFirmwareMetadata *runningFirmwareMetadata;

/**
 *  The metadata of the recovery firmware that is in storage.
 */
@property (nonatomic, readonly, strong) PBFirmwareMetadata *recoveryFirmwareMetadata;

/**
 *  The metadata of the system resources.
 */
@property (nonatomic, readonly, strong) PBResourceMetadata *systemResources;

/**
 *  The version of the bootloader.
 */
@property (nonatomic, readonly) UInt32 bootloaderVersion;

/**
 *  The version of the hardware.
 */
@property (nonatomic, readonly, strong) NSString *hardwareVersion;

/**
 *  The serial number.
 */
@property (nonatomic, readonly, strong) NSString *serialNumber;

/**
 *  The current Bluetooth device address.
 */
@property (nonatomic, readonly, strong) NSData *deviceAddress;

/**
 *  Flags for the supported protocol features of the watch.
 */
@property (nonatomic, readonly, assign) PBRemoteProtocolCapabilitiesFlags remoteProtocolCapabilitiesFlags;

/**
 *  Indicates if the previous connection for the watch was to this device.
 *
 *  If the watch has been connected to this device, but connects to other
 *  device before connecting again to this device, the value will be YES.
 */
@property (nonatomic, readonly, assign) BOOL hasBeenUnfaithful;

/**
 *  YES if valid recovery firmware is installed, NO if not.
 */
- (BOOL)hasRecoveryFirmware;

/**
 *  YES if valid system resources are installed, NO if not.
 */
- (BOOL)hasSystemResources;

@end

NS_ASSUME_NONNULL_END
