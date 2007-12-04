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

enum TipoElem { PASILLO, ESQ, BIFUR, CRUCE, CASA, PORTAL, SALIDA, PWUP, BONUS };

//Defino el tipo enumerado que contiene todas las orientaciones posibles para los elementos

enum Orientacion { NULA, ESTE, OESTE, NORTE, SUR };

//Defino los tamaños de las fichas

#define PAS_HORIZ_ANCHO 3
#define PAS_HORIZ_ALTO 1
#define PAS_VERT_ANCHO 1
#define PAS_VERT_ALTO 3
#define ESQ_ANCHO 2
#define ESQ_ALTO 2

//Defino rutas de imagenes

#define RUTA_ESQ_ESTE "./imagenes/esq_este.jpg"
#define RUTA_ESQ_OESTE "./imagenes/esq_oeste.jpg"
#define RUTA_ESQ_NORTE "./imagenes/esq_norte.jpg"
#define RUTA_ESQ_SUR "./imagenes/esq_sur.jpg"
#define RUTA_PAS_HORIZ "./imagenes/pas_horiz.jpg"
#define RUTA_PAS_VERT "./imagenes/pas_vert.jpg"
#define RUTA_POWER_UP "./imagenes/power_up.png"
#define RUTA_BONUS "./imagenes/frutita.png"
#define RUTA_VACIO "./imagenes/vacio.jpg"

#endif
