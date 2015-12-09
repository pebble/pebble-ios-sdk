# PebbleKit iOS [![GitHub release](https://img.shields.io/github/release/pebble/pebble-ios-sdk.svg)](https://github.com/pebble/pebble-ios-sdk/releases) [![Cocoapod](https://img.shields.io/cocoapods/v/PebbleKit.svg)](https://cocoapods.org/pods/PebbleKit) [![Carthage compatible](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)

Welcome to Pebble's official iOS SDK!

## Examples

All Pebble SDK examples are [available on GitHub](https://github.com/pebble-examples/pebblekit-ios-demos).

You can also run `pod try PebbleKit` to jump into a simple project right away.

## Integrating PebbleKit Using CocoaPods

- Install [CocoaPods](http://www.cocoapods.org) or make sure it is up to date
- Add a Podfile to your project if you don't have one already (Hint: use `pod init`).
- Add this line to the Podfile: `pod 'PebbleKit'`
- Run `pod install`

## Integrating PebbleKit Using Carthage

- Install [Carthage](https://github.com/Carthage/Carthage/releases) or make sure it is up to date
- Add Cartfile to your project if you don't have one already.
- Add this line to the Cartfile: `github "pebble/pebble-ios-sdk"`
- Run `carthage bootstrap`
- Drag `PebbleKit.framework` into your project

## Integrating PebbleKit Manually

- Drag `PebbleKit.framework` into your project
- Link `ExternalAccessory.framework` and `CoreBluetooth.framework`
- Add `-ObjC` linker flag to your project's build settings

## Configure `Info.plist`

- Add the value `com.getpebble.public` to the `UISupportedExternalAccessoryProtocols` ("Supported external accessory protocols") array
- (Optional) Add the following entries to the `UIBackgroundModes` ("Required background modes") array:
 - `bluetooth-peripheral` ("App shares data using CoreBluetooth")
 - `bluetooth-central` ("App communicates using CoreBluetooth")
 - `external-accessory` ("App communicates with an accessory")

## Xcode Documentation

You can browse the [latest documentation online](http://cocoadocs.org/docsets/PebbleKit) (and install an offline docset if you click on the icon on the top right).

Alternatively, manually install the docset from this folder:

- An Xcode docset is included with documentation about all public APIs
- Copy `PebbleKit-ios.docset` content into `~/Library/Developer/Shared/Documentation/DocSets`
- Restart Xcode. The documentation will now be available from `Help > Documentation and API Reference`

## Submitting iOS apps with PebbleKit to Apple's App Store

In order for Pebble to work with iPhones,
Pebble is part of the Made For iPhone program (a requirement for hardware accessories to interact with iOS apps). Unfortunately this also means that if you build an iOS app with PebbleKit,
Pebble will need to whitelist your iOS app before you can upload it to the App Store.
If you have completed a Pebble app and would like to learn more about making it available on the App Store,
please visit [the whitelisting guide](https://developer.getpebble.com/2/distribute/whitelisting.html)

## Change Log

#### 3.1.0

PebbleKit is now a *dynamic* framework.

If you want to support iOS `7.x` add `pod 'PebbleKit-Static'` to your `Podfile`.

- Added: Added workaround for Pebble 2.x / iOS 9 issue causing messages from watch not to arrive
- Added: DataLogging now works better in multi-app setups.
- Changed: DataLogging service is now created lazily when you try to use the API the first time
- Changed: DataLogging won't unannounce server when you have Background Modes set
- Changed: Lowered DeploymentTarget to 7.0 again
- Fixed: DataLogging poll wouldn't be triggered on app launch
- Fixed: `appMessagesRemoveUpdateHandler` not working as intended
- Deprecated: `dataLoggingService.pollForData` - use `pollForDataFromWatch:` instead
- Deprecated: `central.dataLoggingService` - use `dataLoggingServiceForAppUUID:` instead

#### 3.0.0

- Added: Support for *Pebble Time Round*
- Added: Support for 8K app messages
- Added: Support for Swift
- Added: Support for Bitcode
- Change: All `appUUID` properties are now `NSUUID` instead of `NSData`
- Change: As soon as you set the delegate and the appUUID you must call run the central before you'll get any connection events: `[[PBPebbleCentral defaultCentral] run]`
- Tip: Add `bluetooth-peripheral` and `bluetooth-central` to your `UIBackgroundModes` if your app should work while in the background
- Tip: No need to check for `lastConnectedWatch.isConnected` at app launch anymore - just wait for the event after you invoked `run`
- Tip: We removed `PebbleVendor.framework`. Keep it if you need it. Drop it otherwise to reduce the size of your app.

#### 2.4

- Changed: Automatic release on [GitHub](https://github.com/pebble/pebble-ios-sdk) and [Cocoapods](http://cocoapods.org/?q=pebble)

#### 2.3

- Removed: Bluetooth LE code from PebbleKit
- Changes: Improvements to data logging to help troubleshoot issues
- Removed: `PBWatch+PhoneVersion` and `PBWatch+Polling`
- Fixed: `PBWatch+Version` report the correct version
- Fixed: Crash when calling `-[PBNumber description]`
- Changed: Imports now are using`“HeaderName.h”` format (instead of `<PebbleKit/HeaderName.h>`)
- Fixed: Race-condition when sending data between phone and watch
- Fixed: Made `PebbleKit.podspec` pass most-recent CocoaPod linter
- Changed: Prefixed internally used logging classes to fix conflict when using *CocoaLumberjack* in your app
- Changed: Made existing logging more descriptive

#### 2.2

- Removed: `PBWatch+PhoneVersion`
- Fixed:`PBWatch+Version` reported the wrong version
- Fixed: Crash when calling `-[PBNumber description]`

#### 2.1

- Changed: Improvements to data-logging to help troubleshoot issues
