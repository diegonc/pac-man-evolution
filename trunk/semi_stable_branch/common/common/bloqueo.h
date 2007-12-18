#ifndef CLASS_BLOQUEO
#define CLASS_BLOQUEO
/***************************************************************************
-	Esta clase permite proteger, mediante sus instancias, zonas criticas de
	codigo, medianete el bloqueo de la misma.
-	Esta diseñado, de manera que al llamarse al destructor se libera la
	traba, por lo que es util usarlo instanciandolo en forma estatica dentro 
	de scopes por ejemplo

***************************************************************************/
#include <common/mutex.h>

class Bloqueo{
	 
	private:
		Mutex * mutex;
	public: 
		Bloqueo(Mutex *m);
	
		~Bloqueo();
};

#endif
