#include "ModeladorObjetos.h"


ModeladorObjetos::ModeladorObjetos(){

}

void ModeladorObjetos::hidratar(){
    ColeccionOBJ.hidratar();
}

//metodo q dibuja el objeto q se le pasa por referencia
//en el la posicion actual de la pantalla
void ModeladorObjetos::DibujarObjeto(ObjTextura* objTex){

    //textura del objeto
    GLuint* texture=&objTex->textura;
    //proporcion de escalado
    float const proporcion=0.04;
    //referencia a figura
    obj_type* object;
    //seteo el uso de la textura
    glBindTexture( GL_TEXTURE_2D, *texture );
/////////////opacidad
//glColor4f( 1, 1, 1, 1.0f ); // aca le decimos que module la textura con negro, por lo tanto donde dibuje tan solo oscurecera, y que al alpha lo divida por la mitad.
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//glEnable(GL_BLEND);
//glDisable(GL_DEPTH_TEST);
/////////////ENDDDDDDDDopacidad
    //escalo para q quede en un tamanio razonable
    glScalef( proporcion, proporcion, proporcion);

    //para cada figura del objeto
    for (std::list<obj_type_ptr>::iterator it=objTex->Objeto3d.Figuras.begin();it!=objTex->Objeto3d.Figuras.end();++it){
        object=*it;
        //estan formadas por triangulos
        //comienzo el modelado
        glBegin(GL_TRIANGLES);
        //itero sobre los poligonos(triangulos) q forman la imagen
        for (int l_index=0;l_index<object->polygons_qty;l_index++)
        {
            //PrimerVertice
            //Seteo las cordenadas de textura
            glTexCoord2f( object->mapcoord[ object->polygon[l_index].a ].u,
                          object->mapcoord[ object->polygon[l_index].a ].v);

            //agrego el vertice
            glVertex3f( object->vertex[ object->polygon[l_index].a ].x,
                        object->vertex[ object->polygon[l_index].a ].y,
                        object->vertex[ object->polygon[l_index].a ].z);


            //SegundoVertice
            //Seteo las cordenadas de textura
            glTexCoord2f( object->mapcoord[ object->polygon[l_index].b ].u,
                          object->mapcoord[ object->polygon[l_index].b ].v);
            //agrego el vertice
            glVertex3f( object->vertex[ object->polygon[l_index].b ].x,
                        object->vertex[ object->polygon[l_index].b ].y,
                        object->vertex[ object->polygon[l_index].b ].z);

            //SegundoVertice
            //Seteo las cordenadas de textura
            glTexCoord2f( object->mapcoord[ object->polygon[l_index].c ].u,
                          object->mapcoord[ object->polygon[l_index].c ].v);
            //agrego el vertice
            glVertex3f( object->vertex[ object->polygon[l_index].c ].x,
                        object->vertex[ object->polygon[l_index].c ].y,
                        object->vertex[ object->polygon[l_index].c ].z);
        }
        //fin de figura
        glEnd();
    }
    //fin objeto(conjunto de figuras)

    //reseteo el escalado
    glScalef( 1/proporcion, 1/proporcion, 1/proporcion);

    //quito la textura del objeto
    glBindTexture( GL_TEXTURE_2D, 0 );
}


//dibujar objeto em lugar determinado para la vista del observador
void ModeladorObjetos::DibujarObjetoObservadorPosicion(Posicion_Graf* P,char Nombre){
    //efecto caminar
    float static j=0;
    j+=0.02;

    //angulo
    float Angulo=sin(j)*4;

    //roto a angulo
    glRotatef(Angulo,0,1,0);
    //dibujo
    DibujarObjeto(ColeccionOBJ[Nombre]);
    //restauro el angulo de la vista
    glRotatef(-Angulo,0,1,0);
    //roto la camara segun el angulo del jugador
    glRotatef(P->getAnguloActual(), 0, 0.0, 1.0);

    //me traslado a la posicion del mismo
    glTranslatef(P->x,P->y, 0.0);
}

//dibujar objeto en posicion determinado
void ModeladorObjetos::DibujarObjetoPosicion(Posicion_Graf* P,char Nombre){
    // lo llevo al origen
    glTranslatef(-P->x,-P->y, 0.0);
    //lo roto segun su posicion
    glRotatef(P->getAnguloActual(), 0, 0, 1.0);
    //lo dibujo
    DibujarObjeto(ColeccionOBJ[Nombre]);
    //restauro la camara
    glRotatef(-P->getAnguloActual(), 0, 0, 1.0);
    //lo llevo a su posicion
    glTranslatef(P->x,P->y, 0.0);
}
