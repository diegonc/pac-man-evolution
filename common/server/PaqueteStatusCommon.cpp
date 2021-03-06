#include <server/PaqueteStatusCommon.h>

namespace {
	const char ID = 2;
}

PaqueteStatusCommon::PaqueteStatusCommon(): Paquete(ID)
{

}

PaqueteStatusCommon::PaqueteStatusCommon(std::list<NovedadComestible>* Noved,
		S_ptr<ModeloCommon> modelo):Paquete(ID)
{
	//se copia, todas cosas estaticas, excepto el smart pointer q redefine la asignacion
	this->Novedades=*Noved;
	this->jugadores = modelo->get_jugadores();
	this->ancho  = modelo->get_mundo().get_mapa_activo()->get_ancho();
	this->alto  = modelo->get_mundo().get_mapa_activo()->get_alto();
}

void PaqueteStatusCommon::deserialize( InputBitStream& bs )
{
 	Oper = NULL;

}

void PaqueteStatusCommon::serialize( OutputBitStream& bs )
{
//	S_ptr<ModeloServidor> Model = ModeloServidor::get_instancia();
    /*
    ____________________________________________________________________________________________
    |        Cabecera            |                       Cuerpo                                 |
    --------------------------------------------------------------------------------------------
    |Vers(2)|Tipo(3)|CantJugad(3)|Puntuac(32)|PosJugad(CantJug*40)|CantElem(8)|Elem(CantElem*24)|
    --------------------------------------------------------------------------------------------
    ____________________________________________________________________________________________
    |                                PosJugador(CantJug*40)                                     |
    --------------------------------------------------------------------------------------------
    |Posicion 0(40)          |... ... ... ... ... ... ... ... .|Posicion CantJug-1(40)          |
    --------------------------------------------------------------------------------------------


................... Mod
    ____________________________________________________________________________________________
    |                                      Posicion(40)                                         |
    --------------------------------------------------------------------------------------------
    |ID(16)          |Arista(17)             |Posicion(6)             |Direccion(1)             |
    --------------------------------------------------------------------------------------------
................... Modificacion :P
    ____________________________________________________________________________________________
    |                                      Posicion(40)                                         |
    --------------------------------------------------------------------------------------------
    |Vivo(1)  |Rol(1)  |ID(14)     |Arista(17)       |Posicion(6)        |Direccion(1)          |
    --------------------------------------------------------------------------------------------

    ____________________________________________________________________________________________
    |                                Elementos(CantElem*24)                                     |
    --------------------------------------------------------------------------------------------
    |Elemento 0(24)          |... ... ... ... ... ... ... ... |Elemento CantElem-1(24)          |
    --------------------------------------------------------------------------------------------

    ____________________________________________________________________________________________
    |                                      Elemento(24)                                         |
    --------------------------------------------------------------------------------------------
    |Tipo(4)          |Orientacion(2)             |Estado(2)             |Posicion(16)          |
    --------------------------------------------------------------------------------------------

    */


//ComienzoCabecera
    //version y tipo
        Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.

    //escribo la cantidad de jugadores
        bs.append( 3,  jugadores.size() ); // Escribe campo auxiliar.        
//fin cabecera

//ComienzoCuerpo
    //obtengo info
    Jugador * Jug;

    //std::list<Jugador *> lista_jugadores = Model->get_jugadores();
	std::list<Jugador * >::const_iterator jugit;
	
    bool Salir=false;
    unsigned int PuntajePacman=0;
    for(jugit = jugadores.begin();((jugit != jugadores.end()) && (!Salir)); ++jugit){
        Jug= *jugit;
        if (Jug->get_personaje()->get_tipo()==Personaje::pacman){
            Salir=true;
            PuntajePacman=Jug->get_puntos();
        }
    }

    //Puntuacion
        bs.append( 32,  PuntajePacman );
    //Posiciones Jugadores

//	MundoBajoNivel& m=Model->get_mundo();
//	S_ptr<MapaBajoNivel> mapa(m.get_mapa_activo());
//	unsigned int pedo=mapa->get_ancho();

        unsigned int AnchoMapa=ancho; //Model->get_mundo().get_mapa_activo()->get_ancho();

        unsigned int AltoMapa= alto; //Model->get_mundo().get_mapa_activo()->get_alto();
        //itero sobre los jugadores
        //jugadores=Model->get_jugadores().begin();
        for(jugit = jugadores.begin();((jugit != jugadores.end()) ); ++jugit){
            Jug= *jugit;

            Posicion P = Jug->get_posicion();
            int Fila=(int)floor(P.get_y());
            int Col=(int)floor(P.get_x());
            int AristaSup=Col+(Fila*(2*AnchoMapa));
            unsigned int Arista;
            unsigned int PosCuantizada;
            unsigned char EsteONorte;
            int InicioCasillero;
            if (Jug->get_direccion().get_dir()%2){ //movimiento horizontal
                InicioCasillero=(int)floor(P.get_x());
                if (P.get_x()>=(InicioCasillero+0.5)){ //pasando la mitad
                    Arista=AristaSup+AnchoMapa;
                    PosCuantizada=(64*(P.get_x()-(InicioCasillero+0.5)));
                }else{
                    if (Col){ //no es primer fila
                        Arista=AristaSup+AnchoMapa-1;
                    }else{ //es primerfila
                        Arista=AristaSup+(2*AnchoMapa)-1; //elijo de la misma fila la ultima
                    }
                    PosCuantizada=31+(64*(P.get_x() - InicioCasillero));
                }

            }else{ //vertical
                InicioCasillero=(int)floor(P.get_y());
                if (P.get_y()>=(InicioCasillero+0.5)){ //despues de la mitad
                    Arista=AristaSup+(2*AnchoMapa);
                    PosCuantizada=(64*(P.get_y()-(InicioCasillero+0.5)));
		    
			//puede haber dado inferior a la ultima fila
	            Arista=Arista % (AnchoMapa*AltoMapa*2);
                }else{//antes de la mitad
                    Arista=AristaSup;
                    PosCuantizada=31+(64*(P.get_y() - InicioCasillero));
                }

            }

            

            /* de esta forma

                a
            ____|____________
            |   |   |       |
            |-b-    |    ---|---b
            |___|___|_______|
            |   |   |       |
            |-c-a   |    ---|---c
            |___|___|_______|


            de esta forma las aristas q me sobran de arriba las uso para la mitad inferior de la ultima fila
            y las aristas q me sobran a la derecha las uso para la primer mitad de la primer columna
            */
            if ((Jug->get_direccion().get_dir()==Direccion::Norte) || (Jug->get_direccion().get_dir()==Direccion::Este)){
                EsteONorte=1;
            }else{
                EsteONorte=0;
            }

	    unsigned int estaVivo=(Jug->get_personaje()->esta_vivo())?1:0;
	    unsigned int esPacman=(Jug->get_personaje()->get_tipo()==Personaje::pacman)?1:0;

            //escribo el id del jugador
	    bs.append(1,estaVivo);
	    bs.append(1,esPacman);
            bs.append( 14,  Jug->get_id());
            bs.append( 17,  Arista);
            bs.append( 6,  PosCuantizada);
            bs.append( 1,  EsteONorte);


        }


	//cantidad elementos
        bs.append( 8,  (unsigned int) Novedades.size());

    //Posiciones elementos
        std::list< NovedadComestible >::iterator itNovcomestibles;
        
        //itero sobre los comestibles
        for(itNovcomestibles = Novedades.begin(); itNovcomestibles != Novedades.end(); ++itNovcomestibles){
            NovedadComestible& NC = *itNovcomestibles;
            unsigned int tipoCom=NC.get_comestible()->get_tipo();

            unsigned int Orient=0;

            unsigned int Estado=(NC.aparece()?1:0);

            Posicion P=NC.get_comestible()->get_posicion();
            int Fila=(int)floor(P.get_y());
            int Col=(int)floor(P.get_x());

            unsigned int PosCasillero=Col+(Fila*AnchoMapa);
            bs.append( 4,  tipoCom);
            bs.append( 2,  Orient);
            bs.append( 2,  Estado);
            bs.append( 16,  PosCasillero);
        }
}

Operacion* PaqueteStatusCommon::get_operacion()
{
	return Oper;
}
