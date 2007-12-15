#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>
#include "errores.h"

class Mutex
{
    private:
        pthread_mutex_t mutex;

    public:
        class Locker
        {
            Mutex& k;

            public:
                Locker( Mutex& k ) : k( k ) { k.lock(); }
                ~Locker() { k.unlock(); }
        };

    public:
        Mutex() throw( Error::SystemError );
        ~Mutex();

        void lock();
        bool try_lock();
        void unlock();

        operator pthread_mutex_t*()
        {
            return &mutex;
        }
};

#endif
