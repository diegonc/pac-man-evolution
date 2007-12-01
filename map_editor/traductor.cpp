//Header
#include "traductor.h"

/* CLASE TRADUCTOR: Clase que se encarga de traducir un mundo de alto nivel (del editor),
   a un mundo de bajo nivel (para el servidor). */

/* Traducir: */

MundoBajoNivel* Traductor::traducir(Mundo* mundo){
	MundoBajoNivel* mundo_bajo_nivel = new MundoBasicImp();
	for (unsigned int cont = 0; cont < mundo->get_cant_niveles(); cont++){
		S_ptr<Nivel> nivel = mundo->get_nivel(cont+1);
		S_ptr<MapaBajoNivel> mapa_bajo_nivel = this->traducir_mapa(nivel->get_mapa());
		mundo_bajo_nivel->agregar_mapa(mapa_bajo_nivel);
	}
	return mundo_bajo_nivel;
}

/* Traducir Mapa: */

S_ptr<MapaBajoNivel> Traductor::traducir_mapa (Mapa* mapa){
	S_ptr<MapaBajoNivel> mapa_bajo_nivel (new MapaImpSet(mapa->get_ancho(),mapa->get_alto()));
	for (unsigned int cont1 = 0; cont1 < mapa->get_alto(); cont1++)
		for (unsigned int cont2 = 0; cont2 < mapa->get_ancho(); cont2++){
			S_ptr<Casillero> casillero = mapa->get_casillero(cont1, cont2);
			S_ptr<Estructural> estructural = casillero->get_estructural();
			S_ptr<Modificador> modificador = casillero->get_modificador();
			Posicion pos(cont2, cont1);
			S_ptr<EstructuralUnitario>  estruct_bajo_nivel;
			if (!estructural.es_nulo()) {
				const char tipoEstructural = this->trad_cod_elemento(estructural->get_tipo());
				if (!modificador.es_nulo()){
					Comestible::Enum_Comestible  tipoComestible = this->trad_cod_elemento(modificador->get_tipo());
					estruct_bajo_nivel = new EstructuralPasillo(tipoComestible,pos);
				} else
					estruct_bajo_nivel = new EstructuralPasillo(Comestible::quesito,pos);
				mapa_bajo_nivel->agregar_estructural(estruct_bajo_nivel);
			}
		}
	this->realizar_conexiones(mapa, mapa_bajo_nivel);
	return mapa_bajo_nivel;
}

/* Realizar Conexiones: */

void Traductor::realizar_conexiones(Mapa* mapa, S_ptr<MapaBajoNivel> mapa_bajo_nivel){
	for (unsigned int cont1 = 0; cont1 < mapa->get_alto(); cont1++)
		for (unsigned int cont2 = 0; cont2 < mapa->get_ancho(); cont2++){
			S_ptr<Casillero> casillero = mapa->get_casillero(cont1, cont2);
			S_ptr<Estructural> estructural = casillero->get_estructural();
			if (!estructural.es_nulo()) {
					S_ptr<Casillero> c_arriba = mapa->get_casillero(cont1 - 1, cont2);
					S_ptr<Casillero> c_abajo = mapa->get_casillero(cont1 + 1, cont2);
					S_ptr<Casillero> c_izq = mapa->get_casillero(cont1, cont2 - 1);
					S_ptr<Casillero> c_der = mapa->get_casillero(cont1, cont2 + 1);
					
					this->conectar_casilleros(casillero, c_arriba, mapa_bajo_nivel, NORTE);
					this->conectar_casilleros(casillero, c_abajo, mapa_bajo_nivel, SUR);
					this->conectar_casilleros(casillero, c_izq, mapa_bajo_nivel, OESTE);
					this->conectar_casilleros(casillero, c_der, mapa_bajo_nivel, ESTE);
			}
		}
}

/* Conectar Casilleros: */

void Traductor::conectar_casilleros(S_ptr<Casillero> origen, S_ptr<Casillero> destino, S_ptr<MapaBajoNivel> mapa_bajo_nivel, Orientacion orientacion){
		if ((!origen.es_nulo()) && (!destino.es_nulo())){
			S_ptr<Estructural> estruct_origen = origen->get_estructural();
			S_ptr<Estructural> estruct_destino = destino->get_estructural();
			if (!estruct_destino.es_nulo()){
				Posicion pos_origen(origen->get_pos_y(), origen->get_pos_x());
				S_ptr<EstructuralUnitario>  est_bajo_nivel_origen = mapa_bajo_nivel->get_estructural(pos_origen);
				Posicion pos_destino(destino->get_pos_y(), destino->get_pos_x());
				S_ptr<EstructuralUnitario>  est_bajo_nivel_destino = mapa_bajo_nivel->get_estructural(pos_destino);
				if (estruct_origen->hay_conexion(origen->get_pos_x(), origen->get_pos_y(), destino->get_pos_x(), destino->get_pos_y())){
					switch(orientacion){
						case NORTE:
							est_bajo_nivel_origen->set_arriba(est_bajo_nivel_destino);
						case SUR:
							est_bajo_nivel_origen->set_abajo(est_bajo_nivel_destino);
						case OESTE:
							est_bajo_nivel_origen->set_izquierda(est_bajo_nivel_destino);
						case ESTE:
							est_bajo_nivel_origen->set_derecha(est_bajo_nivel_destino);
					}
				}			
			}
		}
}

/* Trad Cod Elemento: */

char Traductor::trad_cod_elemento(TipoElem tipo){
		switch (tipoElem) {
			case CASA:
				return TIPO_CASA_FANTASMA;
			case PWUP:
				return Comestible::power_up;
			case BONUS:
				return Comestible::frutita;
			default:
				return -1;				
		}
}
