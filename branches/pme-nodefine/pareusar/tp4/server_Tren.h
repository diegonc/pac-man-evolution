#ifndef __TREN_H__
#define __TREN_H__

#define NEEDS_REDVIAL
#define NEEDS_EVENTO
#define NEEDS_DIJKSTRA
#include "server_Forwards.h"

#include <vector>
#include <string>
#include <list>

#include "common_Thread.h"
#include "common_Condition.h"

class Tren : public Thread
{
    private:
            class DatoParada;
            static float velocidad;

            std::string id;
            std::string salida;
            std::list<DatoParada> paradas;
            Dijkstra* dijkstra;
            Evento* trenListo;
            Condition en_parada;

            void transitarVia( const std::list<DatoParada>::iterator& i );
            void tomarAnden( const std::list<DatoParada>::iterator& i );
            void calcularDistancias();

    public:
        Tren( const std::vector<std::string>& itinerario, const RedVial& rv );
         ~Tren();

        void* run();
        const std::string& getId() const;
};


#endif    /* __TREN_H__ */
