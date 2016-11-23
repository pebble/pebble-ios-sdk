//
//  PBFirmwareVersion.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 20/08/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PBDefines.h"
#import "PBSemanticVersion.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * PBFirmwareVersion is a helper class that is able to parse the versionTag string
 * into its components (major, minor, revision, suffix) and facilitate comparisons
 * between versions.
 *
 * Valid versions follow the following format:
 * `(v)MAJORVERSION(.MINORVERSION(.REVISIONVERSION(-SUFFIX)))`
 *
 * Where the fields MAJOR, MINOR, REVISION are positive, decimal integer numbers and SUFFIX
 * an arbitrary string. MINOR, REVISION, and SUFFIX are optional (nested optionality).
 *
 * Examples of valid versions:
 *
 * - `1`
 * - `v2`
 * - `v3.4-foo`
 * - `v4.1234.99-alpha-beta-gamma`
 */
PB_EXTERN_CLASS @interface PBFirmwareVersion : PBSemanticVersion <NSCopying>

/**
 * The version timestamp.
 *
 * The timestamp is in the final comparison equation, in the -compare: method,
 * after evaluating major, minor, and revision components.
 */
@property (nonatomic, readonly) uint32_t timestamp;

/**
 * The version's git commit hash.
 *
 * The commit hash is not used in the -compare: method.
 */
@property (nonatomic, readonly, copy, nullable) NSString * commitHash;

/**
 * The version's git tag.
 */
@property (nonatomic, readonly, copy) NSString *tag;

/**
 * Creates a PBFirmwareVersion object given a tag string.
 *
 * @param tag The firmware version string to parse.
 */
+ (nullable instancetype)firmwareVersionWithString:(NSString *)tag;

/**
 * Creates a PBFirmwareVersion object given a tag string and timestamp.
 *
 * @param tag The firmare version string to parse.
 * @param commitHash A version's commit hash. Can be nil.
 * @param timestamp The version timestamp.
 */
+ (nullable instancetype)firmwareVersionWithTag:(NSString *)tag
                                     commitHash:(nullable NSString *)commitHash
                                      timestamp:(uint32_t)timestamp;

/**
 * Creates a PBFirmwareVersion object given its components.
 *
 * The tag string will be set to the canonical format vMAJOR.MINOR.REVISION(-SUFFIX).
 *
 * @param major The version major number.
 * @param minor The version minor number.
 * @param revision The version revision number.
 * @param suffix The version suffix. Can be nil.
 * @param commitHash A version's commit hash. Can be nil.
 * @param timestamp The version timestamp.
 */
+ (instancetype)firmwareVersionWithMajor:(NSInteger)major
                                   minor:(NSInteger)minor
                                revision:(NSInteger)revision
                                  suffix:(nullable NSString *)suffix
                              commitHash:(nullable NSString *)commitHash
                               timestamp:(uint32_t)timestamp;

- (BOOL)isEqualVersionOnly:(PBSemanticVersion *)other;

@end

NS_ASSUME_NONNULL_END
