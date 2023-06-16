#include <iostream>
#include <chrono>
#include <vector>
#include "Logger.h"

std::vector<LogEntry> Logger::messages;

void Logger::log(const std::string &message) {
    LogEntry logEntry;
    logEntry.type = LogType::LOG_INFO;
    logEntry.message = "LOG: [" + getTime() + "]: " + message;
    std::cout << "\033[32m" << logEntry.message << std::endl << "\033[0m";
    messages.push_back(logEntry);
}

void Logger::error(const std::string &error) {
    LogEntry logEntry;
    logEntry.type = LogType::LOG_ERROR;
    logEntry.message = "LOG: [" + getTime() + "]: " + error;
    std::cerr << "\033[31m" << logEntry.message << '\n' << "\033[0m";
    messages.push_back(logEntry);
}

std::string Logger::getTime() {
    auto now{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
    return output;
}