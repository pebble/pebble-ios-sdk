Pod::Spec.new do |s|
  s.name         = "PebbleKit"
  s.version      = "2.4"
  s.summary      = "Embed PebbleKit iOS into your app to communicate with Pebble"
  s.homepage     = "https://github.com/pebble/pebble-ios-sdk"
  s.license      = {
    :type => 'Commercial',
    :text => <<-LICENSE
              © 2014 Pebble Technology Corp. All rights reserved.
    LICENSE
  }
  s.author       = { "Pebble Technology Corp." => "devsupport@getpebble.com" }
  s.source       = { :git => "https://github.com/pebble/pebble-ios-sdk.git", :tag => s.version }
  s.platform     = :ios, '6.0'

  s.preserve_paths = "PebbleKit.framework", "PebbleVendor.framework"
  s.vendored_frameworks = "PebbleKit.framework", "PebbleVendor.framework"
  s.public_header_files = "PebbleKit.framework/Versions/A/Headers/*.h"  # CocoaDocs doesn't follow symlinks
  s.weak_frameworks = 'ExternalAccessory', 'CoreBluetooth', 'CoreMotion', 'MessageUI'
  s.libraries = 'z'
  s.requires_arc = true
end
