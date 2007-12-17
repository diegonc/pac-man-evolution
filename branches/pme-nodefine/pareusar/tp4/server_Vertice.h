#ifndef __VERTICE_H__
#define __VERTICE_H__

#include <list>
#include <string>
#include <assert.h>

#define NEEDS_PARADA
#define NEEDS_ARCO
#include "server_Forwards.h"

class Vertice
{
    private:
        std::list<Arco*> arcos;

    public:
        const std::string& getId() const;

        void agregarArco( Arco* arco )
        {
            arcos.push_back( arco );
        }

        void quitarArco( Arco* arco );

        template<class Functor>
        Functor foreach_arista( Functor fun )
        {
            typename std::list<Arco*>::iterator it = arcos.begin();
            while( it != arcos.end() )
                fun( (*it++) );

            return fun;
        }
    private:
        Parada* parada;

    public:
         Vertice( Parada* parada ) : parada( parada ) { }
        ~Vertice();
        Parada* obtener_dato() const { return parada; }
};

#endif /* __VERTICE_H__ */
