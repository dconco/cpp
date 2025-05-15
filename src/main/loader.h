class LibraryLoader {
public:
    LibraryLoader(const std::string& libraryName);
    ~LibraryLoader();

    bool Load();
    bool Unload();
    bool CheckForChanges();
    bool Reload();

    template<typename T>
    T GetFunction(const std::string& funcName) {
        if (!m_hModule) return nullptr;
        return reinterpret_cast<T>(GetProcAddress(m_hModule, funcName.c_str()));
    }

private:
    std::string m_libraryName;
    std::string m_libraryPath;
    HMODULE m_hModule;
    std::filesystem::file_time_type m_lastWriteTime;
    int m_currentVersion;

    bool CopyToTempAndLoad();
    std::filesystem::file_time_type GetLastWriteTime();
};