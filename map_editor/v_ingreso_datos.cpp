//HEADER
#include "v_ingreso_datos.h"

/* CLASE VIngDatos: Clase que se encarga de controlar el ingreso de los datos para un nuevo nivel. */

/* Constructor: */

VIngDatos::VIngDatos(char* titulo, GtkWidget* window){
	this->dialogo = gtk_dialog_new_with_buttons  (titulo,
                                                  GTK_WINDOW(window),
                                                  GTK_DIALOG_MODAL,
                                                  GTK_STOCK_OK,
                                                  GTK_RESPONSE_ACCEPT,
                                                  GTK_STOCK_CANCEL,
                                                  GTK_RESPONSE_REJECT,
                                                  NULL);
	
	GtkWidget* label =  gtk_label_new ("Nombre del nuevo nivel:");
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      label);
	this->entrada_nombre = gtk_entry_new ();
	gtk_entry_set_max_length(GTK_ENTRY(this->entrada_nombre), 20);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      this->entrada_nombre);
	
   	label =  gtk_label_new ("Ancho: ");
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      label);
	this->entrada_ancho = gtk_entry_new ();
	gtk_entry_set_max_length(GTK_ENTRY(this->entrada_ancho), 2);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      this->entrada_ancho);
					  
	label =  gtk_label_new ("Alto: ");
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      label);
	this->entrada_alto = gtk_entry_new ();
	gtk_entry_set_max_length(GTK_ENTRY(this->entrada_alto), 2);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(this->dialogo)->vbox),
                      this->entrada_alto);
					  
	gtk_widget_show_all (this->dialogo);
	
	this->nombre = "";
	this->alto = 0;
	this->ancho = 0;
}

/* Destructor: */

VIngDatos::~VIngDatos(){

}

/* Ejecutar: */

bool VIngDatos::ejecutar(){
	bool error = false;
	//Corro la ventana de dialogo, y si la respuesta del usuario es aceptar...
	if (gtk_dialog_run (GTK_DIALOG (this->dialogo)) == GTK_RESPONSE_ACCEPT) {
		const gchar* dato = gtk_entry_get_text(GTK_ENTRY(this->entrada_nombre));
		this->nombre = dato;
		if (!(Modelo::get_instance()->get_mundo()->get_nivel_por_nombre(this->nombre)).es_nulo()){
			this->mostrar_msg("Ya existe un nivel con ese nombre");
			error = true;
		}
		if (!error) {
			dato = gtk_entry_get_text(GTK_ENTRY(this->entrada_alto));
			this->alto = atoi(dato);
			if (this->alto <= 0){
				this->mostrar_msg("El alto ingresado es incorrecto");
				error = true;
			}
			if (!error) {
				dato = gtk_entry_get_text(GTK_ENTRY(this->entrada_ancho));
				this->ancho = atoi(dato);
				if (this->ancho <= 0){
					this->mostrar_msg("El ancho ingresado es incorrecto");
					error = true;
				}
			}
		}
		gtk_widget_destroy(this->dialogo);
		return (!(error));
	} else {
		gtk_widget_destroy(this->dialogo);
		return false;
	}
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

/* Mostrar Msg: */

void VIngDatos::mostrar_msg(char* msg){
	//Creo un dialogo de error con el mensaje recibido por param
	GtkWidget* dialog = gtk_message_dialog_new (GTK_WINDOW(GUI::get_instance(0,0)->get_ventana_principal()->get_widget()),
						  GTK_DIALOG_DESTROY_WITH_PARENT,
						  GTK_MESSAGE_ERROR,
						  GTK_BUTTONS_CLOSE,
						  msg);
	//Corro el dialogo
	gtk_dialog_run (GTK_DIALOG (dialog));
	//Lo destruyo
	gtk_widget_destroy (dialog);
}
