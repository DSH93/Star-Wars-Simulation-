#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <mutex>
#include <filesystem>
#include <vector>
#include <ctime>

class Logger {
public:
    enum class Level { INFO, WARNING, ERROR }; // Enum class for log levels
    static Logger& getInstance(); // Singleton
    void log(const std::string& message, Level level = Level::INFO); // Log message with level

private:
    Logger();
    ~Logger();

    void initializeLogFile(); // Initialize log file
    void manageOldLogs(); // Manage old log files (delete if more than maxLogFiles)
    static std::string getTimestamp() ; // Get current timestamp
    void createLogDirectoryIfNotExists(); // Create log directory if not exists

    std::ofstream logFile; // Log file stream
    std::string logFileName;
    std::mutex logMutex; // Mutex for thread safety to write to log file
    std::string logDirectory; // Log directory
    const size_t maxLogFiles = 5; // Maximum number of log files otherwise delete old logs

    static std::string levelToString(Level level);
};

#endif // LOGGER_H
