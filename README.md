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

- Copy `PebbleKit.framework` somewhere in your project folder.
- On your application target “General” settings tab, in the “Linked Frameworks and Libraries” section, drag and drop `PebbleKit.framework`.
- Link `CoreBluetooth.framework`.
- Add `-ObjC` linker flag to your project's build settings.

Additionally, since `PebbleKit.framework` is compiled for both the device and the simulator, when you upload your app to iTunes Connect, it might be rejected. To avoid this, you need to strip the simulator architectures from the binary before submitting. You can do this in many ways, but we will recommend using Carthage for simplicity:

- Install [Carthage](https://github.com/Carthage/Carthage/releases) or make sure it is up to date
- On your application target “Build Phases” settings tab, click the “+” icon and choose “New Run Script Phase”. Create a Run Script with the following contents:

  ```sh
  /usr/local/bin/carthage copy-frameworks
  ```

  and add the paths to the framework under “Input Files”, e.g.:

  ```
  $(SRCROOT)/path/to/PebbleKit.framework
  ```

## Integrating with PebbleKit-Static

PebbleKit-Static provides compatibility with iOS 7. We recommend you using PebbleKit, but if you need to provide versions of your app for older iOS version, you can still use this.

You can use PebbleKit-Static either using Cocoapods or manually. Carthage only supports dynamic frameworks, so PebbleKit-Static is not available for Carthage.

Additionally, in every point of the documentation that uses `#import <PebbleKit/PebbleKit.h>` you should use instead `#import <PebbleKit-Static/PebbleKit.h>`.

### Using CocoaPods

- Install [CocoaPods](http://www.cocoapods.org) or make sure it is up to date.
- Add a Podfile to your project if you don’t have one already (Hint: use `pod init`).
- Add this line to the Podfile: `pod 'PebbleKit-Static'`
- Run `pod install`

### Manually

- Copy `PebbleKit-Static.framework` somewhere in your project folder.
- On your application target “General” settings tab, in the “Linked Frameworks and Libraries” section, drag and drop `PebbleKit-Static.framework`.
- Link `CoreBluetooth.framework`.
- Add `-ObjC` linker flag to your project's build settings.

## Configure `Info.plist` and capabilities

If you want your app to communicate with the Pebble while in the background, you will need to add background modes to your app target `Info.plist`:

- Add the following entries to the `UIBackgroundModes` ("Required background modes") array:
 - `bluetooth-peripheral` ("App shares data using CoreBluetooth")
 - `bluetooth-central` ("App communicates using CoreBluetooth")

If you use background modes you also need to update your target's `Capabilities` in Xcode. Enable `Background Modes` and select:

- Uses Bluetooth LE accessories
- Acts as a Bluetooth LE accessory

If you are compiling in Xcode 8 or greater, you must additionally add the following key `Info.plist` (and it is recommended that you do so in older versions):

- `NSBluetoothPeripheralUsageDescription` (“Privacy - Bluetooth Peripheral Usage Description”)

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

#### 4.0.0

- Added: Support for Pebble 2.
- Added: New superclass `PBSemanticVersion`. `PBFirmwareVersion` is now a subtype of `PBSemanticVersion`.
- Added: New values `SendTextSupported`, `NotificationsFilteringSupported`, `UnreadCoredumpSupport`, and `WeatherApp2` in `PBRemoteProtocolCapabilitiesFlags`.
- Added: `PBPebbleKitLogging` type to customize the logging callback used by PebbleKit and the log level.
- Changed: Remove outdated documentation for `PBWatch`. Improved documentation about `-[PBWatch friendlyDescription]`.
- Changed: Clean up the `PBDataLoggingService` header. Use modern type names and improve nullability annotations.
- Changed: Added nullability annotations to `NSDictionary+Pebble.h`. Deprecated old methods without `pb_` prefix and added alternative methods with `pb_` prefixes instead.
- Changed: Added nullability annotations to `NSNumber+stdint.h`. Deprecated old methods without `pb_` prefix and added alternative methods with `pb_`.
- Changed: Deprecated method for setting the default log level in `PBPebbleCentral` in favor of the new methods in `PBPebbleKitLogging`.
- Changed: Communication with the watches (both through Classic and through LE) will not longer happen in the main thread. The callbacks will still be invoked in the main thread, and many methods are still documented as needed to be called from the main thread. We might lift those restrictions in the future, but they are still in place.
- Changed: Clean up the Sports API and document and improve `PBSportUpdate` helper object.
- Fixed: PebbleKit-Static uses the right header paths for Cocoapods.
- Fixed: PebbleKit-Static is stripped of its debugs symbols, which should avoid printing some warnings.
- Fixed: Golf and Sports do not need to add their UUID manually before using their APIs.
- Fixed: Added correct nullability annotations for `PBWatch (Golf)` and `PBWatch (Sports)`.
- Fixed: Signature of `appMessagesPushUpdate:withUUID:onSent:` no longer declares a non-nullable `NSError *` named `__nullableerror`.
- Fixed: Race condition that was making the communication with watch impossible.
- Fixed: `-[PBFirmwareVersion compare:]` was reporting the wrong results for firmwares released far in the future.
- Fixed: Connecting through Bluetooth LE should be more reliable.
- Fixed: Don’t try connecting with devices that are not Pebble.
- Fixed: Don’t try connecting with Pebble devices that are connected to other mobile devices.
- Fixed: Added correct nullability annotation for `PBVersionInfoCompletionBlock`.
- Fixed: Avoid crash while reconnecting to Bluetooth LE devices.
- Deprecated: `PBFirmwareVersion` `os`, `major`, and `minor`, as well as the convenience initializer `firmwareVersionWithOS:major:minor:suffix:commitHash:timestamp:` has been deprecated. Use instead `majorVersion`, `minorVersion`, `revisionVersion` and `firmwareVersionWithMajor:minor:revision:suffix:commitHash:timestamp:`.
- Removed: Support for Bluetooth Classic communication. Only Bluetooth LE is available. All devices in 3.x or later should be able to use Bluetooth LE, including the original Pebble and Pebble Steel. This should make communication from several third party apps a lot better.

#### 3.1.1

- Fixed: `-[PBPebbleCentral lastConnectedWatch]` is now properly marked as `nullable`.
- Fixed: Avoid watches not connecting to the phone in some infrequent scenarios.
- Fixed: When used from Objective-C++, `-[PBWatch isNew]` property doesn’t have the alias `new` to avoid problems with C++ reserved keywords.
- Fixed: Added Bitcode to the dynamic frameworks, so apps that wants to use Bitcode can submit properly.

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
