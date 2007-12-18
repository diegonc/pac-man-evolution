#ifndef CLASS_COMPARADOR
#define CLASS_COMPARADOR

/***************************************************************************
-	Define una interfaz para poder ser utilizada para comparar. 
-	Requiere que se redefina el operador () para poder ser utilizado como
	una funcion de comparacion.
	
***************************************************************************/

class Comparador{
	
	public:

		virtual ~Comparador(){}
		
		virtual bool operator()(void *valor1, void *valor2)=0;
	
};

#endif
