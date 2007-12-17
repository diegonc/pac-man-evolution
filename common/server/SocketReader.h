#ifndef __SOCKETREADER_H__
#define __SOCKETREADER_H__

#include <common/socket.h>
#include <server/BufferReader.h>

class SocketReader : public BufferReader
{
	private:
		Socket& sock;

	public:
		SocketReader( Socket& sock );

		void recibir( char* b, unsigned int n );
};

#endif /* __SOCKETREADER_H__ */
