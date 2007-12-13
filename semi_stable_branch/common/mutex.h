#ifndef CLASS_MUTEX
#define CLASS_MUTEX
/****************************************************************************
-	Esta clase enmascara los pthread_mutex

******************************************************************************/

#include <pthread.h>

class Mutex{
	
	private:
		 
		pthread_mutex_t llave;
		Mutex(Mutex &m);
		Mutex& operator=(Mutex& m);
	
	public:
		Mutex();			
		
		void lock();
		
		void unlock();
	
		pthread_mutex_t * get_mutex();
	
		~Mutex();
};	

#endif
