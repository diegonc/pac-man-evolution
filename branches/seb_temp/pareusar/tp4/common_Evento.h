#ifndef __EVENTO_H__
#define __EVENTO_H__

#include "common_Thread.h"
#include "common_Mutex.h"
#include "common_Condition.h"

class Evento
{
    private:
        Condition cvar;
        Mutex     key;
        bool      activado;

        class Tester
        {
            const Evento& e;
            public:
                Tester( const Evento& e ) : e( e ) { }
                bool operator()() const
                {
                    return e.activado;
                }
        };

    public:
        Evento();

        void activar();

        void reset();

        void esperar();

        bool probar();

};

#endif /* __EVENTO_H__ */
