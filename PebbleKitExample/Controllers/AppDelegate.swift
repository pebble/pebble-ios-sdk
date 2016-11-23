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

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        pebbleCentral = PBPebbleCentral.default()
        pebbleCentral.appUUID = PBGolfUUID as UUID
        
        // We don't run just yet.
        // Instead we wait for the ViewController to be presented.
        // pebbleCentral.run()
        
        return true
    }
}
