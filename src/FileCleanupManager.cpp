#include <windows.h>
#include <lmcons.h> // For UNLEN and MAX_PATH
#include <shlobj.h> // SHEmptyRecycleBin
#include <tchar.h>
#include <cstdlib> // required for system() function

#include <iostream>
#include <filesystem>

#include "FileCleanupManager.hpp"

// --- PUBLIC --- //
FileCleanupManager::FileCleanupManager() {}

void FileCleanupManager::initTerminal() {
    SetConsoleOutputCP(CP_UTF8); // UTF-8 support

    std::cout << "🏠 Welcome to File Cleanup Manager, " + this->getWindowsUsername() << std::endl;
    std::cout << "⚠️ Please make sure you run the .exe file as administrator!!!" << std::endl;
    std::cout << "⚙️ File Cleanup Manager for Windows v0.0.1-beta.1" << std::endl;
    std::cout << "💻 Developed by Okan Unal" << std::endl;
    std::cout << "📁 This project is open source. Github repo: https://github.com/OkanUnalll/file-cleanup-manager-windows" << std::endl;
    std::cout << "---------------------" << std::endl;
}

int FileCleanupManager::remove(std::string path) {
    if (remove(path) != 0) {
        std::cout << "✅ File Deleted" << std::endl;
    } else {
        std::cout << "❌ Unable to delete the file" << std::endl;
    }

    return 0;
}

void FileCleanupManager::clearLocalTemp() {
    if (this->getUserRootDir() == nullptr) {
        std::cerr << "❌ Error: Unable to user root directory" << std::endl;

        return;
    }

    // access the AppData/Local/Temp
    std::filesystem::path tempPath = std::filesystem::path(this->getUserRootDir()) / "AppData" / "Local" / "Temp";

    try {
        this->deleteDirectoryContents(tempPath);
        std::cout << "✅ Local Temp folder cleared" << std::endl;

        std::string path = "start " + tempPath.string();

        system(path.c_str());
    } catch (const std::exception& e) {
        std::cout << "❌ Error: " << e.what() << std::endl;
    }
}

void FileCleanupManager::clearWindowsTemp() {
    // access the Windows/Temp
    std::filesystem::path tempPath = std::filesystem::path("C:\\Windows\\Temp");

    try {
        this->deleteDirectoryContents(tempPath);
        std::cout << "✅ Windows Temp folder cleared" << std::endl;

        system("start C:\\Windows\\Temp");
    } catch (const std::exception& e) {
        std::cout << "❌ Error: " << e.what() << std::endl;
    }
}

void FileCleanupManager::clearWindowsSoftwareDistribution() {
    // Stop the Windows Update service
    std::cout << "Stopping the Windows Update service... (It will be restarted.)" << std::endl;
    system("net stop wuauserv");

    // Delete files in the Download folder
    std::cout << "Deleting files..." << std::endl;
    system("del /Q /S C:\\Windows\\SoftwareDistribution\\Download\\*");

    // Restart the Windows Update service
    std::cout << "Starting the Windows Update service..." << std::endl;
    system("net start wuauserv");

    std::cout << "✅ Erasing Windows Software Distribution junk files has been completed!" << std::endl;

    system("start C:\\Windows\\SoftwareDistribution\\Download");
}

void FileCleanupManager::clearWindowsPrefetch() {
    // access the Windows\Prefetch
    std::filesystem::path tempPath = std::filesystem::path("C:\\Windows\\Prefetch");

    try {
        this->deleteDirectoryContents(tempPath);
        std::cout << "✅ Windows Prefetch folder cleared" << std::endl;

        system("start C:\\Windows\\Prefetch");
    } catch (const std::exception& e) {
        std::cout << "❌ Error: " << e.what() << std::endl;
    }
}

void FileCleanupManager::clearRecycleBin() {
    std::cout << "Cleaning up..." << std::endl;

    // SHERB_NOCONFIRMATION: Cleans without asking the user for confirmation
    // SHERB_NOPROGRESSUI: Does not show a progress window
    // SHERB_NOSOUND: Sound does not play
    HRESULT result = SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND); 

    if (SUCCEEDED(result)) {
        std::cout << "✅ Recycle Bin Cleared" << std::endl;

        system("start shell:RecycleBinFolder");
    } else {
        std::cout << "❌ Unable to clear the Recycle Bin" << std::endl;
    }   
}

void FileCleanupManager::resetMicrosoftStoreCache() {
    std::cout << "Reseting Microsoft Store cache..." << std::endl;
    system("WSReset.exe");
    std::cout << "❔ Info: The Microsoft store application will open. After waiting for a while, you can close the application. The cache will be cleared." << std::endl;
}

void FileCleanupManager::deleteDirectoryContents(const std::filesystem::path& dir) {
    try {
        for (const auto& entry : std::filesystem::directory_iterator(dir)) {
            try {
                std::filesystem::remove_all(entry.path());  // clears folder contents
                std::cout << "✅ Deleted: " << entry.path() << std::endl;
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "⚠️ Unable to delete file: " << entry.path() << " - " << e.what() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::string FileCleanupManager::getWindowsUsername() {
    char username[UNLEN + 1];
    DWORD username_len = sizeof(username);

    if (GetUserNameA(username, &username_len)) {
        return std::string(username);
    } else {
        return std::string("❌ Error: Unable to get user name.");
    }
}

// gets the user root directory (example: C:/Users/<username>)
char* FileCleanupManager::getUserRootDir() {
    char* userProfile = getenv("USERPROFILE");
    return userProfile;
}