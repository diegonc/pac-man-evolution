#include "app_editor.h"
#include "app_cleaner_editor.h"
#include <iostream>

using namespace std;

//Funcion principal

int main(int argc, char *argv[])
{
  //Creo un App Cleaner Editor para borrar a la aplicacion automaticamente
  AppCleanerEditor app_cleaner;
  //Creo la App del Editor y la ejecuto
  AppEditor::get_instance(argc, argv)->ejecutar();

  return 0;

}
