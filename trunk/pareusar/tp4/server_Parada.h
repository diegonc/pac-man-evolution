#ifndef __PARADA_H__
#define __PARADA_H__

#define NEEDS_TREN
#include "server_Forwards.h"

#include <string>
#include "common_Condition.h"

class Parada
{
    private:
        std::string id;

    public:
        virtual ~Parada() {}

        Parada( const std::string& id ) : id( id ) { }

        const std::string& getId() const { return id; }

        virtual void ocupar( const Tren* t, Condition* ev ) = 0;

        virtual void descargar() = 0;
};

#endif // __PARADA_H__
