//
// Created by Konstantin Skrypak on 30.01.2024.
//

#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

#include "Logger.h"

std::vector <LogEntry> Logger::messages;

void Logger::Log(const std::string &message) {
    auto now = std::chrono::system_clock::now();

    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm *localTime = std::localtime(&currentTime);

    std::ostringstream oss;
    oss << "LOG | " << std::put_time(localTime, "%d-%b-%Y %H:%M:%S") << " - " << message;

    LogEntry entry = {
            LogType::INFO,
            oss.str(),
    };

    std::cout << ANSI_GREEN << oss.str() << ANSI_GREEN << std::endl;

    messages.push_back(entry);

}

void Logger::Err(const std::string &message) {

    auto now = std::chrono::system_clock::now();

    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm *localTime = std::localtime(&currentTime);

    std::ostringstream oss;
    oss << "ERR | " << std::put_time(localTime, "%d-%b-%Y %H:%M:%S") << " - " << message;

    LogEntry entry = {
            LogType::ERR,
            oss.str(),
    };

    std::cout << ANSI_RED << oss.str() << ANSI_RED << std::endl;

    messages.push_back(entry);
}
