#ifndef LOG_H
#define LOG_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <iomanip>

enum LogLevel {
    LOG_NORMAL,
    LOG_WARNING,
    LOG_ERROR
};

struct LogEntry {
    std::time_t timestamp;
    LogLevel level;
    std::string message;
};

class Log {
public:
    static Log* Instance();

    void message(LogLevel level, const std::string& msg);
    void print();

private:
    Log();
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

    std::vector<LogEntry> entries;
    static const int MAX_ENTRIES = 10;
};

#endif // LOG_H
