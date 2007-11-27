#include "MundoBasicImp.h"
#include "MapImpSet.h"

//S_ptr<Mundo> MundoBasicImp::instancia;

#include "EstructuralPasillo.h"
#include "Estructural.h"
#include "../common/smart_pointer.h"
#include "ComestibleFactory.h"



#include <iostream>
MundoBasicImp::MundoBasicImp(std::string ruta_mundo)
{
	Mapa * mapa_nuevo = new MapaImpSet(1,4);
	/************************************************************************
		CREO PARA PROBAR UN MAPITA DEL ESTILO
	
		--- --- --- ---
	   | p |   |   | f |
	    --- --- --- ---
	************************************************************************/
	
	ComestibleFactory::Tipo_Comestible  a = ComestibleFactory::quesito;
	S_ptr<Estructural> e_nuevo(new EstructuralPasillo(a));
	Posicion p(0.0,0.0);
	mapa_nuevo->agregar_estructural(e_nuevo,p);
	
	S_ptr<Estructural> e_nuevo1(new EstructuralPasillo(a));
	Posicion p1(1.0,0.0);
	mapa_nuevo->agregar_estructural(e_nuevo1,p1);
		
	S_ptr<Estructural> e_nuevo2(new EstructuralPasillo(a));
	Posicion p2(2.0,0.0);
	mapa_nuevo->agregar_estructural(e_nuevo2,p2);
		
	S_ptr<Estructural> e_nuevo3(new EstructuralPasillo(a));
	Posicion p3(3.0,0.0);
	mapa_nuevo->agregar_estructural(e_nuevo3,p3);
	
	e_nuevo->set_derecha(e_nuevo1);
	e_nuevo1->set_izquierda(e_nuevo);
	e_nuevo1->set_derecha(e_nuevo2);
	e_nuevo2->set_izquierda(e_nuevo1);
	e_nuevo2->set_derecha(e_nuevo3);
	e_nuevo3->set_izquierda(e_nuevo2);
	
	/////////////////////////////////////////////////////////////////////////
	mapas.push_back( mapa_nuevo );
}

MundoBasicImp::~MundoBasicImp()
{
	delete mapas.back();/*???????*/
}
/*
S_ptr<Mundo> MundoBasicImp::get_instancia()
{
	if( instancia.es_nulo() )
		instancia = S_ptr<Mundo>(new MundoBasicImp());

	return instancia;
}
*/
Mapa& MundoBasicImp::get_mapa_activo()
{
	return *mapas.back();
}
