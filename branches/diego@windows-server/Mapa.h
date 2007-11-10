#ifndef __MAPA_H__
#define __MAPA_H__

class Mapa
{
	public:
		enum Direccion {
			Norte,
			Este,
			Sur,
			Oeste
		};
		
		void mover( int id, Direccion dir ) = 0;
};

#endif /* __MAPA_H__ */
