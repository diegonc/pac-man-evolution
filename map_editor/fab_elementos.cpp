//Header
#include "fab_elementos.h"

/* CLASE FABRICA ELEMENTOS: Clase que se encarga de encapsular la creacion de elementos de cualquier tipo (modificadores
o estructurales). */

/* Construir: */

S_ptr<Elemento> Fab_Elementos::construir (TipoElem tipo, int pos_x, int pos_y, Orientacion orientacion){
	S_ptr<Elemento> elemento;
	switch (tipo) {
		case PASILLO:
			elemento = construir_pasillo(pos_x, pos_y, orientacion);
			break;
		case ESQ:
			elemento = construir_esquina(pos_x, pos_y, orientacion);
			break;
		case CASA:
			elemento = construir_casa(pos_x, pos_y, orientacion);
			break;
		case PWUP: {
			S_ptr<Elemento> power_up (new Power_Up(pos_x, pos_y));
			elemento = power_up;
			break;
		}
		case BONUS: {
			S_ptr<Elemento> bonus (new Bonus(pos_x, pos_y));
			elemento = bonus;
			break;
		}
		case SALIDA:{
			S_ptr<Elemento> salida (new Salida(pos_x, pos_y));
			elemento = salida;
			break;
		}
	}
	return elemento;
}

/* Construir Pasillo: */

S_ptr<Elemento> Fab_Elementos::construir_pasillo (int pos_x, int pos_y, Orientacion orientacion){
	S_ptr<Elemento> elemento;
	switch (orientacion) {
		case ESTE:
		case OESTE: {
			S_ptr<Elemento> pas_horiz (new PasilloHoriz(pos_x, pos_y));
			elemento = pas_horiz;
			break;
			}
		case NORTE:
		case SUR: {
			S_ptr<Elemento> pas_vert (new PasilloVert(pos_x, pos_y));
			elemento = pas_vert;
			break;
			}
	}
	return elemento;
}

/* Construir Esquina: */

S_ptr<Elemento> Fab_Elementos::construir_esquina (int pos_x, int pos_y, Orientacion orientacion){
	S_ptr<Elemento> elemento;
	switch (orientacion) {
		case ESTE: {
			S_ptr<Elemento> esq_este (new EsqEste(pos_x, pos_y));
			elemento = esq_este;
			break;
		}
		case OESTE: {
			S_ptr<Elemento> esq_oeste (new EsqOeste(pos_x, pos_y));
			elemento = esq_oeste;
			break;
		}
		case NORTE: {
			S_ptr<Elemento> esq_norte (new EsqNorte(pos_x, pos_y));
			elemento = esq_norte;
			break;
		}
		case SUR: {
			S_ptr<Elemento> esq_sur (new EsqSur(pos_x, pos_y));
			elemento = esq_sur;
			break;
		}
	}
	return elemento;
}

/* Construir Casa: */

S_ptr<Elemento> Fab_Elementos::construir_casa (int pos_x, int pos_y, Orientacion orientacion){
	S_ptr<Elemento> elemento;
	switch (orientacion) {
		case ESTE: {
			/*S_ptr<Elemento> casa_este (new CasaEste(pos_x, pos_y));
			elemento = casa_este;
			break;*/
		}
		case OESTE: {
			/*S_ptr<Elemento> casa_oeste (new CasaOeste(pos_x, pos_y));
			elemento = casa_oeste;
			break;*/
		}
		case NORTE: {
			/*S_ptr<Elemento> casa_norte (new CasaNorte(pos_x, pos_y));
			elemento = casa_norte;
			break;*/
		}
		case SUR: {
			S_ptr<Elemento> casa_sur (new CasaSur(pos_x, pos_y));
			elemento = casa_sur;
			break;
		}
	}
	return elemento;
}
