/*
 * my_logging.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/23/2024
 */

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_MY_LOGGING_H
#define FINAL_MY_LOGGING_H

// Reference:
// https://www.geeksforgeeks.org/logging-system-in-cpp/

// Enum to represent log levels
enum LogLevel {
    DEBUG, // 0
    INFO, // 1
    WARNING, // 2
    ERROR,  // 3
    CRITICAL // 4
};

class Logger {
    LogLevel l = WARNING;

    // Converts log level to a string for output
    static std::string levelToString( LogLevel level ) {
        switch ( level ) {
            case DEBUG:
                return "DEBUG";
            case INFO:
                return "INFO";
            case WARNING:
                return "WARNING";
            case ERROR:
                return "ERROR";
            case CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN";
        }
    }

    void log( LogLevel ll, const char* m );

public:
    // Constructor: Opens the log file in append mode
    Logger() {}

    Logger( LogLevel l_ ) : l( l_ ) {}

    // Destructor: Closes the log file
    ~Logger() {}

    // Log a message with a given logging level
    // https://stackoverflow.com/questions/5057021/why-do-inline-functions-have-to-be-defined-in-a-header-file
    void debug( const char* m ) {
        log( DEBUG, m );
    }

    void debug( const std::string& m ) {
        debug( m.c_str() );
    }

    void info( const char* m ) {
        log( INFO, m );
    }

    void info( const std::string& m ) {
        info( m.c_str() );
    }
};

#endif //FINAL_MY_LOGGING_H
