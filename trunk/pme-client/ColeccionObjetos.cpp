#include "ColeccionObjetos.h"

ColeccionObjetos::ColeccionObjetos(){

}

void ColeccionObjetos::hidratar(){
    CargarObjetos();
}

//carga los objetos q van a ser usados
void ColeccionObjetos::CargarObjetos(){
    ObjTextura* objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),APP_DATA_DIR_S "banana.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),APP_DATA_DIR_S "banana.bmp");
        Objetos['b'] = objtext;

    objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),APP_DATA_DIR_S "pacman.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),APP_DATA_DIR_S "pacman.bmp");
        Objetos[Personaje::pacman]=objtext;

    objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),APP_DATA_DIR_S "pastilla.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),APP_DATA_DIR_S "pastilla.bmp");
        Objetos[Comestible::quesito]=objtext;

    objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),APP_DATA_DIR_S "cerecita.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),APP_DATA_DIR_S "cerecita.bmp");
		Objetos[Comestible::frutita]=objtext;

    objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),APP_DATA_DIR_S "fantasma.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),APP_DATA_DIR_S "fantasma.bmp");
        Objetos[Personaje::fantasma]=objtext;

    objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),APP_DATA_DIR_S "powerup.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),APP_DATA_DIR_S "powerup.bmp");
        Objetos[Comestible::power_up]=objtext;
}
