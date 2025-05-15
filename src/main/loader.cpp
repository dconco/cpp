#include "loader.h"
#include <iostream>
#include <filesystem>
#include <thread>

namespace fs = std::filesystem;

LibraryLoader::LibraryLoader(const std::string& libraryName) 
    : m_libraryName(libraryName), m_hModule(NULL), m_currentVersion(0) {
    
    m_libraryPath = "./" + m_libraryName + ".dll";
    m_lastWriteTime = GetLastWriteTime();
}

LibraryLoader::~LibraryLoader() {
    Unload();
}

bool LibraryLoader::Load() {
    return CopyToTempAndLoad();
}

bool LibraryLoader::Unload() {
    if (m_hModule) {
        FreeLibrary(m_hModule);
        m_hModule = NULL;
        return true;
    }
    return false;
}

bool LibraryLoader::CheckForChanges() {
    auto currentWriteTime = GetLastWriteTime();
    return currentWriteTime != m_lastWriteTime;
}

bool LibraryLoader::Reload() {
    // Give the compiler some time to finish writing the file
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Unload current library
    Unload();
    
    // Try to load the new version
    if (!CopyToTempAndLoad()) {
        std::cerr << "Failed to reload library" << std::endl;
        return false;
    }
    
    // Get new version
    auto GetLibraryVersionFunc = GetFunction<int(*)()>("GetLibraryVersion");
    if (GetLibraryVersionFunc) {
        int newVersion = GetLibraryVersionFunc();
        std::cout << "Hot reloaded library: version changed from " 
                  << m_currentVersion << " to " << newVersion << std::endl;
        m_currentVersion = newVersion;
    }
    
    m_lastWriteTime = GetLastWriteTime();
    return true;
}

bool LibraryLoader::CopyToTempAndLoad() {
    // We'll create a unique temp file name
    std::string tempLibPath = m_libraryName + "_temp_" + 
        std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ".dll";
    
    try {
        // Copy to temp location so we don't lock the original file
        if (fs::exists(m_libraryPath)) {
            fs::copy_file(m_libraryPath, tempLibPath, fs::copy_options::overwrite_existing);
        } else {
            std::cerr << "Library file not found: " << m_libraryPath << std::endl;
            return false;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Failed to copy library: " << e.what() << std::endl;
        return false;
    }
    
    // Load the DLL
    m_hModule = LoadLibraryA(tempLibPath.c_str());
    if (!m_hModule) {
        std::cerr << "Failed to load library: " << GetLastError() << std::endl;
        return false;
    }
    
    // Get version
    auto GetLibraryVersionFunc = GetFunction<int(*)()>("GetLibraryVersion");
    if (GetLibraryVersionFunc) {
        m_currentVersion = GetLibraryVersionFunc();
    }
    
    return true;
}

std::filesystem::file_time_type LibraryLoader::GetLastWriteTime() {
    try {
        if (fs::exists(m_libraryPath)) {
            return fs::last_write_time(m_libraryPath);
        }
    } catch (const fs::filesystem_error&) {
        // Ignore errors
    }
    return fs::file_time_type::min();
}