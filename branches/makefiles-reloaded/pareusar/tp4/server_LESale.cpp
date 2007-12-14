#include "server_LESale.h"

LESale::LESale( const std::string& tren, const std::string& anden )
    : tren( tren ), anden( anden )
{

}

void LESale::print( std::ostream& out ) const
{
    print_time( out );
    out << tren << " SALE " << anden << '\n';
}
