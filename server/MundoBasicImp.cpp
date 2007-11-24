#include "MundoBasicImp.h"
#include "MapImpMatriz.h"

//S_ptr<Mundo> MundoBasicImp::instancia;

MundoBasicImp::MundoBasicImp(std::string ruta_mundo)
{
	Mapa * mapa_nuevo = new MapaImpMatriz(7,7);
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
