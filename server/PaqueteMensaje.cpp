#include "PaqueteMensaje.h"

namespace {
	const char ID = 6;
}

PaqueteMensaje::PaqueteMensaje(): Paquete(ID)
{

}

std::string PaqueteMensaje::get_mensaje()
{
    return Mensaje;
}

void PaqueteMensaje::set_mensaje(std::string msg)
{
    Mensaje = msg;
}

void PaqueteMensaje::deserialize( InputBitStream& bs )
{
    int TamanioCotaSup= bs.read( 3 )*10;
    bs.skip();

    char* buffer;
    if( TamanioCotaSup == 70 ) {
	    // En este caso el caracter nulo puede no venir en el stream.
	    buffer = new char[TamanioCotaSup+1];
	    buffer[TamanioCotaSup] = 0;
    }else buffer = new char[TamanioCotaSup];
    bs.read_string( buffer, TamanioCotaSup );
    bs.skip();
    std::string variableTemp(buffer);
    Mensaje=variableTemp; //como el igual esta sobrecargado se copia todo el string;
    delete[] buffer;
}

void PaqueteMensaje::serialize( OutputBitStream& bs )
{
    Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.

    int TamanioCotaSup=Mensaje.length()/10;
    ++TamanioCotaSup;
    bs.append( 3, TamanioCotaSup); // Escribe campo auxiliar.
    bs.skip();
    
    //bs.append_string( Mensaje.c_str(), TamanioCotaSup*10 );

}
Operacion * PaqueteMensaje::get_operacion(){
	//TODO
}
