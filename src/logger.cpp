#include <iostream>
#include <chrono>
#include "logger.h"

void Logger::log(const std::string_view &message) {

    std::cout << "\033[32m" << "[ " << getTime() << " ] " << message << std::endl << "\033[0m";
}

void Logger::error(const std::string_view &error) {

    std::cerr << "\033[31m" << "[ " << getTime() << " ] " << error << '\n' << "\033[0m";

}

std::string Logger::getTime() {
    auto now{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
    return output;
}