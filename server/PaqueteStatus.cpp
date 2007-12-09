#include "PaqueteStatus.h"

namespace {
	const char ID = 2;
}

PaqueteStatus::PaqueteStatus(): Paquete(ID)
{

}

void PaqueteStatus::deserialize( InputBitStream& bs )
{
    Oper=new OperacionStatus;
    OperacionStatus::PosicionElemento PosElem;
    OperacionStatus::PosicionJugador PosJugad;
    unsigned int CantidadJugadores;
    unsigned int CantidadElementos;
    CantidadJugadores=bs.read(3);
    unsigned int temp;
    temp=bs.read(32);
    Oper->set_puntuacion(temp);
    for(unsigned int NroJug=0;NroJug<CantidadJugadores;++NroJug){
        PosJugad.ID=bs.read(16);
        PosJugad.Arista=bs.read(17);
        PosJugad.Posic=bs.read(6);
        PosJugad.direcc=bs.read(1);
        Oper->get_jugadores()->push_back(PosJugad);
    }

    CantidadElementos=bs.read(8);

    for(unsigned int NroElem=0;NroElem<CantidadElementos;++NroElem){
        PosElem.Tipo=(char)bs.read(4);
        PosElem.Orient=bs.read(2);
        PosElem.Estado=bs.read(2);
        PosElem.Posic=bs.read(16);
        Oper->get_elementos()->push_back(PosElem);
    }


}

void PaqueteStatus::serialize( OutputBitStream& bs )
{
		//COMENTADO POR ALAN PARA PODER COMPILAR
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

    ____________________________________________________________________________________________
    |                                      Posicion(40)                                         |
    --------------------------------------------------------------------------------------------
    |ID(16)          |Arista(17)             |Posicion(6)             |Direccion(1)             |
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
        bs.append( 3,  Model->get_jugadores().size() ); // Escribe campo auxiliar.
        bs.skip();
//fin cabecera

//ComienzoCuerpo
    //obtengo info
    S_ptr<Jugador> Jug;

    std::list< S_ptr<Jugador> >::const_iterator jugadores;
    bool Salir=false;
    unsigned int PuntajePacman=0;
    jugadores=Model->get_jugadores().begin();
    for(jugadores = Model->get_jugadores().begin();((jugadores != Model->get_jugadores().end()) && (!Salir)); ++jugadores){
        Jug= *jugadores;
        if (Jug->get_personaje()->get_tipo()==Personaje::pacman){
            Salir=true;
            PuntajePacman=Jug->get_puntos();
        }
    }

    //Puntuacion
        bs.append( 32,  PuntajePacman );
        bs.skip();
    //Posiciones Jugadores

        unsigned int AnchoMapa=Model->get_mundo().get_mapa_activo()->get_ancho();
        unsigned int AltoMapa=Model->get_mundo().get_mapa_activo()->get_alto();
        //itero sobre los jugadores
        jugadores=Model->get_jugadores().begin();
        for(jugadores = Model->get_jugadores().begin();((jugadores != Model->get_jugadores().end()) && (!Salir)); ++jugadores){
            Jug= *jugadores;

            Posicion P=Jug->get_posicion();
            int Fila=(int)floor(P.get_y());
            int Col=(int)floor(P.get_x());
            int AristaSup=Col+(Fila*AnchoMapa);
            unsigned int Arista;
            unsigned int PosCuantizada;
            unsigned char EsteONorte;
            int InicioCasillero;
            if (Jug->get_direccion().get_dir()%2){ //movimiento horizontal
                InicioCasillero=(int)floor(P.get_x());
                if (P.get_x()>=(InicioCasillero+0.5)){ //pasando la mitad
                    Arista=AristaSup+AnchoMapa;
                    PosCuantizada=(32*(P.get_x()-(InicioCasillero+0.5)));
                }else{
                    if (!Col){ //es primer fila
                        Arista=AristaSup+AnchoMapa-1;
                    }else{ //es otra
                        Arista=AristaSup+(2*AnchoMapa)-1; //elijo de la misma fila la ultima
                    }
                    PosCuantizada=32+(32*(InicioCasillero+0.5-P.get_x()));
                }

            }else{ //vertical
                InicioCasillero=(int)floor(P.get_y());
                if (P.get_y()>=(InicioCasillero+0.5)){ //despues de la mitad
                    Arista=AristaSup+(2*AnchoMapa);
                    PosCuantizada=(32*(P.get_y()-(InicioCasillero+0.5)));
                }else{//antes de la mitad
                    Arista=AristaSup;
                    PosCuantizada=32+(32*(InicioCasillero+0.5-P.get_y()));
                }
            }

            //puede haber dado inferior a la ultima fila
            Arista=Arista % (AnchoMapa*AltoMapa*2);

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

            //escribo el id del jugador
            bs.append( 16,  Jug->get_id());
            bs.append( 17,  Arista);
            bs.append( 6,  PosCuantizada);
            bs.append( 1,  EsteONorte);


        }

    //cantidad elementos
        std::list< S_ptr<Comestible> > lista_comestibles = Model->get_mundo().get_mapa_activo()->get_comestibles();
        bs.append( 8,  lista_comestibles.size());

    //Posiciones elementos
        std::list< S_ptr<Comestible> >::iterator itcomestibles;
        S_ptr<Comestible> comestible;


        //itero sobre los jugadores
        for(itcomestibles = lista_comestibles.begin(); itcomestibles != lista_comestibles.end(); ++itcomestibles){
            comestible = *itcomestibles;
            unsigned int tipoCom=comestible->get_tipo();

            unsigned int Orient=0;

            unsigned int Estado=1;

            Posicion P=comestible->get_posicion();
            int Fila=(int)floor(P.get_x());
            int Col=(int)floor(P.get_y());

            unsigned int PosCasillero=Col+(Fila*AnchoMapa);

            bs.append( 4,  tipoCom);
            bs.append( 2,  Orient);
            bs.append( 2,  Estado);
            bs.append( 16,  PosCasillero);


        }
}
