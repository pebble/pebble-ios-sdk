//
//  AppDelegate.swift
//  PebbleKitExample
//
//  Created by Tintin on 9/15/15
//  Copyright (c) 2015 ACME. All rights reserved.
//

import UIKit
import PebbleKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
    var window: UIWindow?

    var pebbleCentral: PBPebbleCentral!

    func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
        pebbleCentral = PBPebbleCentral.defaultCentral()
        pebbleCentral.appUUID = PBGolfUUID
        
        // We don't run just yet.
        // Instead we wait for the ViewController to be presented.
        // pebbleCentral.run()
        
        return true
    }
}
