//Header
#ifndef Modelo_h_
#define Modelo_h_

//Incluyo las librerias necesarias
#include <editor/mundo.h>
#include <common/observable.h>

using namespace std;

/* CLASE MODELO: Esta clase representa el modelo del editor de mapas. Contiene la representacion del
   mundo en memoria y permite almacenarlo en el disco en formato xml. Tambien se encarga de controlar
   que los mapas sean consistentes (no tengan mas de 1 componente conexa).
   Tiene una unica instancia (singleton).   */

class Modelo : public Observable {

	//Atributos
	private:
		Mundo* mundo; //Referencia al mundo contenido en el modelo
	
		static Modelo* instancia; //Referencia a la unica instancia del programa

	/* Constructor: Inicializa el modelo, crea un nuevo mundo vacio. */
	Modelo();
	
	/* Pongo al constructor de copia como privado para que no se pueda copiar al singleton */
	Modelo(const Modelo &mod){}

	/* Destructor: Libera los recursos consumidos por el modelo. */
	~Modelo();

	public:
		
	/* Get Instance: Devuelve la unica instancia del programa. Si no existe la crea.  */
	static Modelo* get_instance();
		
	/* Get Mundo: Devuelve una referencia al mundo contenido en el modelo */
	Mundo* get_mundo();
	
	/* Set Mundo: Elimina el mundo contenido actualemente en el modelo y coloca al pasado como
	   parametro como nuevo mundo. El modelo se encarga de eliminarlo. */
	void set_mundo(Mundo* nuevo_mundo);
	
	/* Destroy: Se encarga de liberar los recursos consumidos por el modelo */
	static void destroy();

};

#endif
