//HEADER

#include "m_arch_factory.h"

/* CLASE MENU ARCH FACTORY: Clase que se ocupa de encapsular la creación del menu archivo para el editor de mapas. */

//Construir:

S_ptr<Menu> MenuArchFactory::construir(){

  //Creo un menu
  S_ptr<Menu> menu (new SubMenu());
  //Creo los items "nuevo", "abrir", "guardar" y "salir"
  S_ptr<Item> nuevo (new ItemNuevo());
  S_ptr<Item> abrir (new ItemAbrir());
  S_ptr<Item> guardar (new ItemGuardar());
  S_ptr<Item> salir (new ItemSalir());
  //Creo una separacion para colocar entre salir y el item anterior
  GtkWidget* separador = gtk_separator_menu_item_new();

  //Agrego los items al menu
  menu->agregar_item(nuevo);
  menu->agregar_item(abrir);
  menu->agregar_item(guardar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu->get_widget()), separador);
  menu->agregar_item(salir);

  //Lo devuelvo
  return menu;

}
