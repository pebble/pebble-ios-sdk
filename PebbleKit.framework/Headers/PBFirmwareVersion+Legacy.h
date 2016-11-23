//
//  PBFirmwareVersion+Legacy.h
//  PebbleKit
//
//  Created by Mario Carranca on 2015-12-18.
//  Copyright © 2015 Pebble Technology. All rights reserved.
//

#import "PBFirmwareVersion.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * @note For legacy uses in which the legacy properties below are used, the version format is:
 *       `(v)OS(.MAJOR(.MINOR(-SUFFIX)))`
 */
@interface PBFirmwareVersion (Legacy)

/**
 * The OS version component.
 *
 * @deprecated Use [PBSemanticVersion majorVersion]
 */
@property (nonatomic, readonly) NSInteger os __attribute__((deprecated("Property deprecated. Use `majorVersion`")));

/**
 * The major version component.
 *
 * @note If a version tag string does not contain a major component, it will be set to 0.
 *
 * @deprecated Use [PBSemanticVersion minorVersion]
 */
@property (nonatomic, readonly) NSInteger major __attribute__((deprecated("Property deprecated. Use `minorVersion`")));

/**
 * The minor version component.
 *
 * @note If a version tag string does not contain a major component, it will be set to 0.
 *
 * @deprecated Use [PBSemanticVersion revisionVersion]
 */
@property (nonatomic, readonly) NSInteger minor __attribute__((deprecated("Property deprecated. Use `revisionVersion`")));

/**
 * Creates a PBFirmwareVersion object given its components.
 *
 * The tag string will be set to the canonical format vMAJOR.MINOR.REVISION(-SUFFIX).
 *
 * @param os The version major number.
 * @param major The version minor number.
 * @param minor The version revision number.
 * @param suffix The version suffix. Can be nil.
 * @param commitHash A version's commit hash. Can be nil.
 * @param timestamp The version timestamp.
 *
 * @deprecated Use +[PBFirmwareVersion firmwareVersionWithMajor:minor:revision:suffix:commitHash:timestamp:]
 */
+ (nullable instancetype)firmwareVersionWithOS:(NSInteger)os
                                         major:(NSInteger)major
                                         minor:(NSInteger)minor
                                        suffix:(nullable NSString *)suffix
                                    commitHash:(nullable NSString *)commitHash
                                     timestamp:(uint32_t)timestamp __attribute__((deprecated("Method deprecated. Use `firmwareVersionWithMajor:minor:revision:suffix:commitHash:timestamp:`")));

@end

NS_ASSUME_NONNULL_END
