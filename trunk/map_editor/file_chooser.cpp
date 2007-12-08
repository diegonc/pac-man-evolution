//HEADER
#include "file_chooser.h"

/* CLASE FILE CHOOSER: Permite guardar y cargar archivos. */
   
/* Constructor: */

FileChooser::FileChooser(char* titulo, GtkWidget* window, GtkFileChooserAction accion){
	const char* stock;
	this->accion = accion;
	//Segun la accion coloco un boton de guardar o abrir
	if (accion == GTK_FILE_CHOOSER_ACTION_SAVE)
		stock = GTK_STOCK_SAVE;
	else
		stock = GTK_STOCK_OPEN;
	//Creo el widget del file chooser para el manejo de archivos con los datos recibidos por parametro
	this->file_chooser = gtk_file_chooser_dialog_new (titulo, GTK_WINDOW(window), accion,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      stock, GTK_RESPONSE_ACCEPT,
				      NULL);
	//Pongo que me pida confirmacion para overwrite
	gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(file_chooser), true);
	//Creo el filtro para archivos con extension del mundo y le pongo el patron "*.ext_mundo"
	this->filtro_mundo = gtk_file_filter_new ();
	string pattern ("*");
	pattern += EXT_MUNDO;
	gtk_file_filter_add_pattern(filtro_mundo, pattern.c_str());
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), filtro_mundo);
}

/* Destructor: */

FileChooser::~FileChooser(){
	gtk_widget_destroy(this->file_chooser);
}

/* Ejecutar: */

void FileChooser::ejecutar(){
	Mundo* mundo = Modelo::get_instance()->get_mundo();
	//Corro el dialogo del file chooser, y si la respuesta del usuario es aceptar...
	if (gtk_dialog_run (GTK_DIALOG (this->file_chooser)) == GTK_RESPONSE_ACCEPT) {
		char* filename = this->get_filename();
		//Si la accion es guardar, guardo el mundo segun el filename
		if (this->accion == GTK_FILE_CHOOSER_ACTION_SAVE){
			if (!mundo->toXml(filename))
				//Si se produjo un error guardando el archivo notifico por pantalla
				this->mostrar_msg("Error guardando archivo.");
		} else {
			//Si la accion es abrir, creo un nuevo mundo y lo cargo desde el archivo con nombre filename
			Mundo* mundo_nuevo = new Mundo();
			if (mundo_nuevo->fromXml(filename)){
				//Si se pudo cargar, seteo el nuevo mundo al modelo
				Modelo::get_instance()->set_mundo(mundo_nuevo);
			} else {
				//Sino muestro error y borro el nuevo mundo
				this->mostrar_msg("Error abriendo archivo.");
				delete (mundo_nuevo);
			}
		}
		//Libero el filename
		g_free (filename);
	}
}

/* Get Widget: */

GtkWidget* FileChooser::get_widget(){
	return this->file_chooser;
}

/* Get FileName: */

char* FileChooser::get_filename(){
	return gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (this->file_chooser));
}

/* Mostrar Msg: */

void FileChooser::mostrar_msg(char* msg){
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
