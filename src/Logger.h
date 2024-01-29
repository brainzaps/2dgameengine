//
// Created by Konstantin Skrypak on 30.01.2024.
//

#pragma once

#include <string>

const std::string ANSI_RED = "\x1B[31m";
const std::string ANSI_GREEN = "\x1B[32m";

class Logger {
public:
    static void Log(const std::string &message);

    static void Err(const std::string &message);
};


