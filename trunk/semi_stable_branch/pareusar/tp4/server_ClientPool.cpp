#include "server_ClientPool.h"

ClientPool::ClientPool() : num_orden(0)
{

}

ClientPool::~ClientPool()
{
    std::list<Cliente*>::iterator it = clientes.begin();
    while( it != clientes.end() )
        delete (*it++);
}

void ClientPool::lanzar_cliente( Socket* sock )
{
    Cliente* c = new Cliente( sock, ++num_orden );
    c->start();
    clientes.push_back(c);
}

void ClientPool::join_all()
{
    std::list<Cliente*>::iterator it = clientes.begin();
    while( it != clientes.end() )
        (*it++)->join();
}
