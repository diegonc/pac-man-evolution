#ifndef __POSICION_H__
#define __POSICION_H__

class Posicion{
	typedef double Tipo_Coordenada;
	private:
		Tipo_Coordenada x;
		Tipo_Coordenada y;
	public:
		Posicion(Tipo_Coordenada x = 0, Tipo_Coordenada y = 0);
		
		Tipo_Coordenada get_x();
			
		void set_x(Tipo_Coordenada x_nuevo);
			
		Tipo_Coordenada get_y();
			
		void set_y(Tipo_Coordenada y_nuevo);
			
		bool operator==(Posicion &p);
};
#endif /*__POSICION_H__*/
