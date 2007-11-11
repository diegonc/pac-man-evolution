#ifndef __APP_H__
#define __APP_H__

/****************************************************************************
-	Esta clase es la que modela la aplicacion. 
-	Solo se permite una unica instancia. 
-	Implementada con smart_pointer como tecnica RAII
******************************************************************************/


#include "../common/smart_pointer.h"

class App{
	private:
		App();
		App(App& a);
	
		static S_ptr<App> instancia;
		
	public:
		~App();
	
		static S_ptr<App> get_instancia();
	
		int ejecutar();		
};



#endif /* __APP_H__ */
