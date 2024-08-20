#include <iostream>
#include <stdio.h>
#include <filesystem>

#include "FileCleanupManager.hpp"

int main() {
    char answer;

    FileCleanupManager fcm = FileCleanupManager();

    fcm.initTerminal();

    do {
        std::cout << "💭 Clear the Local Temp Folder?" << std::endl;
        std::cout << "Target: " << fcm.getUserRootDir() << "\\AppData\\Local\\Temp\\*" << std::endl;
        std::cout << "Y (Clear) / N (Skip)" << std::endl;
        std::cin >> answer;

        switch (answer) {
            case 'Y':
                fcm.clearLocalTemp();
                std::cout << std::endl;
                break;
            case 'N':
                std::cout << std::endl;
                break;
            default:
                std::cout << "Invalid input" << std::endl;
    }
    } while (answer != 'Y' && answer != 'N');

    do {
        std::cout << "💭 Clear the Windows Temp Folder?" << std::endl;
        std::cout << "Target: C:/Windows/Temp/*" << std::endl;
        std::cout << "Y (Clear) / N (Skip)" << std::endl;
        std::cin >> answer;

        switch (answer) {
            case 'Y':
                fcm.clearWindowsTemp();
                std::cout << std::endl;
                break;
            case 'N':
                std::cout << std::endl;
                break;
            default:
                std::cout << "Invalid input" << std::endl;
    }
    } while (answer != 'Y' && answer != 'N');

    do {
        std::cout << "💭 Reset the Microsoft Store Cache?" << std::endl;
        std::cout << "Y (Clear) / N (Skip)" << std::endl;
        std::cin >> answer;

        switch (answer) {
            case 'Y':
                fcm.resetMicrosoftStoreCache();
                std::cout << std::endl;
                break;
            case 'N':
                std::cout << std::endl;
                break;
            default:
                std::cout << "Invalid input" << std::endl;
    }
    } while (answer != 'Y' && answer != 'N');

    do {
        std::cout << "💭 Clear the Windows Software Distribution files and folders?" << std::endl;
        std::cout << "Target: C:/Windows/SoftwareDistribution/Download/*" << std::endl;
        std::cout << "Y (Clear) / N (Skip)" << std::endl;
        std::cin >> answer;

        switch (answer) {
            case 'Y':
                fcm.clearWindowsSoftwareDistribution();
                std::cout << std::endl;
                break;
            case 'N':
                std::cout << std::endl;
                break;
            default:
                std::cout << "Invalid input" << std::endl;
    }
    } while (answer != 'Y' && answer != 'N');
    
    do {
        std::cout << "💭 Clear the Windows Prefetch Folder?" << std::endl;
        std::cout << "Target: C:/Windows/Prefetch/*" << std::endl;
        std::cout << "Y (Clear) / N (Skip)" << std::endl;
        std::cin >> answer;

        switch (answer) {
            case 'Y':
                fcm.clearWindowsPrefetch();
                std::cout << std::endl;
                break;
            case 'N':
                std::cout << std::endl;
                break;
            default:
                std::cout << "Invalid input" << std::endl;
    }
    } while (answer != 'Y' && answer != 'N');

    do {
        std::cout << "💭 Clear the Recycle Bin? Y (Clear) / N (Skip)" << std::endl;
        std::cin >> answer;

        switch (answer) {
        case 'Y':
            fcm.clearRecycleBin();
            std::cout << std::endl;
            break;
        case 'N':
            std::cout << std::endl;
            break;
        default:
            std::cout << "Invalid input" << std::endl;
    }
    } while (answer != 'Y' && answer != 'N');

    std::cout << "🎉 Cleanup completed!" << std::endl;

    return 0;
}