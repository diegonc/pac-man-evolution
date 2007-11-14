#include "Modelo.h"


Modelo::Modelo(std::string ruta_mundo){
	cargar_modelo(ruta_mundo);
	
}

void Modelo::cargar_modelo(std::string ruta_mundo){
	this->mundo = new MundoBasicImp(ruta_mundo);
	
	
	
	/*TODO TRUCHAR OPERACIONES Y DESPUES REEMPLAZAR POR UN PARSER*/
}

Modelo::~Modelo(){
	
}

void Modelo::agregar_jugador(Tipo_Jugador jugador){
	
}
			
void Modelo::run(){

}
