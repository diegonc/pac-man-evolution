#ifndef __ARCO_H__
#define __ARCO_H__

#define NEEDS_GRAFO
#define NEEDS_VERTICE
#include "server_Forwards.h"

#include <string>

class Arco
{
    private:
        Vertice* origen;
        Vertice* destino;
        float peso;
        std::string id;

    public:
        Arco( const std::string& id, float peso ) : peso( peso ), id( id ) { }
        const std::string& getId() const;
        float getPeso() const { return peso; }
        void setOrigen( Vertice* v ) { origen = v; }
        void setDestino( Vertice* v ) { destino = v; }
        Vertice* getOrigen() const { return origen; }
        Vertice* getDestino() const { return destino; }
};

#endif /* __ARCO_H__ */
