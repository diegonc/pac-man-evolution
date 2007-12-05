//Header
#include "traductor.h"

/* CLASE TRADUCTOR: Clase que se encarga de traducir un mundo de alto nivel (del editor),
   a un mundo de bajo nivel (para el servidor). */

/* Traducir: */

MundoBajoNivel* Traductor::traducir(Mundo* mundo){
	//Creo un mundo de bajo nivel a devolver
	MundoBajoNivel* mundo_bajo_nivel = new MundoBasicImp();
	//Recorro todos los niveles del mundo de alto nivel
	for (unsigned int cont = 0; cont < mundo->get_cant_niveles(); cont++){
		//Obtengo cada nivel y traduzco su mapa a mapa de bajo nivel
		S_ptr<Nivel> nivel = mundo->get_nivel(cont+1);
		S_ptr<MapaBajoNivel> mapa_bajo_nivel = this->traducir_mapa(nivel->get_mapa());
		//Agrego el mapa de bajo nivel al mundo de bajo nivel
		mundo_bajo_nivel->agregar_mapa(mapa_bajo_nivel);
	}
	return mundo_bajo_nivel; //Devuelvo el mundo de bajo nivel
}

/* Traducir Mapa: */

S_ptr<MapaBajoNivel> Traductor::traducir_mapa (Mapa* mapa){
	//Creo un mapa de bajo nivel a devolver
	S_ptr<MapaBajoNivel> mapa_bajo_nivel (new MapaImpSet(mapa->get_ancho(),mapa->get_alto()));
	//Recorro todos los casilleros del mapa de alto nivel
	for (int cont1 = 0; cont1 < mapa->get_alto(); cont1++)
		for (int cont2 = 0; cont2 < mapa->get_ancho(); cont2++){
			//Obtengo cada casillero, su estructural y su modif de alto nivel
			S_ptr<Casillero> casillero = mapa->get_casillero(cont1, cont2);
			S_ptr<Elemento> estructural = casillero->get_estructural();
			S_ptr<Elemento> modificador = casillero->get_modificador();
			Posicion pos(cont2, cont1);
			S_ptr<EstructuralUnitario>  estruct_bajo_nivel;
			//Si hay estructural en el casillero y es habitable, creo un estructural de bajo nivel y lo agrego al mapa de bajo nivel
			if ((!estructural.es_nulo()) && (estructural->es_habitable(cont1,cont2))) {
				//Creo una fabrica de estructurales unitarios (de bajo nivel)
				S_ptr<EstructuralUnitarioFactory> fabrica (new EstructuralUnitarioFactory());
				//Obtengo el tipo de estructural de bajo nivel, a partir del tipo de alto nivel
				EstructuralUnitario::Enum_Estructural tipoEstructural = this->trad_cod_elemento(estructural->get_tipo());
				//Si el estructural tiene un modificador
				if (!modificador.es_nulo()){
					//Obtengo el tipo de comestible de bajo nivel, a partir del tipo de alto nivel
					Comestible::Enum_Comestible  tipoComestible = this->trad_cod_elemento(modificador->get_tipo());
					//Creo un estructural de bajo nivel con los datos obtenidos
					estruct_bajo_nivel = fabrica->construir(pos, tipoEstructural, tipoComestible);
				} else //Si no tiene modif, creo un estructural con un quesito
					estruct_bajo_nivel = fabrica->construir(pos, tipoEstructural, Comestible::quesito);
				//Agrego el estructural al mapa de bajo nivel
				mapa_bajo_nivel->agregar_estructural(estruct_bajo_nivel);
			}
		}
	//Una vez cargado el mapa de bajo nivel, hago las conexiones entre los mismos
	this->realizar_conexiones(mapa, mapa_bajo_nivel);
	return mapa_bajo_nivel;
}

/* Realizar Conexiones: */

void Traductor::realizar_conexiones(Mapa* mapa, S_ptr<MapaBajoNivel> mapa_bajo_nivel){
	//Recorro todos los casilleros del mapa de alto nivel
	for (int cont1 = 0; cont1 < mapa->get_alto(); cont1++)
		for (int cont2 = 0; cont2 < mapa->get_ancho(); cont2++){
			//Obtengo cada casillero y su estructural
			S_ptr<Casillero> casillero = mapa->get_casillero(cont1, cont2);
			S_ptr<Elemento> estructural = casillero->get_estructural();
			//Si hay estructural
			if ((!estructural.es_nulo()) && (estructural->es_habitable(cont1, cont2))) {
					//Obtengo los casilleros en las 4 direcciones posibles de coneixon
					S_ptr<Casillero> c_arriba = mapa->get_casillero(cont1 - 1, cont2);
					S_ptr<Casillero> c_abajo = mapa->get_casillero(cont1 + 1, cont2);
					S_ptr<Casillero> c_izq = mapa->get_casillero(cont1, cont2 - 1);
					S_ptr<Casillero> c_der = mapa->get_casillero(cont1, cont2 + 1);
					//Realizo conexiones entre los estructurales de bajo nivel, cuando sea posible, en las 4 direcciones
					this->conectar_casilleros(casillero, c_arriba, mapa_bajo_nivel, NORTE);
					this->conectar_casilleros(casillero, c_abajo, mapa_bajo_nivel, SUR);
					this->conectar_casilleros(casillero, c_izq, mapa_bajo_nivel, OESTE);
					this->conectar_casilleros(casillero, c_der, mapa_bajo_nivel, ESTE);
			}
		}
}

/* Conectar Casilleros: */

void Traductor::conectar_casilleros(S_ptr<Casillero> origen, S_ptr<Casillero> destino, S_ptr<MapaBajoNivel> mapa_bajo_nivel, Orientacion orientacion){
		//Si hay casillero de origen y destino
		if ((!origen.es_nulo()) && (!destino.es_nulo())){
			//Obtengo los estructurales de alto nivel origen y destino
			S_ptr<Elemento> estruct_origen = origen->get_estructural();
			S_ptr<Elemento> estruct_destino = destino->get_estructural();
			if ((!estruct_destino.es_nulo()) && (estruct_destino->es_habitable(destino->get_pos_x(), destino->get_pos_y()))){
				//Obtengo los estructurales de bajo nivel que se corresponden con los de
				//alto nivel recien obtenidos.
				Posicion pos_origen(origen->get_pos_y(), origen->get_pos_x());
				S_ptr<EstructuralUnitario>  est_bajo_nivel_origen = mapa_bajo_nivel->get_estructural(pos_origen);
				Posicion pos_destino(destino->get_pos_y(), destino->get_pos_x());
				S_ptr<EstructuralUnitario>  est_bajo_nivel_destino = mapa_bajo_nivel->get_estructural(pos_destino);
				//std::cout << "Probando entre: (" << origen->get_pos_x() << "," << origen->get_pos_y() << ") y (" << destino->get_pos_x() << "," << destino->get_pos_y() << ") " << std::endl << std::flush;
				//Si existe una conexion en el mapa de alto nivel entre los estructurales origen y destino:
				if (estruct_origen->hay_conexion(origen->get_pos_x(), origen->get_pos_y(), destino->get_pos_x(), destino->get_pos_y())){
					//std::cout << "Conexion entre: (" << origen->get_pos_x() << "," << origen->get_pos_y() << ") y (" << destino->get_pos_x() << "," << destino->get_pos_y() << ") " << std::endl << std::flush;
					//Segun la orientacion de conexion, realizo la misma en el mapa de bajo nivel
					switch(orientacion){
						case NORTE: {
							est_bajo_nivel_origen->set_arriba(est_bajo_nivel_destino);
							break;}
						case SUR:{
							est_bajo_nivel_origen->set_abajo(est_bajo_nivel_destino);
							break;}
						case OESTE:{
							est_bajo_nivel_origen->set_izquierda(est_bajo_nivel_destino);
							break;}
						case ESTE:{
							est_bajo_nivel_origen->set_derecha(est_bajo_nivel_destino);
							}
					}
				}			
			}
		}
}

/* Trad Cod Elemento: */

char Traductor::trad_cod_elemento(TipoElem tipo){
		switch (tipo) {
			case CASA:
				return EstructuralUnitario::Casa_Fantasma;
			case SALIDA:
				return EstructuralUnitario::Salida_Pacman;
			case PWUP:
				return Comestible::power_up;
			case BONUS:
				return Comestible::frutita;
			default:
				return EstructuralUnitario::Pasillo;				
		}
}
