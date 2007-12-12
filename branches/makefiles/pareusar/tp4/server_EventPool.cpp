#include "server_EventPool.h"

EventPool* EventPool::instance = 0;

EventPool::~EventPool()
{
    Container::iterator it = pool.begin( );

    while( it != pool.end() )
        delete (*it++).second;
}

Evento* EventPool::crear_evento( const std::string& nombre )
{
    Evento* ev = new Evento();
    pool.insert( std::pair<std::string,Evento*>(nombre, ev ) );
    return ev;
}

bool EventPool::probar( const std::string& nombre )
{
    Container::iterator fin = pool.upper_bound( nombre );
    Container::iterator cursor = pool.find( nombre );

    while( cursor != pool.upper_bound( nombre ) ) {
        Evento* cur = (*cursor++).second;
        if( cur && cur->probar() )
            return true;
    }
    return false;
}

void EventPool::esperar( const std::string& nombre )
{
    Container::iterator cursor = pool.find( nombre );
    Container::iterator fin = pool.upper_bound( nombre );
    while( cursor != fin ) {
        Evento* cur = (*cursor++).second;
        cur->esperar();
    }
}
