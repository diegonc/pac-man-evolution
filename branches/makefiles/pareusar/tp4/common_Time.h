#ifndef __TIME_H__
#define __TIME_H__

#include "sys/time.h"
#include "math.h"

#define MS_X_SEG    (1000L)
#define US_X_MS     (1000L)
#define US_X_SEG    (US_X_MS*MS_X_SEG)

class Time
{
    private:
        struct timeval time;

    public:
        Time(){ time.tv_sec = 0; time.tv_usec = 0; }

        Time(unsigned long s, unsigned long u)
        {
            time.tv_sec = s;
            time.tv_usec = u;
        }

        Time( const timeval& t ) : time( t ) { }

        Time( double segundos );

        static Time now( );

        Time operator-( const Time& t );

        Time operator+( const Time& t );

        operator timeval*()
        {
            return &time;
        }

        bool operator<( const Time& t )
        {
            return ( (time.tv_sec < t.time.tv_sec) ||
                     ((time.tv_sec == t.time.tv_sec) &&
                      (time.tv_usec < t.time.tv_usec ) ));
        }

        unsigned long to_micro() const
        {
            return ( to_mili() * US_X_MS );
        }

        unsigned long to_mili() const
        {
            return ( time.tv_sec * MS_X_SEG + time.tv_usec / US_X_MS );
        }
};

#endif // __TIME_H__
