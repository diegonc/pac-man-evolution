#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <pthread.h>
#include "common_Mutex.h"

class Condition
{
    pthread_cond_t cvar;

    public:
        Condition();
        ~Condition();

        void signal();
        template<class Functor>
        void wait( Mutex& m, Functor tester );
};

template<class Functor>
void Condition::wait( Mutex& m, Functor tester )
{
    Mutex::Locker locker( m );
    while( !tester() )
        pthread_cond_wait( &cvar, m );
}

#endif
