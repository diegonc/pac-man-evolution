#include "reloj.h"

S_ptr<Reloj> Reloj::instancia;

S_ptr<Reloj> Reloj::get_instancia(){
	//lo implemento con smart pointers para no tener memory leaks
	if(instancia.es_nulo() )
		instancia = S_ptr<Reloj>(new Reloj());
	return (instancia);
}	

Reloj::Reloj(){
	gettimeofday(&this->hora_inicio, NULL);
}

Reloj::~Reloj(){}

unsigned int Reloj::get_hora_actual(){
	unsigned int hora_en_milisegundos = 0;
	gettimeofday(&this->hora_actual, NULL);		
	
	hora_en_milisegundos += (hora_actual.tv_sec - hora_inicio.tv_sec) * 1000;
	hora_en_milisegundos += (hora_actual.tv_usec - hora_inicio.tv_usec) / 1000;
		
	return hora_en_milisegundos;
}

double Reloj::get_hora_actual_decimal(){
	double hora_en_milisegundos = 0;
	gettimeofday(&this->hora_actual, NULL);		
	
	hora_en_milisegundos += (hora_actual.tv_sec - hora_inicio.tv_sec) * 1000;
	hora_en_milisegundos += (hora_actual.tv_usec - hora_inicio.tv_usec) / 1000;
		
	return hora_en_milisegundos;
}
