//
//  PBFirmwareVersion.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 20/08/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PebbleKit/PBDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  PBFirmwareVersion is a helper class that is able to parse the versionTag string
 *  into its components (os, major, minor, suffix) and facilitate comparisons
 *  between versions.
 *  Valid versions follow the following format:
 *  `(v)OS(.MAJOR(.MINOR(-SUFFIX)))`
 *  Where the fields OS, MAJOR, MINOR are positive, decimal integer numbers and SUFFIX
 *  an arbitrary string. MAJOR, MINOR and SUFFIX are optional (nested optionality).
 *  Examples of valid versions:
 *  `1`
 *  `v2`
 *  `v3.4-foo`
 *  `v4.1234.99-alpha-beta-gamma`
 */
PB_EXTERN_CLASS @interface PBFirmwareVersion : NSObject <NSCopying>
/**
 *  The OS version component.
 */
@property (nonatomic, readonly) NSInteger os;

/**
 *  The major version component.
 *  @note If a version tag string does not contain a major component, it will be set to 0.
 */
@property (nonatomic, readonly) NSInteger major;

/**
 *  The minor version component.
 *  @note If a version tag string does not contain a major component, it will be set to 0.
 */
@property (nonatomic, readonly) NSInteger minor;

/**
 *  The release suffix, which is the part following the dash '-'.
 *  @note If a version tag string does not contain a suffix, it will be set to an empty string.
 *  @discussion The release suffix is not used in the -compare: method.
 */
@property (nonatomic, readonly, copy) NSString *suffix;

/**
 *  The version timestamp.
 *  @note The timestamp is in the final comparison equation, in the -compare: method, after evaluating
 *  os, major and minor components.
 */
@property (nonatomic, readonly) UInt32 timestamp;

/**
 *  The version's git commit hash.
 *  @discussion The commit hash is not used in the -compare: method.
 */
@property (nonatomic, readonly, copy) NSString * __nullable commitHash;

/**
 *  The version's git tag.
 */
@property (nonatomic, readonly, copy) NSString *tag;

/**
 *  Creates a PBFirmwareVersion object given a tag string.
 */
+ (PBFirmwareVersion *)firmwareVersionWithString:(NSString *)string;

/**
 *  Creates a PBFirmwareVersion object given a tag string and timestamp.
 */
+ (PBFirmwareVersion*)firmwareVersionWithTag:(NSString*)tag commitHash:(NSString * __nullable)commitHash timestamp:(UInt32)timestamp;

/**
 *  Creates a PBFirmwareVersion object given its components.
 *  @discussion The tag string will be set to the canonical format vOS.MINOR.MAJOR(-SUFFIX).
 */
+ (PBFirmwareVersion*)firmwareVersionWithOS:(NSInteger)os major:(NSInteger)major minor:(NSInteger)minor suffix:(NSString * __nullable)suffix commitHash:(NSString * __nullable)commitHash timestamp:(UInt32)timestamp;

/**
 *  Compares the receiver to another version object.
 *  @param aVersion The version to compare with the receiver.
 *  @return NSOrderedAscending if the value of aVersion is greater than the receiver’s,
 *  NSOrderedSame if they’re equal, and NSOrderedDescending if the value of aVersion is less than the receiver’s.
 */
- (NSComparisonResult)compare:(PBFirmwareVersion *)aVersion;

/**
 *  Convenience wrappers around -compare:
 */
- (BOOL)isEqualOrNewer:(PBFirmwareVersion *)other;
- (BOOL)isNewer:(PBFirmwareVersion *)other;
- (BOOL)isEqualVersionOnly:(PBFirmwareVersion *)other;

@end

NS_ASSUME_NONNULL_END
