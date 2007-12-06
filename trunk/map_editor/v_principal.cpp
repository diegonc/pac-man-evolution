//HEADER

#include "v_principal.h"

/* CLASE VPRINCIPAL: Representa la ventana principal del editor de mapas. */

//Constructor:

VPrincipal::VPrincipal(){
	
	//Creo la ventana principal y la configuro
	this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_border_width (GTK_CONTAINER (this->window), BORDE);
	gtk_window_maximize(GTK_WINDOW(this->window)); //La ventana arranca maximizada
	gtk_window_set_title (GTK_WINDOW(this->window), TITULO);
	
	//Conecto la señal delete event con el handler para la ventana
	g_signal_connect(G_OBJECT(this->window), "delete_event", G_CALLBACK(delete_event_handler), NULL);
	g_signal_connect(G_OBJECT(this->window), "destroy", G_CALLBACK(destroy_handler), this);
	
	ControlSeleccion::get_instance();
	this->panel_mundo = new PanelMundo();
	this->panel_estruc = new PanelElems("ESTRUCTURALES");
	this->panel_modif = new PanelElems("MODIFICADORES");
	
	this->construir();

}

//Destructor:

VPrincipal::~VPrincipal(){
	delete(this->panel_mundo);
	delete(this->panel_estruc);
	delete(this->panel_modif);
	delete(this->vista_mapa);
	ControlSeleccion::destroy();
}

//Get Widget:

GtkWidget* VPrincipal::get_widget() const {
	return this->window;
}

//Mostrar:
	
void VPrincipal::mostrar(){
	//Muestro la ventana y todos sus widgets
	gtk_widget_show_all (this->window);
}

//Construir:

void VPrincipal::construir(){
	this->vbox_princ = gtk_vbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->vbox_princ), 1);
	gtk_container_add (GTK_CONTAINER (window), this->vbox_princ);

	//Creo una barra de menus y la agrego a la ventana principal
	S_ptr<MenuBarFactory> fab (new MenuBarFactory());
	this->menubar = fab->construir();
	gtk_box_pack_start (GTK_BOX (this->vbox_princ), menubar->get_widget(), FALSE, TRUE, 0);

	this->hbox_princ = gtk_hbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->hbox_princ), 1);
	gtk_container_add (GTK_CONTAINER (this->vbox_princ), this->hbox_princ);
	
	this->vbox_tools = gtk_vbox_new(TRUE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (this->vbox_tools), 1);
	gtk_box_pack_start (GTK_BOX (this->hbox_princ), this->vbox_tools, FALSE, TRUE, 0);
	
	GtkWidget* p_mundo = this->panel_mundo->get_widget();
	gtk_box_pack_start (GTK_BOX (this->vbox_tools), p_mundo, FALSE, TRUE, 0);
	
	GtkWidget* p_estruc = this->panel_estruc->get_widget();
	gtk_box_pack_start (GTK_BOX (this->vbox_tools), p_estruc, FALSE, TRUE, 0);
	
	this->panel_estruc->agregar_elemento(PASILLO, ESTE, RUTA_PAS_HORIZ);
	this->panel_estruc->agregar_elemento(PASILLO, NORTE, RUTA_PAS_VERT);
	this->panel_estruc->agregar_elemento(ESQ, ESTE, RUTA_ESQ_ESTE);
	this->panel_estruc->agregar_elemento(ESQ, SUR, RUTA_ESQ_SUR);
	this->panel_estruc->agregar_elemento(ESQ, OESTE, RUTA_ESQ_OESTE);
	this->panel_estruc->agregar_elemento(ESQ, NORTE, RUTA_ESQ_NORTE);
	this->panel_modif->agregar_elemento(PWUP, NULA, RUTA_POWER_UP);
	this->panel_modif->agregar_elemento(BONUS, NULA, RUTA_BONUS);
	this->panel_modif->agregar_elemento(SALIDA, NULA, RUTA_SALIDA);
	
	this->panel_estruc->agregar_observador(ControlSeleccion::get_instance());
	this->panel_modif->agregar_observador(ControlSeleccion::get_instance());
	
	GtkWidget* p_modif = this->panel_modif->get_widget();
	gtk_box_pack_start (GTK_BOX (this->vbox_tools), p_modif, FALSE, TRUE, 0);
	
	//Creo un modelo
 	modeloTemporal = new Modelo();
  	//Obtengo su mundo
    Mundo* mundo = modeloTemporal->get_mundo();
    //Agrego un nivel de 50 x 50
    mundo->agregar_nivel(50, 50);
	//Agrego uno de 10 x 10
	mundo->agregar_nivel(10,10);
	
	this->panel_mundo->agregar_nivel(mundo->get_nivel(1), "nivel 50 x 50");
	this->panel_mundo->agregar_nivel(mundo->get_nivel(2), "nivel 10 x 10");
	
  	this->vista_mapa = new VistaMapa(mundo->get_nivel(1));
	
	this->panel_mundo->agregar_observador(this->vista_mapa);
	
	gtk_container_add (GTK_CONTAINER (this->hbox_princ), this->vista_mapa->get_widget());
	
}

// Delete Event Handler:

gboolean VPrincipal::delete_event_handler(GtkWidget* widget, GdkEvent* event, gpointer data) {
	
	/* finaliza el loop de gtk_main() y libera memoria */
	gtk_main_quit();
	
	/* Devuelve FALSE, asi que la ventana se destruye */
	return FALSE;
}

/* Destroy Handler: */

gboolean VPrincipal::destroy_handler(GtkWidget* widget, gpointer data){
	
	/**************************************************/
	
	VPrincipal* v_princ = (VPrincipal*) data;
	Mundo* mundo_alto_nivel = v_princ->modeloTemporal->get_mundo();
	Traductor traductor;
	MundoBajoNivel* mundo_bajo_nivel = traductor.traducir(mundo_alto_nivel);
	S_ptr<MundoBajoNivel> mundo_ptr(mundo_bajo_nivel);
	AplicacionGrafica::modelo.set_mundo(mundo_ptr);
	delete(v_princ->modeloTemporal);
	
	/**************************************************/
	
	return TRUE;
}
