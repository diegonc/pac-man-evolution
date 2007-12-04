#include "ColeccionObjetos.h"

ColeccionObjetos::ColeccionObjetos(){

}

void ColeccionObjetos::hidratar(){
    CargarObjetos();
}

//carga los objetos q van a ser usados
void ColeccionObjetos::CargarObjetos(){
    ObjTextura* objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),"banana.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),"banana.bmp");
        Objetos['b'] = objtext;

    objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),"pacman.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),"pacman.bmp");
        Objetos[Personaje::pacman]=objtext;

    objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),"pastilla.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),"pastilla.bmp");
        Objetos[Comestible::quesito]=objtext;

    objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),"cerecita.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),"cerecita.bmp");

    objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),"fantasma.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),"fantasma.bmp");
        Objetos[Personaje::fantasma]=objtext;

    objtext=new ObjTextura;
        CargadorDe3DS::Cargar3DS(&(objtext->Objeto3d),"powerup.3DS");
        CargadorDeTexturas::CargarTextura(&(objtext->textura),"powerup.bmp");
        Objetos[Comestible::power_up]=objtext;
}
