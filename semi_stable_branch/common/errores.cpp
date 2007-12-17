#include "errores.h"
#include "mutex.h"
#include <iostream>

std::string Error::MutexError::to_string( int err )
    {
	    switch( err ) {
		        case EINVAL:
			    return std::string( "EINVAL: The value specified by mutex does not refer to an initialized mutex object.");
			case EBUSY:
			    return std::string( "EBUSY: The mutex could not be acquired because it was already locked." );
			case EAGAIN:
			    return std::string( "EAGAIN: The mutex could not be acquired because the maximum number of recursive locks for mutex has been exceeded." );
			case EDEADLK:
			    return std::string( "EDEADLK: A deadlock condition was detected or the current thread already owns the mutex." );
			case EPERM:
			    return std::string( "EPERM: The current thread does not own the mutex." );
			default:
			    return std::string( "Unknowk error." );
	    }
    }

Error::MutexError::MutexError(Mutex* m, int err)
	: std::runtime_error(to_string(err))
{
	Mutex::Locker ml( Mutex::_lock ); 
	std::list<Mutex*>::iterator it = Mutex::inicializados.begin( );
	while( it != Mutex::inicializados.end() )
		if( *it == m ){
			Mutex::inicializados.erase(it);
			break;
		} else ++it;

	std::cerr << "Creando MutexError para Mutex: " << std::hex;
	std::cerr << (int)m << " mutex_t: " << std::hex << (int)m->get_mutex();
	std::cerr << std::endl;
	if( it == Mutex::inicializados.end() )
		std::cerr << " no ";
	std::cerr << "inicializado." << std::endl;
}
