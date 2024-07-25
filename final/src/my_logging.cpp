/*
 * my_logging.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/23/2024
 */

#include "../include/my_logging.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void Logger::log( LogLevel ll, const char* m ) {
    if ( ll < l ) return;

    // Get current timestamp
    time_t now = time( 0 );
    tm *timeinfo = localtime( &now );
    char timestamp[20];
    std::strftime( timestamp, sizeof( timestamp ),
              "%Y-%m-%d %H:%M:%S", timeinfo );

    // Create log entry
    std::ostringstream logEntry;
    logEntry << "[" << timestamp << "] "
             << levelToString( ll ) << ": " << m;

    // Output to console
    std::cout << logEntry.str();
}
