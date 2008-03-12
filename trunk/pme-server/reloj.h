#ifndef CLASS_RELOJ
#define CLASS_RELOJ

/*****************************************************************************
-	Esta clase permite calcular en milisegundos, el tiempo transcurrido desde
	que se lo inicia.
*****************************************************************************/

#include <common/smart_pointer.h>
#include <sys/time.h>

class Reloj{
	private:
		
		typedef struct timeval t_tiempo;		
	
		Reloj();
		//hora re referencia sobre la cual se toma el tiempo
		t_tiempo hora_inicio;
		t_tiempo hora_actual;
		//instancia ya que es singleton
		static S_ptr<Reloj> instancia;

	public:
		static S_ptr<Reloj> get_instancia();
	
		~Reloj();
			
		unsigned int get_hora_actual();
		
		double get_hora_actual_decimal();
};

#endif
