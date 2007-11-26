#ifndef __BUFFERREADER_H__
#define __BUFFERREADER_H__

class BufferReader
{
	public:
		virtual ~BufferReader(){}

		virtual void recibir( char* b, unsigned int n ) = 0;
};

#endif /* __BUFFERREADER_H__ */
