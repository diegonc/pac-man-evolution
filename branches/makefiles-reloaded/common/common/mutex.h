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
        Mutex() throw( Error::MutexError );
	Mutex(bool log) throw( Error::MutexError );
        ~Mutex();

        void lock();
        bool try_lock();
        void unlock();

	pthread_mutex_t* get_mutex(); /*    operator pthread_mutex_t*()
        {
            return &mutex;
        }*/
};

#endif
