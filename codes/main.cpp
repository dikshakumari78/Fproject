#include <iostream>
#include "FileExplorer.h"
#include "Logger.h"

int main() {
    Logger logger("file_explorer.log");
    FileExplorer explorer(logger);
    int choice;
    std::string path, src, dest, filename;
    int permissions;

    do {
        std::cout << "\nCurrent Directory: " << std::filesystem::current_path() << std::endl;
        std::cout << "File Explorer Options:\n";
        std::cout << "1. List Files in Directory\n";
        std::cout << "2. Copy File\n";
        std::cout << "3. Move File\n";
        std::cout << "4. Delete File\n";
        std::cout << "5. Create File\n";
        std::cout << "6. Search File\n";
        std::cout << "7. Set File Permissions\n";
        std::cout << "8. Change Directory\n";
        std::cout << "9. Go Up One Directory\n";
        std::cout << "10. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter directory path: ";
                std::cin >> path;
                explorer.listFiles(path);
                break;

            case 2:
                std::cout << "Enter source file name: ";
                std::cin >> src;
                std::cout << "Enter destination file name: ";
                std::cin >> dest;
                if (explorer.copyFile(src, dest)) {
                    std::cout << "File copied successfully.\n";
                } else {
                    std::cout << "File copy failed.\n";
                }
                break;

            case 3:
                std::cout << "Enter source file name: ";
                std::cin >> src;
                std::cout << "Enter destination file name: ";
                std::cin >> dest;
                if (explorer.moveFile(src, dest)) {
                    std::cout << "File moved successfully.\n";
                } else {
                    std::cout << "File move failed.\n";
                }
                break;

            case 4:
                std::cout << "Enter file name to delete: ";
                std::cin >> path;
                if (explorer.deleteFile(path)) {
                    std::cout << "File deleted successfully.\n";
                } else {
                    std::cout << "File delete failed.\n";
                }
                break;

            case 5:
                std::cout << "Enter file name to create: ";
                std::cin >> path;
                if (explorer.createFile(path)) {
                    std::cout << "File created successfully.\n";
                } else {
                    std::cout << "File creation failed.\n";
                }
                break;

            case 6:
                std::cout << "Enter file name to search: ";
                std::cin >> filename;
                if (explorer.searchFile(filename)) {
                    std::cout << "File found.\n";
                } else {
                    std::cout << "File not found.\n";
                }
                break;

            case 7:
                std::cout << "Enter file name to set permissions: ";
                std::cin >> path;
                std::cout << "Enter permissions (e.g., 755): ";
                std::cin >> permissions;
                if (explorer.setPermissions(path, permissions)) {
                    std::cout << "Permissions set successfully.\n";
                } else {
                    std::cout << "Setting permissions failed.\n";
                }
                break;

            case 8:
                std::cout << "Enter directory to navigate to: ";
                std::cin >> path;
                explorer.changeDirectory(path);
                break;

            case 9:
                explorer.goUpOneDirectory();
                break;

            case 10:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 10);

    return 0;
}
