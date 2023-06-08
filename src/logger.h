#pragma once

#include <string_view>

class Logger {
public:
    static void log(const std::string_view &message);
    static void error(const std::string_view &error);
private:
    static std::string getTime();
};