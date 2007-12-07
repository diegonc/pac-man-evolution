#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <unistd.h> // para usleep

class Thread
{
    private:
        static void* helper( void* data );

        pthread_t threadId;

    public:
        virtual ~Thread() {}
        void start();
        void raise( int signal );
        virtual void* run() = 0;
        void* join( );

        static void sleep( double sec );
        static void yield();
};

#endif /* __THREAD_H__ */
