#include "log.h"

Log* Log::Instance() {
    static Log instance;
    return &instance;
}

Log::Log() {}

void Log::message(LogLevel level, const std::string& msg) {
    if (entries.size() == MAX_ENTRIES) {
        entries.erase(entries.begin());
    }
    LogEntry entry{ std::time(nullptr), level, msg };
    entries.push_back(entry);
}

void Log::print() {
    for (const auto& entry : entries) {
        std::tm* tm = std::localtime(&entry.timestamp);
        std::cout << "[" << std::put_time(tm, "%Y-%m-%d %H:%M:%S") << "] ";
        switch (entry.level) {
            case LOG_NORMAL: std::cout << "[INFO] "; break;
            case LOG_WARNING: std::cout << "[WARNING] "; break;
            case LOG_ERROR: std::cout << "[ERROR] "; break;
        }
        std::cout << entry.message << std::endl;
    }
}
