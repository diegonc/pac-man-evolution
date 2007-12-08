#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "../../common/client_socket.h"
#include "../../common/thread.h"
#include <string>

class Cliente : public Thread
{
    std::string ip;
    short port;

    public:
        Cliente( const std::string& ip, short port );

        void run();
};

#endif /* __CLIENTE_H__ */
