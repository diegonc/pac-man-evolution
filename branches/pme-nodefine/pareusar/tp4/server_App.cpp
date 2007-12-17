#include "server_App.h"
#include <fstream>
#include "server_Simulacion.h"
#include "common_StringUtil.h"
#include "server_Servidor.h"
#include "server_FileLogger.h"
#include "common_Errores.h"
#include <signal.h>

void App::setup_signal_handler()
{
    struct sigaction sa;
    sigaction(SIGUSR1, NULL, &sa);
    sa.sa_flags &= ~SA_RESTART;
    sa.sa_handler = signal_handler;
    sigaction(SIGUSR1, &sa, NULL);
}

void App::parse_arguments()
{
    if( argc != 4 )
        throw Error::CMDLINE;

    try {
        StringUtil::convertir( argv[3], port );
    } catch(  StringUtil::ConversionInvalida e ) {
        throw Error::CMDLINE;
    }

    fred = argv[1];
    fitinerario = argv[2];
}

int App::run()
{
    int error;

    try {
        EventPool::Cleaner epm;
        Log::Cleaner lm;

        setup_signal_handler();
        parse_arguments();

        std::ifstream red( fred );
        std::ifstream it( fitinerario );
        FileLogger flog( "simulacion.log" );
        Simulacion sim( red, it );
        Servidor serv( port );

        flog.start();
        serv.start();
        error = sim.run();

        // Desbloquea el servidor.
        serv.raise( SIGUSR1 );

        flog.join();
        serv.join();
    }catch( Error::SystemError e ) {
        std::cerr << e.what() << std::endl;
        error = Error::OTRO;
    }catch( Error::Codes e ) {
        error = e;
    }
    return error;
}
