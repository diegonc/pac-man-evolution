#include "OperacionStatus.h"

#include <math.h>
#include <server/PacMan.h>
#include <server/Fantasma.h>

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
		Jug->get_personaje()->matar();
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
//    std::cout<< "el " << ((PosJ.esPacman)?"Pacman":"Fantasma") << " esta en la posicion " << Jug->get_posicion() << "\n";

}

void OperacionStatus::ejecutar(ModeloCommon &modelo){
    Jugador * Jug = NULL;

    std::list< Jugador * >::const_iterator itjugadores;
    bool Encontrado = false;
    int AnchoMapa = modelo.get_mundo().get_mapa_activo()->get_ancho();
    int AltoMapa  = modelo.get_mundo().get_mapa_activo()->get_alto();
    for (std::list<OperacionStatus::PosicionJugador>::iterator it=get_jugadores()->begin();((it!=get_jugadores()->end())&&(!Encontrado));++it){
		OperacionStatus::PosicionJugador& PosJ=*it;
		Jug= modelo.get_jugador(PosJ.ID);
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
			modelo.agregar_jugador(Jug);			
			ModificarPosicionJugador(Jug,PosJ,AnchoMapa,AltoMapa);	
		}
	}
	//itero sobre los personajes y al pacman le seteo el puntaje
/*	Encontrado=false;
    	for (std::list<OperacionStatus::PosicionJugador>::iterator it=get_jugadores()->begin();((it!=get_jugadores()->end())&&(!Encontrado));++it){
		OperacionStatus::PosicionJugador& PosJ=*it;
		Jug= ModeloServidor::get_instancia()->get_jugador(PosJ.ID);
		if (Jug != NULL){
		        if (Jug->get_personaje()->get_tipo()==Personaje::pacman){
			    Encontrado=true;
			    Jug->set_puntos(get_puntuacion());
			}			
		}
	}
	std::list<Jugador*> jugadModelo=ModeloServidor::get_instancia()->get_jugadores();
	std::list<Jugador*>::iterator itJug=jugadModelo.begin();
	while ()    */
	Encontrado=false;
	std::list<Jugador*> listajug = modelo.get_jugadores();
	for(std::list<Jugador*>::iterator itjugadores = listajug.begin();((itjugadores != listajug.end()) && (!Encontrado)); ++itjugadores){
		Jugador* Jug=*itjugadores;
	        if (Jug->get_personaje()->get_tipo()==Personaje::pacman){
		    Encontrado=true;
		    Jug->set_puntos(get_puntuacion());
		}			
	}

	//verifico de eliminar los jugadores q no me llegaron en el status
	for(std::list<Jugador*>::iterator itjugadores = listajug.begin();itjugadores != listajug.end(); ++itjugadores){
		Jugador* Jug=*itjugadores;
		Encontrado=false;
	        for (std::list<OperacionStatus::PosicionJugador>::iterator it=get_jugadores()->begin();((it!=get_jugadores()->end())&&(!Encontrado));
++it){
			OperacionStatus::PosicionJugador& PosJ=*it;			
			if (Jug->get_id()==PosJ.ID){
				Encontrado=true;			
			}
		}
		if (!Encontrado){
			modelo.quitar_jugador(Jug->get_id());		
		}
	}

    //los jugadores ya fueron seteados*/
	
    //itero sobre los comestibles
    Encontrado=false;
    for (std::list<OperacionStatus::PosicionElemento>::iterator it=get_elementos()->begin();((it!=get_elementos()->end())&&(!Encontrado));++it){
        OperacionStatus::PosicionElemento& PosE=*it;
	
		if (PosE.Estado){
			//esto solo se ejecuta para las cosas que aparecen durante el juego, digase power ups			
			modelo.get_mundo().get_mapa_activo()->refresh(PosE.Posic,PosE.Tipo);
		}else{
			modelo.get_mundo().get_mapa_activo()->refresh(PosE.Posic);
        }
    }
}
