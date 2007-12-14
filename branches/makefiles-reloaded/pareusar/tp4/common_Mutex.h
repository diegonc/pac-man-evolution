#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>
#include "common_Errores.h"

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

        int lock();
        bool try_lock();
        int unlock();

        operator pthread_mutex_t*()
        {
            return &mutex;
        }
};

#endif
