#include "OperacionStatus.h"

#include "../common/ComestibleFactory.h"
#include <math.h>
#include "../common/PacMan.h"
#include "../common/Fantasma.h"

unsigned int OperacionStatus::get_puntuacion(){
    return Puntuacion;
}

void OperacionStatus::set_puntuacion(unsigned int punt){
    Puntuacion=punt;
}

std::list<OperacionStatus::PosicionJugador>* OperacionStatus::get_jugadores(){
    return &Jugadores;
}

std::list<OperacionStatus::PosicionElemento>* OperacionStatus::get_elementos(){
    return &Elementos;
}



void OperacionStatus::ModificarPosicionJugador(Jugador * Jug,OperacionStatus::PosicionJugador& PosJ,int AnchoMapa,int AltoMapa){
    Posicion& PosModelo=Jug->get_posicion();
	int UltimaFila=AltoMapa-1;
    int UltimaColum=AnchoMapa-1;
//    std::cout << "la direccion es: " << ((PosJ.direcc)?"Norte/Este":"Sur/Oeste") << std::endl;
//    std::cout << "nroArista es: " << PosJ.Arista << std::endl;
    float Col=PosJ.Arista % AnchoMapa; //ver lo de la 1ra col y ultima
    int temp=(int)floor(PosJ.Arista / AnchoMapa); //par en verticales, impar en horizontales
    float Fila=floor(PosJ.Arista / (AnchoMapa * 2)); // ver 1ra fil y la ultima
    bool Vertical=!(temp%2); //corresponde a una arista vertical
 //   std::cout << "la arista es: " << (Vertical?"Vertical":"Horizontal") << std::endl;
//seteo el estado del Jugador;
    if (PosJ.esPacman){ //si recibo q es pacman
	//y en mi modelo es fantasma
		if (Jug->get_personaje()->get_tipo()==Personaje::fantasma){
			Personaje * personaje = new PacMan(&(*Jug));
			Jug->set_personaje(personaje);
	//		personaje->set_jugador(Jug);
		}
    }else{// si recibo q es fantasma
	//y en mi modelo es pacman
		if (Jug->get_personaje()->get_tipo()==Personaje::pacman){
			Personaje * personaje = new Fantasma(&(*Jug));
			Jug->set_personaje(personaje);
	//		personaje->set_jugador(Jug);
		}
    }

    if (PosJ.estaVivo){//si me llego q estaba vivo
	//si no esta vivo, lo revivo
		if (!(Jug->get_personaje()->esta_vivo())){
			  Jug->get_personaje()->revivir();
		}
		}else{ //si me llego q estaba muerto
		//si esta vivo, lo mato
		if (Jug->get_personaje()->esta_vivo()){
			  Jug->get_personaje()->revivir();
		}
    }
//END seteo el estado del jugador;



	double temporal;
    if (Vertical){
        if (PosJ.Posic<32){
            Fila=(Fila>0)?Fila-1:UltimaFila;
            PosJ.Posic+=32;
        }else{
            PosJ.Posic-=32;
        }
	temporal=PosJ.Posic;
	temporal/=64;
	temporal+=Fila;
        PosModelo.set_y(temporal);
        if (PosJ.direcc){
            Jug->get_direccion().set_dir(Direccion::Norte);
        }else{
            Jug->get_direccion().set_dir(Direccion::Sur);
        }
    }else{
        if (PosJ.Posic>32){
            Col=(Col<UltimaColum)?Col+1:0;
            PosJ.Posic-=32;
        }else{
            PosJ.Posic+=32;
        }
	temporal=PosJ.Posic;
	temporal/=64;
	temporal+=Col;
        PosModelo.set_x(temporal);
        if (PosJ.direcc){
            Jug->get_direccion().set_dir(Direccion::Este);
        }else{
            Jug->get_direccion().set_dir(Direccion::Oeste);
        }
    }
	//std::cout<< PosJ.Posic<<std::endl;

}

void OperacionStatus::ejecutar(ModeloServidor &modelo){
    std::cout << "comienzo ejecutar \n";
    Jugador * Jug = NULL;

    std::list< Jugador * >::const_iterator itjugadores;
    bool Encontrado = false;
    int AnchoMapa = modelo.get_mundo().get_mapa_activo()->get_ancho();
    int AltoMapa  = modelo.get_mundo().get_mapa_activo()->get_alto();
    for (std::list<OperacionStatus::PosicionJugador>::iterator it=get_jugadores()->begin();((it!=get_jugadores()->end())&&(!Encontrado));++it){
		OperacionStatus::PosicionJugador& PosJ=*it;
		Jug= ModeloServidor::get_instancia()->get_jugador(PosJ.ID);
		
		if (Jug != NULL){
			ModificarPosicionJugador(Jug,PosJ,AnchoMapa,AltoMapa);
		}else{	
			Jug=new Jugador(PosJ.ID);
			Personaje * personaje;
			if (PosJ.esPacman)
				personaje = new PacMan(Jug);
			else
				personaje = new Fantasma(Jug);
		
			Jug->set_personaje(personaje);			

			if (!PosJ.estaVivo){
				 Jug->get_personaje()->matar();
			}
			ModeloServidor::get_instancia()->agregar_jugador(Jug);			
			ModificarPosicionJugador(Jug,PosJ,AnchoMapa,AltoMapa);	
		}
	}
	//itero sobre los personajes y al pacman le seteo el puntaje
    bool salir=false;
    /*for(itjugadores = modelo.get_jugadores().begin();((itjugadores != modelo.get_jugadores().end()) && (!salir)); ++itjugadores){
        Jug= *itjugadores;
        //Actualizo puntaje del pacman
        if (Jug->get_personaje()->get_tipo()==Personaje::pacman){
            salir=true;
            //Jug->set_puntos(get_puntuacion());
        }
    }*/
    //los jugadores ya fueron seteados*/
	
	//itero sobre los comestibles
Encontrado=false;
    std::list<S_ptr<Comestible> > comestibles;
    ComestibleFactory fab;
	for (std::list<OperacionStatus::PosicionElemento>::iterator it=get_elementos()->begin();((it!=get_elementos()->end())&&(!Encontrado));++it){
        OperacionStatus::PosicionElemento& PosE=*it;

        int Col=PosE.Posic % AnchoMapa;
        int Fila=(int)floor(PosE.Posic / AnchoMapa);
	
		//std::cout << "Estado Comest:" <<PosE.Estado << "\n";
		if (PosE.Estado){
			Posicion p(Fila,Col);
			S_ptr<Comestible> c_nuevo(fab.construir(PosE.Tipo,p));
			comestibles.push_back(c_nuevo);            
			//agregar Elemento posicion(Col,Fila)
        }else{
            //eliminar Elemento posicion(Col,Fila)
        }
    }
//	modelo.get_mundo().get_mapa_activo()->refresh(comestibles);
    std::cout << "end ejecutar \n";
	
}
