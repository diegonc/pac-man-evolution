#ifndef __DIRECCION_H__
#define __DIRECCION_H__

class Direccion
{
	private:
		Direccion( int i );

	public:
		static Direccion Norte;
		static Direccion Sur;
		static Direccion Este;
		static Direccion Oeste;
	
	private:
		int dir;

	public:
		Direccion combinar( int i );
};

#endif /* __DIRECCION_H__ */
