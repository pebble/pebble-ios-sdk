//
//  PBFirmwareMetadata.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 20/08/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import <PebbleKit/PBDefines.h>
#import <Foundation/Foundation.h>

@class PBFirmwareVersion;

/**
 *  Values specifying the Pebble hardware platform variant.
 */
typedef NS_ENUM(uint8_t, FirmwareMetadataPlatform) {
  FirmwareMetadataPlatformUnknown = 0,
  FirmwareMetadataPlatformPebbleOneEV1 = 1,
  FirmwareMetadataPlatformPebbleOneEV2 = 2,
  FirmwareMetadataPlatformPebbleOneEV2_3 = 3,
  FirmwareMetadataPlatformPebbleOneEV2_4 = 4,
  FirmwareMetadataPlatformPebbleOnePointFive = 5,
  FirmwareMetadataPlatformPebbleTwoPointZero = 6,
  FirmwareMetadataPlatformPebbleSnowyEVT2 = 7,
  FirmwareMetadataPlatformPebbleSnowyDVT = 8,
  FirmwareMetadataPlatformPebbleBobbySmilesPVT = 10,
  FirmwareMetadataPlatformPebbleOneBigboard = 0xff,
  FirmwareMetadataPlatformPebbleOneBigboard2 = 0xfe,
  FirmwareMetadataPlatformPebbleSnowyBigboard = 0xfd,
  FirmwareMetadataPlatformPebbleSnowyBigboard2 = 0xfc,
  FirmwareMetadataPlatformPebbleSpaldingEVT = 9,
  FirmwareMetadataPlatformPebbleSpalding = 11,
  FirmwareMetadataPlatformPebbleSpaldingBigboard = 0xfb,
};

NS_ASSUME_NONNULL_BEGIN

PB_EXTERN_CLASS @interface PBFirmwareMetadata : NSObject

/**
 *  The version of the firmware.
 *  @see PBFirmwareVersion
 */
@property (nonatomic, readonly) PBFirmwareVersion *version;

/**
 *  YES if the firmware is a recovery firmware, NO if it is a regular firmware.
 */
@property (nonatomic, readonly) BOOL isRecoveryFirmware;

/**
 *  The hardware platform variant with which the firmware is compatible.
 */
@property (nonatomic, readonly) FirmwareMetadataPlatform hardwarePlatform;

/**
 *  Converts a <FirmwareMetadataPlatform> value to a string.
 *  @param hardwarePlatform The hardware platform value to convert
 *  @return A string of the hardware platform
 */
+ (NSString*)hardwarePlatformToString:(FirmwareMetadataPlatform)hardwarePlatform;

/**
 *  Converts an NSString hardware platform string to the corresponding
 *  FirmwareMetadataPlatform value.
 *  @param hardwarePlatformString The string representing the hardware platform.
 *  @return The hardware platform enum value
 */
+ (FirmwareMetadataPlatform)stringToHardwarePlatform:(NSString *)hardwarePlatformString;

@end

NS_ASSUME_NONNULL_END
