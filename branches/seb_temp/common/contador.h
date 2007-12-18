/*****************CLASE CONTADOR******************/

/* Clase que representa un contador de referencia,
   es decir: Un contador que puede ser usado
   por varios objetos. */

/******************* HEADER **********************/

#ifndef Contador_h_
#define Contador_h_

/*************************************************/

/* CLASE CONTADOR */

class Contador {
	//Atributos
	private:
		int cont; //Variable que lleva la cuenta
	//Metodos
	public:
		Contador(){
			this->cont = 0;
		}
		/* Incrementar: Incrementa en 1 el contador */
		void incrementar() {
			this->cont++;
		}
		/* Decrementar: Decrementa en 1 el contador */
		void decrementar() {
			this->cont--;
		}
		/* Get Valor: Devuelve el valor del contador */
		int getValor() {
			return this->cont;
		}
};

#endif

/*************************************************/
