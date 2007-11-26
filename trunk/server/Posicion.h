#ifndef __POSICION_H__
#define __POSICION_H__

typedef double Tipo_Coordenada;
class Posicion{
	
	
	private:
		Tipo_Coordenada x;
		Tipo_Coordenada y;
	public:
		Posicion(Tipo_Coordenada x = 0.0, Tipo_Coordenada y = 0.0);
		
		Posicion( const Posicion &p);
	
		Tipo_Coordenada get_x() const;
			
		void set_x(Tipo_Coordenada x_nuevo);
			
		Tipo_Coordenada get_y() const;
			
		void set_y(Tipo_Coordenada y_nuevo);
			
		bool operator==(const Posicion &p);
};
#endif /*__POSICION_H__*/