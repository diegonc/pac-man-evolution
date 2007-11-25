#include "Posicion.h"

Posicion::Posicion(Tipo_Coordenada x = 0, Tipo_Coordenada y = 0){
	this->set_x(x);
	this->set_y(y);	
}
Tipo_Coordenada Posicion::get_x(){
	return this->x;
}
void Posicion::set_x(Tipo_Coordenada x_nuevo){
	if(x_nuevo >= 0)
		this->x = x_nuevo;
}
Tipo_Coordenada Posicion::get_y(){
	return this->y;	
}
void Posicion::set_y(Tipo_Coordenada y_nuevo){
	if(y_nuevo >= 0)
		this->y = y_nuevo;	
}
bool Posicion::operator==(Posicion &p){
	if(this->get_x() == p.get_x() && this->get_y() == p.get_y() )
		return true;
	else
		return false;
}
