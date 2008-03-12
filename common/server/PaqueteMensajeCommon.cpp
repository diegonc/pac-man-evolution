#include <server/PaqueteMensajeCommon.h>

namespace {
	const char ID = 6;
}

PaqueteMensajeCommon::PaqueteMensajeCommon(): Paquete(ID)
{

}
/*
std::string PaqueteMensajeCommon::get_mensaje()
{
    return Mensaje;
}

void PaqueteMensajeCommon::set_mensaje(std::string msg)
{
    Mensaje = msg;
}
*/
void PaqueteMensajeCommon::deserialize( InputBitStream& bs )
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

void PaqueteMensajeCommon::serialize( OutputBitStream& bs )
{
    Paquete::serialize( bs ); // Escribe version de protocolo e ID de paquete.

    int slen = Mensaje.length() + 1; // slen cuenta el '\0'
    if( slen > 70 ) slen = 70;
    int TamanioCotaSup= slen/10 + ( slen%10 != 0 ? 1 : 0 );
    bs.append( 3, TamanioCotaSup); // Escribe campo auxiliar.
    bs.skip();
    bs.append_string( Mensaje.c_str(), slen );
}

Operacion * PaqueteMensajeCommon::get_operacion(){
	return new OperacionNula();
}
