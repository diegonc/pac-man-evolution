#ifndef __SYNCQUEUE_H__
#define __SYNCQUEUE_H__

#include <queue>
#include "common_Mutex.h"
#include "common_Condition.h"

template<class T>
class SyncQueue
{
    Mutex key;
    Condition ready;
    std::queue<T> q;

    class QueueNotEmptyTester
    {
        std::queue<T>& q;

        public:
            QueueNotEmptyTester( std::queue<T>& q ) : q(q) { }
            bool operator()()
            {
                return !q.empty();
            }
    };

    public:
        void push( T t );
        T pop();
        bool empty();

        /*
         * Espera a que la cola deje de estar vacia.
         */
        void wait();
};

template<class T>
void SyncQueue<T>::push( T t )
{
    Mutex::Locker locker( key );

    /* Si la cola estaba vacia, manda la señal para desbloquear a quienes
       esperan. */
    if( q.empty() ) ready.signal();
    q.push( t );
}

template<class T>
T SyncQueue<T>::pop( )
{
    Mutex::Locker locker( key );
    T t = q.front();
    q.pop();

    return t;
}

template<class T>
bool SyncQueue<T>::empty( )
{
    Mutex::Locker locker( key );
    return q.empty();
}

template<class T>
void SyncQueue<T>::wait( )
{
    ready.wait( key, QueueNotEmptyTester( q ) );
}


#endif
