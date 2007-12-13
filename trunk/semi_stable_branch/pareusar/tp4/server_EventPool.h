#ifndef __EVENTPOOL_H__
#define __EVENTPOOL_H__

#include "common_Evento.h"
#include "common_Thread.h"
#include <map>
#include <string>

class EventPool
{
    private:
        static EventPool* instance;

    public:
        static EventPool& getInstance()
        {
            if( !instance ) {
                instance = new EventPool();
            }
            return *instance;
        }
        static void destroy()
        {
            if( instance )
                delete instance;
        }

        class Cleaner
        {
            public:
                /* Con constructor por default y -Wall, el compilador reporta
                 * "unused variable"
                 */
                Cleaner() { }
                ~Cleaner()
                {
                    EventPool::destroy();
                }
        };

    private:
        typedef std::multimap<std::string, Evento*> Container;
        Container pool;

        EventPool() {}

        ~EventPool();

    public:
        Evento* crear_evento( const std::string& nombre );

        /* Devuelve verdadero si alguno de los eventos estan activos. */
        bool probar( const std::string& nombre );

        /* Espera a que todos los eventos asociados a nombre este activos. */
        void esperar( const std::string& nombre );
};

#endif /* __EVENTPOOL_H__ */
