#include "FileExplorer.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

FileExplorer::FileExplorer(Logger& logger) : logger_(logger), currentDirectory_(std::filesystem::current_path().string()) {}

void FileExplorer::listFiles(const std::string& directory) {
    logger_.log("Listing files in directory: " + directory);
    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            std::cout << entry.path() << std::endl;
        }
    } catch (const std::exception& e) {
        logger_.log("Listing files failed: " + std::string(e.what()));
    }
}

bool FileExplorer::copyFile(const std::string& src, const std::string& dest) {
    logger_.log("Copying file from " + src + " to " + dest);
    try {
        std::filesystem::copy(src, dest);
        logger_.log("File copied successfully.");
        return true;
    } catch (const std::exception& e) {
        logger_.log("Copy failed: " + std::string(e.what()));
        return false;
    }
}

bool FileExplorer::moveFile(const std::string& src, const std::string& dest) {
    logger_.log("Moving file from " + src + " to " + dest);
    try {
        std::filesystem::rename(src, dest);
        logger_.log("File moved successfully.");
        return true;
    } catch (const std::exception& e) {
        logger_.log("Move failed: " + std::string(e.what()));
        return false;
    }
}

bool FileExplorer::deleteFile(const std::string& path) {
    logger_.log("Deleting file: " + path);
    try {
        std::filesystem::remove(path);
        logger_.log("File deleted successfully.");
        return true;
    } catch (const std::exception& e) {
        logger_.log("Delete failed: " + std::string(e.what()));
        return false;
    }
}

bool FileExplorer::createFile(const std::string& path) {
    logger_.log("Creating file: " + path);
    try {
        std::ofstream file(path);
        file.close();
        logger_.log("File created successfully.");
        return true;
    } catch (...) {
        logger_.log("File creation failed.");
        return false;
    }
}

bool FileExplorer::searchFile(const std::string& filename) {
    logger_.log("Searching for file: " + filename);
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(".")) {
            if (entry.path().filename() == filename) {
                logger_.log("File found: " + entry.path().string());
                return true;
            }
        }
        logger_.log("File not found.");
        return false;
    } catch (const std::exception& e) {
        logger_.log("Search failed: " + std::string(e.what()));
        return false;
    }
}

bool FileExplorer::setPermissions(const std::string& path, int permissions) {
    logger_.log("Setting permissions for file: " + path);
    try {
        std::filesystem::permissions(path, static_cast<std::filesystem::perms>(permissions), std::filesystem::perm_options::replace);
        logger_.log("Permissions set successfully.");
        return true;
    } catch (const std::exception& e) {
        logger_.log("Setting permissions failed: " + std::string(e.what()));
        return false;
    }
}

void FileExplorer::changeDirectory(const std::string& directory) {
    logger_.log("Changing directory to: " + directory);
    try {
        std::filesystem::current_path(directory);
        currentDirectory_ = std::filesystem::current_path().string();
        logger_.log("Directory changed successfully.");
    } catch (const std::exception& e) {
        logger_.log("Change directory failed: " + std::string(e.what()));
    }
}

void FileExplorer::goUpOneDirectory() {
    logger_.log("Going up one directory level.");
    try {
        std::filesystem::current_path("..");
        currentDirectory_ = std::filesystem::current_path().string();
        logger_.log("Directory changed successfully.");
    } catch (const std::exception& e) {
        logger_.log("Going up one directory failed: " + std::string(e.what()));
    }
}
