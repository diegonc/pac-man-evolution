#include "server_FileLogger.h"
#include "server_Cliente.h"

FileLogger::FileLogger( const std::string& s ) : fd( s.c_str() )
{
    Log::getInstance().add_observer( this );
}

FileLogger::~FileLogger( )
{
    Log::getInstance().remove_observer( this );
}

void* FileLogger::run()
{
    EventPool& eventos = EventPool::getInstance();

    while( !eventos.probar( "simulacion-fin" ) ) {
        pending.wait();
        while( !pending.empty() ) {
            LogEntry* e = pending.pop();

            // escribe la entrada en el archivo
            e->print( );
            e->print( fd );
            e->destruir();
        }
    }

    // Despacha los eventos que podrian haber ingresado pero no procesados
    // por recibir el evento de finalizacion
    while( !pending.empty() ) {
        LogEntry* e = pending.pop();

        // escribe la entrada en el archivo
        e->print( );
        e->print( fd );
        e->destruir();
    }
    return 0;
}

void FileLogger::notify( LogEntry* le )
{
    pending.push( le );
}
