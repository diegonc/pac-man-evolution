#include "server_Nodo.h"
#include "server_Tren.h"
#include "server_Log.h"
#include "common_Time.h"
#include <sstream>

void Nodo::ocupar( const Tren* t, Condition* cond )
{
    Time para = Time::now();

    Log::getInstance().add( LogEntry::crear_para( t->getId(), getId(), true ));

    Time entra = Time::now();

    Log::getInstance().add( LogEntry::crear_entra( t->getId(), getId(), (entra - para).to_mili() ) );
}
