#include "MundoBasicImp.h"
#include "MapImpSet.h"

//S_ptr<MundoBajoNivel> MundoBasicImp::instancia;

#include "EstructuralPasillo.h"
#include "EstructuralUnitario.h"
#include "../common/smart_pointer.h"
#include "ComestibleFactory.h"
#include "EstructuralUnitarioFactory.h"


#include <iostream>
MundoBasicImp::MundoBasicImp()
{
	this->cant_niveles = 0;

}

MundoBasicImp::~MundoBasicImp()
{
	this->mapas.clear();
}
MapaBajoNivel* MundoBasicImp::get_mapa_activo()
{
	if(! this->mapas.empty() )
		return mapas.front();

	return NULL;		
}

void MundoBasicImp::agregar_mapa(MapaBajoNivel* mapa){
	mapas.push_back(mapa);
	this->cant_niveles++;
}
int MundoBasicImp::cantidad_niveles(){
	return this->cant_niveles;
}
void MundoBasicImp::pasar_de_nivel(){
	if(! this->mapas.empty() ){
		MapaBajoNivel * mapa = mapas.front();
		mapas.pop_front();
		delete mapa;	
	}
}
