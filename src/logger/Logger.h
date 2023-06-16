#pragma once

#include <string_view>
#include <vector>

enum class LogType {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
};

struct LogEntry {
    LogType type;
    std::string message;
};

class Logger {
public:
    static std::vector<LogEntry> messages;
    static void log(const std::string &message);
    static void error(const std::string &error);
private:
    static std::string getTime();

};