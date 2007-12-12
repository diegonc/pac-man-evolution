#include "common_Evento.h"

Evento::Evento()
{
    activado = false;
}

void Evento::activar()
{
    Mutex::Locker lm( key );
    activado = true;
    cvar.signal();
}

void Evento::reset()
{
    Mutex::Locker lm( key );
    activado = false;
}

void Evento::esperar()
{
    cvar.wait( key, Tester( *this ) );
}

bool Evento::probar()
{
    Mutex::Locker lm( key );
    return activado;
}
