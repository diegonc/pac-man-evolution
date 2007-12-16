#include "mutex.h"

Mutex::Mutex() throw( Error::MutexError )
{
    int err = pthread_mutex_init( &mutex, NULL );
    if( err != 0 )
        throw Error::MutexError(err);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy( &mutex );
}

void Mutex::lock()
{
	int err = pthread_mutex_lock( &mutex );
	if( err	!= 0 )
		throw Error::MutexError(err);
}

bool Mutex::try_lock()
{
    return ( pthread_mutex_trylock( &mutex ) == 0 );
}

void Mutex::unlock()
{
	int err = pthread_mutex_unlock( &mutex );
	if( err != 0 )
		throw Error::MutexError(err);
}

pthread_mutex_t* Mutex::get_mutex()
{
	return &mutex;
}
