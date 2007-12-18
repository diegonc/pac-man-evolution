#include "SocketReader.h"

SocketReader::SocketReader( Socket& sock ) : sock( sock )
{
}

void SocketReader::recibir( char* b, unsigned int n )
{
	sock.recibir( b, n );
}
