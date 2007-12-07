#include "server_LETermina.h"

LETermina::LETermina( const std::string& tren ) : tren( tren )
{

}

void LETermina::print( std::ostream& out ) const
{
    print_time( out );
    out << tren << " TERMINA\n";
}
