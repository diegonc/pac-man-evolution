#include "MundoBasicImp.h"
#include "MapImpSet.h"

//S_ptr<MundoBajoNIvel> MundoBasicImp::instancia;

#include "EstructuralPasillo.h"
#include "EstructuralUnitario.h"
#include "../common/smart_pointer.h"
#include "ComestibleFactory.h"



#include <iostream>
MundoBasicImp::MundoBasicImp(std::string ruta_mundo)
{
	S_ptr<MapaBajoNivel> mapa_nuevo = new MapaImpSet(1,4);
	/************************************************************************
		CREO PARA PROBAR UN MAPITA DEL ESTILO

		--- --- --- ---
	   | p |   |   | f |
	    --- --- --- ---
	************************************************************************/

	Comestible::Enum_Comestible  a = Comestible::quesito;
	Comestible::Enum_Comestible  b = Comestible::power_up;
	
	Posicion p(0.0,0.0);
	S_ptr<EstructuralUnitario> e_nuevo(new EstructuralPasillo(a,p));
	
	e_nuevo->set_posicion(p);
	mapa_nuevo->agregar_estructural(e_nuevo);

	Posicion p1(1.0,0.0);
	//S_ptr<EstructuralUnitario> e_nuevo1(new EstructuralPasillo(b));
	S_ptr<EstructuralUnitario> e_nuevo1(new EstructuralPasillo(a, p1));
	mapa_nuevo->agregar_estructural(e_nuevo1);

	Posicion p2(2.0,0.0);
	S_ptr<EstructuralUnitario> e_nuevo2(new EstructuralPasillo(a, p2));
		
	mapa_nuevo->agregar_estructural(e_nuevo2);

	Posicion p3(3.0,0.0);
	S_ptr<EstructuralUnitario> e_nuevo3(new EstructuralPasillo(a, p3));
		
	mapa_nuevo->agregar_estructural(e_nuevo3);

	Posicion p4(1.0,1.0);
	S_ptr<EstructuralUnitario> e_nuevo4(new EstructuralPasillo(a, p4));
	
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
	mapas.push_back( mapa_nuevo );
}

MundoBasicImp::~MundoBasicImp()
{
	this->mapas.clear();
}
/*
S_ptr<MundoBajoNIvel> MundoBasicImp::get_instancia()
{
	if( instancia.es_nulo() )
		instancia = S_ptr<MundoBajoNIvel>(new MundoBasicImp());

	return instancia;
}
*/
MapaBajoNivel& MundoBasicImp::get_mapa_activo()
{
	return *mapas.back();
}
