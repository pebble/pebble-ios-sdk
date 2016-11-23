//
//  ViewController.swift
//  PebbleKitExample
//
//  Created by Tintin on 9/15/15
//  Copyright (c) 2015 ACME. All rights reserved.
//

import UIKit
import PebbleKit

class ViewController: UIViewController, PBPebbleCentralDelegate {
    var pebbleCentral: PBPebbleCentral!
    var activeWatch: PBWatch?

    @IBOutlet weak var statusLabel: UILabel!

    struct Hole {
        var par: Int
        var score: Int
    }

    var holes: [Hole] = []
    var holeIndex = 0

    override func viewDidLoad() {
        super.viewDidLoad()
        pebbleCentral = PBPebbleCentral.default()
        holes = [
            Hole(par: 2, score: 0),
            Hole(par: 4, score: 0),
            Hole(par: 1, score: 0),
            Hole(par: 7, score: 0),
            Hole(par: 6, score: 0),
        ]
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        pebbleCentral.delegate = self
        pebbleCentral.run()
    }

    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        pebbleCentral.delegate = nil
    }

    func pebbleCentral(_ central: PBPebbleCentral, watchDidConnect watch: PBWatch, isNew: Bool) {
        print("Hello, \(watch.name)!")

        guard activeWatch == nil else { return }
        activeWatch = watch

        statusLabel.text = watch.name

        watch.golfAppAddReceiveUpdateHandler { [weak self] (_, command) -> Bool in
            guard let sself = self else { return false }

            switch (command) {
            case .previous:
                sself.holeIndex = self!.holeIndexStep(-1)
                break
            case .select:
                var hole = sself.holes[sself.holeIndex]
                hole.score += 1
                sself.holes[sself.holeIndex] = hole
            case .next:
                sself.holeIndex = self!.holeIndexStep(+1)
                break
            }

            sself.sendState()
            return true
        }

        watch.appMessagesLaunch { [weak self] _ in
            self?.sendState()
        }
    }

    func sendState() {
        guard let watch = activeWatch else { return }

        let previousHole = holes[holeIndexStep(-1)]
        let currentHole = holes[holeIndex]
        let nextHole = holes[holeIndexStep(+1)]

        let update = [
            PBGolfBackKey: String(previousHole.score),
            PBGolfMidKey: String(currentHole.score),
            PBGolfFrontKey: String(nextHole.score),
            PBGolfParKey: String(currentHole.par),
            PBGolfHoleKey: String(holeIndex)
        ]

        watch.golfAppUpdate(update) { (watch, error) -> Void in
            if let error = error {
                print(error)
            }
        }
    }

    func holeIndexStep(_ diff: Int) -> Int {
        var newIndex = holeIndex + diff

        while (newIndex < 0) {
            newIndex += holes.count
        }

        return newIndex % holes.count
    }

    func pebbleCentral(_ central: PBPebbleCentral, watchDidDisconnect watch: PBWatch) {
        print("Bye, \(watch.name)!")
        guard activeWatch == watch else { return }

        activeWatch = nil
        statusLabel.text = "No Pebble"
    }
}
