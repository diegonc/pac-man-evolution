#ifndef __ANDEN_H__
#define __ANDEN_H__

#define NEEDS_TREN
#define NEEDS_EVENTO
#include "server_Forwards.h"

#include "common_Mutex.h"
#include "server_Parada.h"
#include <string>
#include <queue>

class Anden : public Parada
{
    private:
        typedef std::pair<const Tren*,Condition*> Elemento;
        class OnFrontTester;

        Mutex key;
        std::queue<Elemento> trenes;

    public:
        Anden( const std::string& id );

        void ocupar( const Tren* t, Condition* ev );

        void descargar();

        void* run();
};

#endif /* __ANDEN_H__ */
