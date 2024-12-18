#include "Logger.h"
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>

namespace fs = std::filesystem;

std::string getLogDirectory() {
    fs::path projectRoot = fs::current_path().parent_path();
    fs::path logDir = projectRoot / "logs";

    if (!fs::exists(logDir)) {
        fs::create_directories(logDir);
    }
    return logDir.string();
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {
    this->logDirectory = getLogDirectory();
    createLogDirectoryIfNotExists();
    initializeLogFile();
    manageOldLogs();
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::createLogDirectoryIfNotExists() {
    if (!fs::exists(logDirectory)) {
        fs::create_directory(logDirectory);
    }
}

std::string Logger::getTimestamp() {
    auto now = std::time(nullptr);
    std::tm localTime{};
    localtime_s(&localTime, &now);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y_%m_%d__%H_%M_%S");
    return oss.str();
}

void Logger::initializeLogFile() {
    logFileName = logDirectory + "/log_" + getTimestamp() + ".txt";
    logFile.open(logFileName, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Failed to create log file: " + logFileName);
    }
}

void Logger::manageOldLogs() {
    std::vector<fs::path> logFiles;

    for (const auto& entry : fs::directory_iterator(logDirectory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            logFiles.push_back(entry.path());
        }
    }

    if (logFiles.size() > maxLogFiles) {
        std::sort(logFiles.begin(), logFiles.end());
        size_t excessFiles = logFiles.size() - maxLogFiles;
        for (size_t i = 0; i < excessFiles; ++i) {
            fs::remove(logFiles[i]);
        }
    }
}

void Logger::log(const std::string& message, Level level) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::string output = "[" + levelToString(level) + "] " + message;

    if (logFile.is_open()) {
        logFile << output << std::endl;
    }
}

std::string Logger::levelToString(Level level) {
    switch (level) {
        case Level::INFO: return "INFO";
        case Level::WARNING: return "WARNING";
        case Level::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}
