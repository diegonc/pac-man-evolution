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

void Mutex::lock()
{
	if( pthread_mutex_lock( &mutex ) != 0 )
		throw Error::SystemError();
}

bool Mutex::try_lock()
{
    return ( pthread_mutex_trylock( &mutex ) == 0 );
}

void Mutex::unlock()
{
	if( pthread_mutex_unlock( &mutex ) != 0 )
		throw Error::SystemError();
}
