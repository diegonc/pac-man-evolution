#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include <list>
#include "common_Mutex.h"

template<class X>
class Observable
{
    public:
        class Observer
        {
            public:
                virtual ~Observer() {}
                virtual void notify( X le ) = 0;
        };

    private:
        Mutex obs_lock;
        std::list<Observer*> observers;

    public:

        void add_observer( Observer* o );

        void remove_observer( Observer* o );

        void notify_all( X le );

        int observer_count();
};

template<class X>
void Observable<X>::add_observer( Observer* o )
{
    Mutex::Locker lm( obs_lock );
    observers.push_back( o );
}

template<class X>
int Observable<X>::observer_count()
{
    Mutex::Locker lm( obs_lock );
    return observers.size();
}

template<class X>
void Observable<X>::remove_observer( Observer* o )
{
    Mutex::Locker lm( obs_lock );

    typename std::list<Observer*>::iterator it = observers.begin();
    while( it != observers.end() )
        if( *it == o ) {
            observers.erase( it );
            break;
        } else ++it;
}

template<class X>
void Observable<X>::notify_all( X le )
{
    Mutex::Locker lm( obs_lock );

    typename std::list<Observer*>::iterator it = observers.begin();
    while( it != observers.end() )
        (*it++)->notify( le );
}

#endif /* __OBSERVABLE_H__ */
