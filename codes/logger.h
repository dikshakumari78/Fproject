#include "Logger.h"
#include <iostream>

Logger::Logger(const std::string& filename) : logFile_(filename, std::ios_base::app) {
    if (!logFile_.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

void Logger::log(const std::string& message) {
    if (logFile_.is_open()) {
        logFile_ << message << std::endl;
    } else {
        std::cerr << "Log file is not open." << std::endl;
    }
}
