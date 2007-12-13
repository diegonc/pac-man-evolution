#include "common_Thread.h"
#include "common_Time.h"
#include "common_Errores.h"
#include <signal.h> // para pthread_kill

void* Thread::helper( void* data )
{
    return ((Thread*)data)->run();
}

void Thread::start( )
{
    if( pthread_create( &threadId, NULL, helper, this ) != 0 )
        throw Error::SystemError();
}

void Thread::raise( int signal )
{
    pthread_kill( threadId, signal );
}

void* Thread::join( )
{
    void* ret;
    pthread_join( threadId, &ret );
    return ret;
}

void Thread::yield()
{
    pthread_yield();
}

void Thread::sleep( double sec )
{
    usleep( (__useconds_t)(US_X_SEG * sec) );
}
