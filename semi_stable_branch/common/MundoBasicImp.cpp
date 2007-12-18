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
	/*S_ptr<MapaBajoNivel> mapa_nuevo = new MapaImpSet(1,4);
	/************************************************************************
		CREO PARA PROBAR UN MAPITA DEL ESTILO

		--- --- --- ---
	   | p |   |   | f |
	    --- --- --- ---
	***********************************************************************

	EstructuralUnitarioFactory fab;
	
	Comestible::Enum_Comestible  a = Comestible::quesito;
	Comestible::Enum_Comestible  b = Comestible::power_up;
	
	EstructuralUnitario::Enum_Estructural e = EstructuralUnitario::Pasillo;
	
	Posicion p(0.0,0.0);
	S_ptr<EstructuralUnitario> e_nuevo = fab.construir(p,e,a);
	mapa_nuevo->agregar_estructural(e_nuevo);

	Posicion p1(1.0,0.0);
	//S_ptr<EstructuralUnitario> e_nuevo1(new EstructuralPasillo(b));
	S_ptr<EstructuralUnitario> e_nuevo1 = fab.construir(p1,e,a);
	mapa_nuevo->agregar_estructural(e_nuevo1);

	Posicion p2(2.0,0.0);
	S_ptr<EstructuralUnitario> e_nuevo2 = fab.construir(p2,e,a);
	mapa_nuevo->agregar_estructural(e_nuevo2);

	Posicion p3(3.0,0.0);
	S_ptr<EstructuralUnitario> e_nuevo3 = fab.construir(p3,e,a);	
	mapa_nuevo->agregar_estructural(e_nuevo3);

	Posicion p4(1.0,1.0);
	S_ptr<EstructuralUnitario> e_nuevo4 = fab.construir(p4,e,a);
	mapa_nuevo->agregar_estructural(e_nuevo4);

	e_nuevo->set_derecha(e_nuevo1);
	e_nuevo1->set_izquierda(e_nuevo);
	e_nuevo1->set_derecha(e_nuevo2);
	e_nuevo2->set_izquierda(e_nuevo1);
	e_nuevo2->set_derecha(e_nuevo3);
	e_nuevo3->set_izquierda(e_nuevo2);
	e_nuevo4->set_arriba(e_nuevo1);
	e_nuevo1->set_abajo(e_nuevo4);

	/////////////////////////////////////////////////////////////////////////
	
	agregar_mapa( mapa_nuevo );*/
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
	if(! this->mapas.empty() )
		mapas.pop_front();
}
