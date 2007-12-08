#include "PaqueteMensaje.h"

namespace {
	const char ID = 6;
}

PaqueteMensaje::PaqueteMensaje(): Paquete(ID)
{

}

string PaqueteMensaje::get_mensaje()
{
    return Mensaje;
}

void PaqueteMensaje::set_mensaje(string msg)
{
    Mensaje=msg;
}

void PaqueteMensaje::deserialize( InputBitStream& bs )
{
    int TamanioCotaSup= bs.read( 3 )*10;
	bs.skip();

    char* buffer=new char[TamanioCotaSup];

    buffer = bs.read_block( TamanioCotaSup);
    bs.skip();
    string variableTemp(buffer);
    Mensaje=variableTemp; //como el igual esta sobrecargado se copia todo el string;
    delete buffer;
}

void PaqueteMensaje::serialize( OutputBitStream& bs )
{
    Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.

    int TamanioCotaSup=Mensaje.lenght()/10;
    ++TamanioCotaSup;
    bs.append( 3, TamanioCotaSup); // Escribe campo auxiliar.
	bs.skip();

    bs.grow(Mensaje.lenght());
	bs.append( Mensaje.lenght(), Mensaje);

}
