#include "Posicion.h"

Posicion::Posicion(Tipo_Coordenada x, Tipo_Coordenada y){
	this->set_x(x);
	this->set_y(y);	
}
Posicion::Posicion(const Posicion &p){
	this->x = p.x;
	this->y = p.y;
}
Tipo_Coordenada Posicion::get_x() const{
	return this->x;
}
void Posicion::set_x(Tipo_Coordenada x_nuevo){
	//if(x_nuevo >= 0)
		this->x = x_nuevo;
}
Tipo_Coordenada Posicion::get_y() const{
	return this->y;	
}
void Posicion::set_y(Tipo_Coordenada y_nuevo){
	//if(y_nuevo >= 0)
		this->y = y_nuevo;	
}
bool Posicion::operator==(const Posicion &p) {
	if(this->get_x() == p.get_x() && this->get_y() == p.get_y() )
		return true;
	else
		return false;
}
void Posicion::incrementar(Tipo_Coordenada cantidad, Direccion &direccion){
	if(direccion.get_dir() == Direccion::Norte)
		this->set_y(this->get_y() - cantidad);
	else{
		if(direccion.get_dir() == Direccion::Sur)
			this->set_y(this->get_y() + cantidad);
		else{
			if(direccion.get_dir() == Direccion::Este)
				this->set_x(this->get_x() + cantidad);
			else
				this->set_x(this->get_x() - cantidad);
			
		}
	}
}
