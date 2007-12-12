#ifndef __LOG_H__
#define __LOG_H__

#include "common_Time.h"
#include "server_LogEntry.h"
#include "server_Observable.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <sstream>
#include <string>
#include <vector>

class Log : public Observable<LogEntry*>
{
    // Singleton
    private:
        static Log* instance;

        Log() {}

        ~Log() {}

    public:
        static Log& getInstance()
        {
            if( !instance ) {
                instance = new Log();
            }
            return *instance;
        }
        static void destroy()
        {
            if( instance )
                delete instance;
        }

        class Cleaner
        {
            public:
                /* Con constructor por default y -Wall, el compilador reporta
                 * "unused variable"
                 */
                Cleaner() { }
                ~Cleaner() { Log::destroy(); }
        };

    // Log
    private:
        Time start;

    public:
        void set_start_time( const Time& t );

        void add( LogEntry* le );
};

#endif // __LOG_H__
