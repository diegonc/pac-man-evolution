//HEADER

#include "m_bar_factory.h"

/* CLASE MENU BAR FACTORY: Clase que se ocupa de encapsular la creación de la barra de menus. */

//Construir:

S_ptr<Menu> MenuBarFactory::construir(){

  //Creo una barra de menus
  S_ptr<Menu> menubar (new MenuBar());
  //Creo la fabrica del menu archivo
  S_ptr<MenuArchFactory> fab (new MenuArchFactory());
  //Creo el menu archivo
  S_ptr<Menu> menuArch = fab->construir();
  //Creo un item "archivo" con el menu archivo como submenu
  S_ptr<Item> archivo (new ItemArchivo());
  archivo->set_sub_menu(menuArch);
  //Agrego el item a la barra de menus
  menubar->agregar_item(archivo);

  //Lo devuelvo
  return menubar;

}
