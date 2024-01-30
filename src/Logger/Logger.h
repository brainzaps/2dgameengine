//
// Created by Konstantin Skrypak on 30.01.2024.
//

#pragma once

#include <string>
#include <vector>

const std::string ANSI_RED = "\x1B[31m";
const std::string ANSI_GREEN = "\x1B[32m";

enum LogType {
    INFO,
    ERR,
    WARN,
};

struct LogEntry {
    LogType type;
    std::string message;
};

class Logger {
public:
    static std::vector <LogEntry> messages;

    static void Log(const std::string &message);

    static void Err(const std::string &message);
};


