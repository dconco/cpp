#include "loader.h"
#include "../logic/api.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

// Function types that match our API
using InitializeFunc = void(*)();
using UpdateFunc = void(*)(float);
using ShutdownFunc = void(*)();

int main() {
    std::cout << "Hot Reload Demo" << std::endl;
    std::cout << "===============" << std::endl;
    std::cout << "Watching for changes to app_logic.dll..." << std::endl;
    std::cout << "Make changes to your library and recompile to see hot reloading in action!" << std::endl;
    
    // Create our library loader
    LibraryLoader loader("app_logic");
    
    // Load the initial version of the library
    if (!loader.Load()) {
        std::cerr << "Failed to load initial library" << std::endl;
        return 1;
    }
    
    // Get function pointers
    auto initialize = loader.GetFunction<InitializeFunc>("Initialize");
    auto update = loader.GetFunction<UpdateFunc>("Update");
    auto shutdown = loader.GetFunction<ShutdownFunc>("Shutdown");
    
    if (!initialize || !update || !shutdown) {
        std::cerr << "Failed to load required functions" << std::endl;
        return 1;
    }
    
    // Initialize the library
    initialize();
    
    // Main loop
    bool running = true;
    auto lastTime = std::chrono::high_resolution_clock::now();
    
    while (running) {
        // Calculate delta time
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        // Check for library changes
        if (loader.CheckForChanges()) {
            std::cout << "Detected changes to library. Hot reloading..." << std::endl;
            
            // Shutdown current library
            shutdown();
            
            // Reload library
            if (loader.Reload()) {
                // Get new function pointers
                initialize = loader.GetFunction<InitializeFunc>("Initialize");
                update = loader.GetFunction<UpdateFunc>("Update");
                shutdown = loader.GetFunction<ShutdownFunc>("Shutdown");
                
                if (!initialize || !update || !shutdown) {
                    std::cerr << "Failed to load required functions after reload" << std::endl;
                    break;
                }
                
                // Re-initialize with the new code
                initialize();
            }
        }
        
        // Update with current library
        update(deltaTime);
        
        // Simulate frame time
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Handle exit condition (for this example, run for a limited time)
        static int frameCount = 0;
        if (++frameCount > 10000) {  // Run for about 16.6 minutes
            running = false;
        }
    }
    
    // Shutdown
    shutdown();
    
    return 0;
}