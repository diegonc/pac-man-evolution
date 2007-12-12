#include "server_Log.h"

Log* Log::instance = 0;

void Log::set_start_time( const Time& t )
{
    start = t;
}

void Log::add( LogEntry* le )
{
    le->set_time( Time::now() - start );
    le->add_refs( observer_count() - 1 );
    notify_all( le );
}
