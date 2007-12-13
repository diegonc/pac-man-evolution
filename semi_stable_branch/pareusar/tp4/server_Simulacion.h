#ifndef __SIMULACION_H__
#define __SIMULACION_H__

#define NEEDS_TREN
#include "server_Forwards.h"

#include "server_RedVial.h"
#include "server_Parada.h"
#include "server_Parser.h"
#include "common_Evento.h"
#include <iostream>

class Simulacion
{
    private:
        RedVial red;
        Parser p;
        std::list<Tren*> trenes;
        Evento* fin;
        Evento* inicio;
        std::istream& fd_red; // stream de configuracion.
        std::istream& fd_it; // stream de itinerario.

        struct wait
        {
            void operator()( Evento* ev )
            {
                ev->esperar();
            }
        };

    public:
        Simulacion( std::istream& fd_red, std::istream& fd_it );

        ~Simulacion();

        void inicializar_eventos();

        void cargar_red();

        void cargar_itinerario();

        void comenzar();

        void aguardar();

        int run();
};

#endif // __SIMULACION_H__
