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
#define CASA_ALTO 3
#define CASA_ANCHO 3
#define BIF_VERT_ALTO 3
#define BIF_VERT_ANCHO 2
#define BIF_HORIZ_ALTO 2
#define BIF_HORIZ_ANCHO 3
#define CRUCE_ALTO 3
#define CRUCE_ANCHO 3

//Defino rutas de imagenes

#define RUTA_ESQ_ESTE "./imagenes/esq_este.png"
#define RUTA_ESQ_OESTE "./imagenes/esq_oeste.png"
#define RUTA_ESQ_NORTE "./imagenes/esq_norte.png"
#define RUTA_ESQ_SUR "./imagenes/esq_sur.png"
#define RUTA_PAS_HORIZ "./imagenes/pas_horiz.png"
#define RUTA_PAS_VERT "./imagenes/pas_vert.png"
#define RUTA_POWER_UP "./imagenes/power_up.png"
#define RUTA_BONUS "./imagenes/frutita.png"
#define RUTA_SALIDA "./imagenes/salida.png"
#define RUTA_CASA_SUR "./imagenes/casa_sur.png"
#define RUTA_CASA_NORTE "./imagenes/casa_norte.png"
#define RUTA_CASA_ESTE "./imagenes/casa_este.png"
#define RUTA_CASA_OESTE "./imagenes/casa_oeste.png"
#define RUTA_BIF_SUR "./imagenes/bif_sur.png"
#define RUTA_BIF_NORTE "./imagenes/bif_norte.png"
#define RUTA_BIF_ESTE "./imagenes/bif_este.png"
#define RUTA_BIF_OESTE "./imagenes/bif_oeste.png"
#define RUTA_CRUCE "./imagenes/cruce.png"
#define RUTA_VACIO "./imagenes/vacio.png"
#define RUTA_MARCA "./imagenes/cruz.png"

//Defino las extensiones de los archivos del editor

#define EXT_MUNDO ".mdo"
#define EXT_NIVEL ".nvl"

//Defino los codigos y textos de los errores
#define E_NO_SALIDA_COD 1
#define E_NO_CASA_COD 2
#define E_NO_CONGR_COD 3
#define E_GUARDAR_INC_COD 4
#define E_CARGAR_INC_COD 5
#define E_MISMO_NOMBRE_COD 6
#define E_ALTO_INC_COD 7
#define E_ANCHO_INC_COD 8

#define E_NO_SALIDA_TXT "Error - No hay salida de pacman en el nivel: ";
#define E_NO_CASA_TXT "Error - No hay casa de fantasmas en el nivel: ";
#define E_NO_CONGR_TXT "Error - Hay elementos desconectados en el nivel: ";
#define E_GUARDAR_INC_TXT "Error - Se produjo un error guardando el mundo";
#define E_CARGAR_INC_TXT "Error - Se produjo un error cargando el mundo";
#define E_MISMO_NOMBRE_TXT "Error - Nombre Incorrecto: Ya existe otro nivel con ese nombre";
#define E_ALTO_INC_TXT "Error - Alto incorrecto, debe ser un numero entero mayor a 0 de 2 dígitos";
#define E_ANCHO_INC_TXT "Error - Ancho incorrecto, debe ser un numero entero mayor a 0 de 2 dígitos";

#endif
