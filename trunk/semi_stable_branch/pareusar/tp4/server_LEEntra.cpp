#include "server_LEEntra.h"


LEEntra::LEEntra( const std::string& tren, const std::string& anden, int t )
    : tren( tren ), anden( anden ), espera( t )
{

}

void LEEntra::print( std::ostream& out ) const
{
    print_time( out );
    out << tren << " ENTRA " << anden << " ESPERA " << espera << '\n';
}
