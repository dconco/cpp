#include "app_logic.h"
#include <iostream>

// Global version counter - increases when you recompile
static int g_LibraryVersion = 1;

// Keep track of application state
AppLogic::State AppLogic::s_state;

// Implementation of exported functions
int GetLibraryVersion() {
    return g_LibraryVersion;
}

void Initialize() {
    std::cout << "Library initialized (version " << g_LibraryVersion << ")" << std::endl;
    AppLogic::Init();
}

void Update(float deltaTime) {
    AppLogic::Update(deltaTime);
}

void Shutdown() {
    AppLogic::Shutdown();
    std::cout << "Library shut down" << std::endl;
}