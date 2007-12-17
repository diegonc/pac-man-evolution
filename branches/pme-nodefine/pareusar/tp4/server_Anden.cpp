#include "server_Anden.h"
#include "server_Tren.h"
#include "server_Log.h"
#include "server_LogEntry.h"
#include "server_EventPool.h"
#include <sstream>
#include <cassert>

class Anden::OnFrontTester
{
    std::queue<Elemento>& q;
    const Tren* t;

    public:
        OnFrontTester( std::queue<Elemento>& q, const Tren* t ) : q(q), t(t) { }

        bool operator()()
        {
            return ( q.front().first == t );
        };
};

Anden::Anden( const std::string& id ) : Parada( id )
{
}

void Anden::ocupar( const Tren* t, Condition* cond )
{
    bool libre;

    Time para = Time::now();

    {
        Mutex::Locker lm( key );
        libre = trenes.empty();
        trenes.push( Elemento(t,cond) );
    }

    Log::getInstance().add( LogEntry::crear_para( t->getId(), getId(), libre ));

    // Si esta libre puede ocuparlo inmediatamente
    if( !libre ) {
        // Antes de volver espera a que la condicion se cumpla.
        cond->wait( key, OnFrontTester( trenes, t ) );
    }

    Time entra = Time::now();
    Log::getInstance().add( LogEntry::crear_entra( t->getId(), getId(), (entra - para).to_mili() ) );
}

void Anden::descargar()
{
    const Tren* t;
    Thread::sleep( 1.5 );

    {
        Mutex::Locker lm( key );
        t = trenes.front().first;
    }

    Log::getInstance().add( LogEntry::crear_sale( t->getId(), getId() ));

    {
        Mutex::Locker lm( key );
        // El tren se quita de la cola
        trenes.pop();
        // notifica al siguiente tren
        if( !trenes.empty() )
            trenes.front().second->signal();
    }
}
