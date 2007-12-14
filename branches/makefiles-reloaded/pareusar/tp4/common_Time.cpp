#include "common_Time.h"

Time::Time( double segundos )
{
    // Segundos
    time.tv_sec = (time_t)floor( segundos );
    // fraccion de segundo en micros
    time.tv_usec = (suseconds_t)((segundos - time.tv_sec)*US_X_SEG);
}

Time Time::now( )
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday( &tv, &tz );
    return Time( tv );
}

Time Time::operator-( const Time& t )
{
    Time resta;

    resta.time.tv_sec = time.tv_sec - t.time.tv_sec;
    resta.time.tv_usec = time.tv_usec - t.time.tv_usec;

    if( time.tv_usec < t.time.tv_usec ) {
        resta.time.tv_sec--;
        resta.time.tv_usec += US_X_SEG;
    }
    return resta;
}

Time Time::operator+( const Time& t )
{
    unsigned long sec = time.tv_sec + t.time.tv_sec;
    unsigned long usec = time.tv_usec + t.time.tv_usec;

    sec += ( usec / US_X_SEG );
    usec %= US_X_SEG;

    return Time( sec, usec );
}
