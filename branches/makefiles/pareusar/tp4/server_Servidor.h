#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

#include "common_Thread.h"
#include "common_Socket.h"
#include "server_EventPool.h"
#include "server_ClientPool.h"

class Servidor : public Thread
{
    Socket sock;
    int port;
    ClientPool pool;

    public:
        Servidor( int port );

        void* run( );
};

#endif /* __SERVIDOR_H__ */
