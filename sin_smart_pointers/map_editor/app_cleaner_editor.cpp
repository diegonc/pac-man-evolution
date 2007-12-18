//Header
#include "app_cleaner_editor.h"

/* CLASE APP CLEANER EDITOR: Clase que se encarga de liberar los recursos de
   la aplicacion. */
   
//Destructor:

AppCleanerEditor::~AppCleanerEditor(){
	AppEditor::destroy();
}
