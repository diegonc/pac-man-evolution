#ifndef ESTADOAPLICACION_H_INCLUDED
#define ESTADOAPLICACION_H_INCLUDED

//tipo de dato de estado de aplicacion
class EstadoAplicacion
{
    public:
	bool Visible;											// Aplicacion Visible o Minimizada
	bool MouseFocus;										// Foco de Mouse
	bool KeyboardFocus;										// Foco de Teclado
};

#endif // ESTADOAPLICACION_H_INCLUDED
