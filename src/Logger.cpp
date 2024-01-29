//
// Created by Konstantin Skrypak on 30.01.2024.
//

#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>

#include "Logger.h"

void Logger::Log(const std::string &message) {
    auto now = std::chrono::system_clock::now();

    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm *localTime = std::localtime(&currentTime);


    std::cout
            << ANSI_GREEN
            << "LOG | "
            << std::put_time(localTime, "%d-%b-%Y %H:%M:%S")
            << " - "
            << message
            << ANSI_GREEN
            << std::endl;

}

void Logger::Err(const std::string &message) {

    auto now = std::chrono::system_clock::now();

    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm *localTime = std::localtime(&currentTime);

    std::cout
            << ANSI_RED
            << "ERR | "
            << std::put_time(localTime, "%d-%b-%Y %H:%M:%S")
            << " - "
            << message
            << ANSI_RED
            << std::endl;
}
