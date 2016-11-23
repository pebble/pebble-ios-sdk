//
//  PebbleKit.h
//  PebbleKit
//
//  Created by Martijn Thé on 4/24/12.
//  Copyright (c) 2012 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for PebbleKit.
FOUNDATION_EXPORT double PebbleKitVersionNumber;

//! Project version string for PebbleKit.
FOUNDATION_EXPORT const unsigned char PebbleKitVersionString[];

#import <PebbleKit-Static/PBFirmwareVersion.h>

#import <PebbleKit-Static/PBWatch.h>
#import <PebbleKit-Static/PBWatch+AppMessages.h>
#import <PebbleKit-Static/PBWatch+Golf.h>
#import <PebbleKit-Static/PBWatch+Legacy.h>
#import <PebbleKit-Static/PBWatch+Ping.h>
#import <PebbleKit-Static/PBWatch+Sports.h>
#import <PebbleKit-Static/PBWatch+Version.h>

#import <PebbleKit-Static/PBPebbleCentral.h>
#import <PebbleKit-Static/PBPebbleCentral+DefaultCentral.h>

#import <PebbleKit-Static/PBBitmap.h>
#import <PebbleKit-Static/PBDataLoggingService.h>
#import <PebbleKit-Static/PBErrors.h>

#import <PebbleKit-Static/NSNumber+stdint.h>
#import <PebbleKit-Static/NSDictionary+Pebble.h>

#pragma mark - Legacy behavior
#import <PebbleKit-Static/PBFirmwareVersion+Legacy.h>
#import <PebbleKit-Static/PBPebbleCentral+Legacy.h>
