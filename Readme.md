# PebbleKit iOS

Welcome to Pebble's official iOS SDK!

## Examples

All Pebble SDK examples are now available on GitHub at https://github.com/pebble/pebble-sdk-examples, please look into the `weather-demo`, `sports-demo`, and `golf-demo` folder for iOS sample code.

## Integrating PebbleKit using CocoaPods

- Install [CocoaPods](http://www.cocoapods.org) or make sure it is up to date
- Add a Podfile to your project if you don't have one already (Hint: use `pod init`).
- Add this line to the Podfile: `pod 'PebbleKit'`
- Run `pod install`

## Integrating PebbleKit Manually

- Drag PebbleKit.framework into project
- Drag in PebbleVendor.framework into the project, or, drag the PebbleVendor.xcodeproj into project if you need to control the 3rd party components needed for PebbleKit.
- Link ExternalAccessory.framework, libz.dylib, CoreBluetooth.framework, CoreMotion.framework and MessageUI.framework
- Add "-ObjC" linker flag to your project's build settings
- Add the value "com.getpebble.public" to the "Supported external accessory protocols" (UISupportedExternalAccessoryProtocols) array in your app's Info.plist
- Optionally, add the value "App communicates with an accessory" (external-accessory) to the "Required background modes" (UIBackgroundModes) array in your app's Info.plist


## Xcode Documentation

You can browser the latest documentation online at http://cocoadocs.org/docsets/PebbleKit and install an offline docset if you click on the icon on the top right.

Alternatively, manually install the docset from this folder:

- An Xcode docset is included with documentation about all public APIs.
- Copy `PebbleKit-ios.docset` content into `~/Library/Developer/Shared/Documentation/DocSets`
- Restart Xcode. The documentation will now be available from `Help > Documentation and API Reference`

## Submitting iOS apps with PebbleKit to Apple's App Store

In order for Pebble to work with iPhones, Pebble is part of the Made For iPhone program (a requirement for hardware accessories to interact with iOS apps). Unfortunately this also means that if you build an iOS app with PebbleKit, we (Pebble) will need to whitelist your iOS app before you can upload it to the App Store. If you have completed a Pebble app and would like to learn more about making it available on the App Store, please visit [the whitelisting guide](https://developer.getpebble.com/2/distribute/whitelisting.html)

## Change Log

#### 2.4

- Automatic release on [GitHub](https://github.com/pebble/pebble-ios-sdk) and [Cocoapods](http://cocoapods.org/?q=pebble)

#### 2.3

- Removed Bluetooth LE code from PebbleKit
- Improvements to data logging to help troubleshoot issues
- Removed PBWatch+PhoneVersion and +Polling
- Made PBWatch+Version report the correct version
- Fixed a crash when calling PBNumber description
- Changed imports from <PebbleKit/HeaderName.h> to “HeaderName.h” format
- Fixed on rare race-condition when sending data between phone and watch
- Made PebbleKit.podspec pass most-recent CocoaPod linter
- Prefixed internally used logging classes to fix conflict when using CocoaLumberjack in your app
- Made existing logging more descriptive

#### 2.2
- Removed PBWatch+PhoneVersion (moved to PebblePrivateKit)
- Make PBWatch+Version report the correct version
- Fixed a crash when calling PBNumber description

#### 2.1
- Some improvements to datalogging to help troubleshoot issues
