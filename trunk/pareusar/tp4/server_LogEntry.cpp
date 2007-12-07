#include "server_LogEntry.h"
#include "server_LESale.h"
#include "server_LEPara.h"
#include "server_LEEntra.h"
#include "server_LETermina.h"
#include "server_LEDummy.h"

LogEntry* LogEntry::crear_sale( const std::string& tren, const std::string& anden )
{
    return new LESale( tren, anden );
}

LogEntry* LogEntry::crear_para( const std::string& tren, const std::string& anden, bool libre )
{
    return new LEPara( tren, anden, libre );
}

LogEntry* LogEntry::crear_entra( const std::string& tren, const std::string& anden, int espera )
{
    return new LEEntra( tren, anden, espera );
}

LogEntry* LogEntry::crear_termina( const std::string& tren )
{
    return new LETermina( tren );
}

LogEntry* LogEntry::crear_dummy( )
{
    return new LEDummy();
}

void LogEntry::print_time( std::ostream& out ) const
{
    out << std::setfill('0') << std::setw(6);
    out << timestamp.to_mili();
    out << ' ';
}

std::string LogEntry::raw_form() const
{
    std::ostringstream o;
    print( o );
    return o.str();
}

void LogEntry::add_refs( int n )
{
    Mutex::Locker lm( m );
    ref_count += n;
}

void LogEntry::destruir()
{
    m.lock();
    if( ref_count == 1 ) {
        m.unlock();
        delete this;
    } else {
        ref_count--;
        m.unlock();
    }
}
