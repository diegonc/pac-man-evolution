#include "mutex.h"

#include <iostream>
using namespace std;

Mutex Mutex::_lock;
std::list<Mutex*> Mutex::inicializados;

Mutex::Mutex() throw( Error::MutexError )
{
    //pthread_mutexattr_t attr;

    int err = pthread_mutex_init( &mutex, NULL );
    if( err != 0 )
        throw Error::MutexError(this, err);

    Mutex::Locker ml( _lock );
    inicializados.push_back( this );
}


Mutex::Mutex(bool log) throw( Error::MutexError )
{
    int err = pthread_mutex_init( &mutex, NULL );
    if( err != 0 )
        throw Error::MutexError(this, err);

 //   if( log )
   // cerr << "Mutex: 0x" << hex << (int)this << " mutex_t: " << hex << (int)&mutex << " creado." << endl;
    Mutex::Locker ml( _lock );
    inicializados.push_back( this );
}

Mutex::~Mutex()
{
    //cerr << "Mutex: 0x" << hex << (int)this << " mutex_t: 0x" << hex <<(int)&mutex << " destruyendose." << endl;

    pthread_mutex_destroy( &mutex );

    Mutex::Locker ml( _lock );
    std::list<Mutex*>::iterator it = inicializados.begin( );
    while( it != inicializados.end() )
	    if( *it == this ){
		    inicializados.erase(it);
		    break;
	    } else ++it;
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
