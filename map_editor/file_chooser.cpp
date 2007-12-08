//HEADER
#include "file_chooser.h"

/* CLASE FILE CHOOSER: Permite guardar y cargar archivos. */
   
/* Constructor: */

FileChooser::FileChooser(char* titulo, GtkWidget* window, GtkFileChooserAction accion){
	const char* stock;
	this->accion = accion;
	if (accion == GTK_FILE_CHOOSER_ACTION_SAVE)
		stock = GTK_STOCK_SAVE;
	else
		stock = GTK_STOCK_OPEN;
	this->file_chooser = gtk_file_chooser_dialog_new (titulo, GTK_WINDOW(window), accion,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      stock, GTK_RESPONSE_ACCEPT,
				      NULL);
	gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(file_chooser), true);
	this->filtro_xml = gtk_file_filter_new ();
	string pattern ("*");
	pattern += EXT_MUNDO;
	gtk_file_filter_add_pattern(filtro_xml, pattern.c_str());
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), filtro_xml);
}

/* Destructor: */

FileChooser::~FileChooser(){
	gtk_widget_destroy(this->file_chooser);
}

/* Ejecutar: */

void FileChooser::ejecutar(){
	Mundo* mundo = Modelo::get_instance()->get_mundo();
	if (gtk_dialog_run (GTK_DIALOG (this->file_chooser)) == GTK_RESPONSE_ACCEPT) {
		char* filename = this->get_filename();
		if (this->accion == GTK_FILE_CHOOSER_ACTION_SAVE){
			if (!mundo->toXml(filename))
				this->mostrar_msg("Error guardando archivo.");
		} else {
			Mundo* mundo_nuevo = new Mundo();
			if (mundo_nuevo->fromXml(filename)){
				Modelo::get_instance()->set_mundo(mundo_nuevo);
			} else {
				this->mostrar_msg("Error abriendo archivo.");
				delete (mundo_nuevo);
			}
		}
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

/* Cumple Filtro: */

bool FileChooser::cumple_filtro(){
	char* filename = this->get_filename();
	GtkFileFilterInfo filter_info;
	filter_info.filename = filename;
	filter_info.uri = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (this->file_chooser));
	filter_info.display_name = filename;
	bool result = gtk_file_filter_filter (this->filtro_xml, &filter_info);
	g_free(filename);
	return result;
}

/* Mostrar Msg: */

void FileChooser::mostrar_msg(char* msg){
	GtkWidget* dialog = gtk_message_dialog_new (GTK_WINDOW(GUI::get_instance(0,0)->get_ventana_principal()->get_widget()),
						  GTK_DIALOG_DESTROY_WITH_PARENT,
						  GTK_MESSAGE_ERROR,
						  GTK_BUTTONS_CLOSE,
						  msg);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}
