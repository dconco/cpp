#pragma once

#include "api.h"

// Define APP_LOGIC_EXPORTS when building the DLL
#define APP_LOGIC_EXPORTS

class AppLogic {
public:
    // Structure to maintain state across reloads
    struct State {
        int counter = 0;
        // Add any other state variables you want to persist across reloads
    };

    // Static state that persists between reloads
    static State s_state;

    static void Init() {
        // Initialize your logic here
    }

    static void Update(float deltaTime) {
        // Update your game/app logic here
        s_state.counter++;
        std::cout << "Logic update: counter = " << s_state.counter 
                  << ", deltaTime = " << deltaTime << std::endl;
    }

    static void Shutdown() {
        // Cleanup code here
    }
};