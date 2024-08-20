#include <iostream>

class FileCleanupManager {
public:
    // - CONSTRUCTOR
    FileCleanupManager();

    void initTerminal();

    void clearRecycleBin();

    void clearLocalTemp();

    void clearWindowsTemp();

    void clearWindowsSoftwareDistribution();

    void clearWindowsPrefetch();

    void resetMicrosoftStoreCache();

    void deleteDirectoryContents(const std::filesystem::path& dir);

    int remove(std::string path);

    std::string getWindowsUsername();

    char* getUserRootDir();
};
