#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "common_Socket.h"
#include "common_Evento.h"
#include <string>

class Cliente : public Thread
{
    std::string ip;
    Evento& fin_app;
    short port;

    public:
        Cliente( Evento& t );

        void set_ip( const std::string& ip ) { this->ip = ip; }

        void set_port( short port ) { this->port = port; }

        /*
         * Si el usuario presiona la tecla de salida retorna con Error::OTRO
         * sino con Error::OK.
         */
        void* run();
};

#endif /* __CLIENTE_H__ */
