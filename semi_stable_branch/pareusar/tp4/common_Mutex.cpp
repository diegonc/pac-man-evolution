#include "common_Mutex.h"

Mutex::Mutex() throw( Error::SystemError )
{
    if( pthread_mutex_init( &mutex, NULL ) != 0 )
        throw Error::SystemError();
}

Mutex::~Mutex()
{
    pthread_mutex_destroy( &mutex );
}

int Mutex::lock()
{
    return pthread_mutex_lock( &mutex );
}

bool Mutex::try_lock()
{
    return ( pthread_mutex_trylock( &mutex ) == 0 );
}

int Mutex::unlock()
{
    return pthread_mutex_unlock( &mutex );
}
