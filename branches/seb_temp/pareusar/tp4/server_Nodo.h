#ifndef __NODO_H__
#define __NODO_H__

#define NEEDS_THREAD
#define NEEDS_EVENTO
#include "server_Forwards.h"

#include "server_Parada.h"
#include "server_EventPool.h"
#include <string>

class Nodo : public Parada
{
    public:
        Nodo( const std::string& id ) : Parada( id ) { }

        void ocupar( const Tren* t, Condition* cond );

        void descargar() { }
};

#endif
