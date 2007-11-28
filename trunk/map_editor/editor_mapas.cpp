#include "gui.h"
#include "modelo.h"
#include "mundo.h"
#include <iostream>

using namespace std;

//Funcion principal

int main(int argc, char *argv[])
{

  //Creo la interfaz grafica
  GUI* gui = new GUI(argc, argv);
  //La hago arrancar
  gui->start();
  //Uno la interfaz grafica con el hilo principal, cuando termina
  gui->join(gui);
  //Elimino la interfaz grafica
  delete(gui);
/*
  //Creo un modelo
  Modelo* modelo = new Modelo();
  //Obtengo su mundo
  Mundo* mundo = modelo->get_mundo();
  //Agrego un nivel de 10 x 10
  mundo->agregar_nivel(10, 10);
  //Intento agregar pasillos al nivel
  mundo->agregar_elemento(PASILLO, 1, 0, 1, ESTE);
  mundo->agregar_elemento(PASILLO, 1, 1, 1, ESTE);
  mundo->agregar_elemento(PASILLO, 1, 0, 4, ESTE);
  mundo->agregar_elemento(ESQ, 1, 0, 7, SUR);
  mundo->agregar_elemento(PASILLO, 1, 0, 4, NORTE);
  mundo->agregar_elemento(PASILLO, 1, 1, 5, NORTE);
  mundo->agregar_elemento(PASILLO, 1, 8, 6, NORTE);
  mundo->agregar_elemento(PWUP, 1, 0, 2, NULA);
  mundo->agregar_elemento(PWUP, 1, 8, 8, NULA);
  mundo->agregar_elemento(PWUP, 1, 1, 7, NULA);
  //Imprimo el nivel
  mundo->imprimir_nivel(1);

  delete(modelo);*/

  return 0;

}
