//Header
#include "app_editor.h"

/* CLASE APP EDITOR: Esta clase representa a la aplicacion en si. Tiene
   una sola instancia y un punto de acceso global a ella. */

AppEditor* AppEditor::instancia = NULL; //Inicializo la instancia en null
		
/* Constructor Privado: */
AppEditor::AppEditor(int argc, char* argv[]){
	//Creo el modelo y la interfaz grafica
	this->modelo = Modelo::get_instance();
	this->gui = GUI::get_instance(argc, argv);
}

/* Destructor Privado: */
AppEditor::~AppEditor(){
	//Destruyo el modelo y la interfaz grafica
	GUI::destroy();
	Modelo::destroy();
}

/* Get Instance: */
AppEditor* AppEditor::get_instance(int argc, char* argv[]){
	//Si no existe la instancia creo una nueva y la seteo como instancia unica
	if (AppEditor::instancia == NULL)
		AppEditor::instancia = new AppEditor(argc, argv);
	return AppEditor::instancia;	//Devuelvo la instancia
}		

/* Ejecutar: */
void AppEditor::ejecutar(){
  //Hago arrancar la interfaz grafica
  gui->start();
  //Uno la interfaz grafica con el hilo principal, cuando termina
  gui->join();
}


/* Imprimir Error: */

void AppEditor::imprimir_error(char codigo, int nroNivel){
	//Obtengo la ventana principal del gui para poder mandar mensajes de dialogo
	VPrincipal* ventana = this->gui->get_ventana_principal();
	//Stream de entrada para cadenas, para realizar conversiones de int a string
	std::stringstream ss; 
	//Aux para tener el nro de nivel como string y poder imprimir
	string sNroNivel;
	ss << nroNivel << '\n';
	ss >> sNroNivel;
	
	string msg; //Msg a imprimir
	
	//Segun el codigo de error, imprimo el error correcto por pantalla.
	switch (codigo) {
		case E_NO_SALIDA_COD:{
			msg = E_NO_SALIDA_TXT 
			msg += sNroNivel;
			ventana->mostrar_msg(msg);
			break; }
		case E_NO_CASA_COD: {
			msg = E_NO_CASA_TXT;
			msg += sNroNivel;
			ventana->mostrar_msg(msg);
			break; }
		case E_NO_CONGR_COD: {
			msg = E_NO_CONGR_TXT;
			msg += sNroNivel;
			ventana->mostrar_msg(msg);
			break; }
		case E_GUARDAR_INC_COD: {
			msg = E_GUARDAR_INC_TXT;
			ventana->mostrar_msg(msg);
			break; }
		case E_CARGAR_INC_COD: {
			msg = E_CARGAR_INC_TXT;
			ventana->mostrar_msg(msg);
			break; }
		case E_MISMO_NOMBRE_COD: {
			msg = E_MISMO_NOMBRE_TXT;
			ventana->mostrar_msg(msg);
			break; }
		case E_ALTO_INC_COD: {
			msg = E_ALTO_INC_TXT;
			ventana->mostrar_msg(msg);
			break; }
		case E_ANCHO_INC_COD: {
			msg = E_ANCHO_INC_TXT;
			ventana->mostrar_msg(msg);
			break; }
	}		
}

/* Destroy: */
void AppEditor::destroy(){
	delete(instancia);
}
