//
//  exampleApp.swift
//  example
//
//  Created by Antonio Ramar Collins on 3/10/25.
//

import SwiftUI

@main
struct exampleApp: App {
    let persistenceController = PersistenceController.shared

    var body: some Scene {
        WindowGroup {
            ContentView()
                .environment(\.managedObjectContext, persistenceController.container.viewContext)
        }
    }
}
