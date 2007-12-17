#ifndef __LECTORCONSOLA_H__
#define __LECTORCONSOLA_H__

#include "common_Thread.h"
#include "common_Evento.h"
#include <iostream>
#include "common_Errores.h"

class LectorConsola : public Thread
{
    Evento& fin_app;

    public:
        LectorConsola( Evento& t ) : fin_app( t ) { }

        void* run();
};

void* LectorConsola::run()
{
    int result = Error::OK;
    char c;
    while( ! fin_app.probar() ) {
        std::cin >> c;
        if( ( c=='x' ) || ( c=='X' ) ) {
            fin_app.activar();
            break;
        }
    }
    return (void*)result;
}

#endif /* __LECTORCONSOLA_H__ */
