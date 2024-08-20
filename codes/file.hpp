// FileManager.hpp
#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP
#include <string>
class FileManager {
public:
    void displayMenu();
    void handleUserChoice(int choice);
private:
    void moveFile();
    void copyFile();
    void deleteFile();
    void createFile();
    void searchFile();
    void managePermissions();
    // Helper functions to get input from the user
    std::string getFilePath(const std::string &prompt);
    std::string getSearchCriteria();
    std::string getDirectory();
    std::string getPermissions();
    void logOperation(const std::string &operation, const std::string &details);
};
#endif // FILE_MANAGER_HPP
