//DEFINICIONES: Contiene todos los typedefs y definiciones de constantes necesarias para la implementacion del editor de mapas.

#ifndef definiciones_h_
#define definiciones_h_

//Defino el elemento nulo
#ifndef NULL
#define NULL 0
#endif

//Defino constantes necesarias

//Borde de la ventana principal
#define BORDE 1

//Titulo de la ventana principal
#define TITULO "PAC-MAN EVOLUTION - Editor de Mapas" 
#define N_ARCHIVO "Archivo" //Defino el nombre para el menu archivo
#define N_NUEVO "Nuevo" //Defino el nombre para el menu nuevo
#define N_ABRIR "Abrir" //Defino el nombre para el menu abrir
#define N_GUARDAR "Guardar" //Defino el nombre para el menu guardar
#define N_SALIR "Salir" //Defino el nombre para el menu salir

//Defino el tipo enumerado que contiene todos los tipos de elementos posibles

enum TipoElem { PASILLO, ESQ, BIFUR, CRUCE, CASA, PORTAL, SALIDA, PWUP, BONUS};

//Defino el tipo enumerado que contiene todas las orientaciones posibles para los elementos

enum Orientacion { NULA, ESTE, OESTE, NORTE, SUR };

#endif
