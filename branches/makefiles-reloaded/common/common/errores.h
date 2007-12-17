#ifndef __ERRORES_H__
#define __ERRORES_H__

#include <stdexcept>
#include <errno.h>
#include <cstring> // para strerror
#include <pthread.h>

class Mutex;

namespace Error
{
    enum Codes{
        OK,
        CMDLINE,
        OTRO
    };

    class SystemError : public std::runtime_error
    {
        /*
         * Clase utilizada como excepcion cuando alguna funcion de sistema
         * falla por motivos variados. Puede obtenerse una descripcion con
         * what().
         */
        bool interrupcion;

        public:
            SystemError( ) : std::runtime_error(strerror(errno))
            {
                interrupcion = (errno == EINTR );
            }

            bool interrumpido() { return interrupcion; }
    };

    class MutexError : public std::runtime_error
    {
	    static std::string to_string( int err );
	    public:
		    MutexError(Mutex* m, int err);
    };
}

#endif /* __ERRORES_H__ */
