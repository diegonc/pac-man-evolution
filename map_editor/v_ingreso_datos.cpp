//HEADER
#include "v_ingreso_datos.h"

/* CLASE VIngDatos: Clase que se encarga de controlar el ingreso de los datos para un nuevo nivel. */

/* Constructor: */

VIngDatos::VIngDatos(char* titulo, GtkWidget* window){
	//Creo una nueva ventana de dialogo con los datos pasados por parametro
	this->dialogo = gtk_dialog_new_with_buttons  (titulo,
                                                  GTK_WINDOW(window),
                                                  GTK_DIALOG_MODAL,
                                                  GTK_STOCK_OK,
                                                  GTK_RESPONSE_ACCEPT,
                                                  GTK_STOCK_CANCEL,
                                                  GTK_RESPONSE_REJECT,
                                                  NULL);
	//Creo y agrego la entrada para el nombre
	GtkWidget* label =  gtk_label_new ("Nombre del nuevo nivel:");
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      label);
	this->entrada_nombre = gtk_entry_new ();
	gtk_entry_set_max_length(GTK_ENTRY(this->entrada_nombre), 20); //Max 20 caracteres
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      this->entrada_nombre);
	//Creo y agrego la entrada para el ancho del nivel
   	label =  gtk_label_new ("Ancho: ");
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      label);
	this->entrada_ancho = gtk_entry_new ();
	gtk_entry_set_max_length(GTK_ENTRY(this->entrada_ancho), 2); //Max 2 caracteres
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      this->entrada_ancho);
	//Creo y agrego la entrada para el alto del nivel	  
	label =  gtk_label_new ("Alto: ");
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      label);
	this->entrada_alto = gtk_entry_new ();
	gtk_entry_set_max_length(GTK_ENTRY(this->entrada_alto), 2); //Max 2 caracteres
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      this->entrada_alto);
	//Muestro la ventana de dialogo
	gtk_widget_show_all (this->dialogo);
}

/* Destructor: */

VIngDatos::~VIngDatos(){

}

/* Ejecutar: */

bool VIngDatos::ejecutar(){
	bool error = false; //Controla si hay o no errores
	//Referencia a la ventana principal del programa
	VPrincipal* vprincipal = GUI::get_instance(0,0)->get_ventana_principal();
	//Corro la ventana de dialogo, y si la respuesta del usuario es aceptar, intento agregar los datos del nivel
	if (gtk_dialog_run (GTK_DIALOG (this->dialogo)) == GTK_RESPONSE_ACCEPT) {
		//Obtengo el nombre
		const gchar* dato = gtk_entry_get_text(GTK_ENTRY(this->entrada_nombre));
		this->nombre = dato;
		//Si hay otro nivel con el mismo nombre mando un mensaje al usuario
		if (!(Modelo::get_instance()->get_mundo()->get_nivel_por_nombre(this->nombre)).es_nulo()){
			vprincipal->mostrar_msg("Ya existe un nivel con ese nombre");
			error = true;
		}
		if (!error) {
			//Obtengo la altura del nivel
			dato = gtk_entry_get_text(GTK_ENTRY(this->entrada_alto));
			this->alto = atoi(dato); //La convierto a int
			//Si no se puede convertir o vale 0 arrojo error por pantalla
			if (this->alto <= 0){
				vprincipal->mostrar_msg("El alto ingresado es incorrecto");
				error = true;
			}
			//Obtengo el ancho del nivel
			dato = gtk_entry_get_text(GTK_ENTRY(this->entrada_ancho));
			this->ancho = atoi(dato); //Lo convierto a int
			//Si no se puede convertir o vale 0 arrojo error por pantalla
			if (this->ancho <= 0){
				vprincipal->mostrar_msg("El ancho ingresado es incorrecto");
				error = true;
			}
		}
	} else
		error = true; //Si el usuario pulso cancelar o cerro la ventana marco como error
	gtk_widget_destroy(this->dialogo); //Destruyo la ventana de dialogo
	return (!error); //Devuelvo true si no hubo error, false en caso contrario
}

/* Get Nombre: */

string VIngDatos::get_nombre(){
	return this->nombre;
}

/* Get Alto: */

int VIngDatos::get_alto(){
	return this->alto;
}

/* Get Ancho: */

int VIngDatos::get_ancho(){
	return this->ancho;
}

/* Get Widget: */

GtkWidget* VIngDatos::get_widget(){
	return this->dialogo;
}
