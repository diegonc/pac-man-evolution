#include "server_Arco.h"
#include "server_Parada.h"
#include "server_Vertice.h"

Vertice::~Vertice()
{
    delete parada;
}

const std::string& Vertice::getId() const
{
    return parada->getId();
}

void Vertice::quitarArco( Arco* arco )
{
    std::list<Arco*>::iterator it = arcos.begin();

    while( it != arcos.end() )
        if( *it == arco ) {
            delete *it;
            arcos.erase( it );
            break;
        } else
            ++it;
}
