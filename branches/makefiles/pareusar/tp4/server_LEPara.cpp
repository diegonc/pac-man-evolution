#include "server_LEPara.h"

LEPara::LEPara( const std::string& tren, const std::string& anden, bool libre )
    : tren( tren ), anden( anden ), libre( libre )
{

}

void LEPara::print( std::ostream& out ) const
{
    print_time( out );
    out << tren << " PARA " << anden;
    out << ( libre ? " LIBRE" : " OCUPADO" ) << '\n';
}
