#include <common/mutex.h>

#include <iostream>
using namespace std;

Mutex::Mutex() throw( Error::MutexError )
{
    //pthread_mutexattr_t attr;

    int err = pthread_mutex_init( &mutex, NULL );
    if( err != 0 )
        throw Error::MutexError(this, err);
}


Mutex::Mutex(bool log) throw( Error::MutexError )
{
    int err = pthread_mutex_init( &mutex, NULL );
    if( err != 0 )
        throw Error::MutexError(this, err);

 //   if( log )
   // cerr << "Mutex: 0x" << hex << (int)this << " mutex_t: " << hex << (int)&mutex << " creado." << endl;
}

Mutex::~Mutex()
{
    //cerr << "Mutex: 0x" << hex << (int)this << " mutex_t: 0x" << hex <<(int)&mutex << " destruyendose." << endl;

    pthread_mutex_destroy( &mutex );
}

void Mutex::lock()
{
	int err = pthread_mutex_lock( &mutex );
	if( err	!= 0 )
		throw Error::MutexError(this, err);
}

bool Mutex::try_lock()
{
    return ( pthread_mutex_trylock( &mutex ) == 0 );
}

void Mutex::unlock()
{
	int err = pthread_mutex_unlock( &mutex );
	if( err != 0 )
		throw Error::MutexError(this, err);
}

pthread_mutex_t* Mutex::get_mutex()
{
	return &mutex;
}
