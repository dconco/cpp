#pragma once

#ifdef APP_LOGIC_EXPORTS
    #define API_EXPORT __declspec(dllexport)
#else
    #define API_EXPORT __declspec(dllimport)
#endif

// Version function to check if library has been reloaded
extern "C" API_EXPORT int GetLibraryVersion();

// Your app's actual API functions
extern "C" API_EXPORT void Initialize();
extern "C" API_EXPORT void Update(float deltaTime);
extern "C" API_EXPORT void Shutdown();