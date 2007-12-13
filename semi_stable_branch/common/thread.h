#ifndef CLASS_THREAD
#define CLASS_THREAD
/***************************************************************************
-	Esta clase envuelve a los pthreads.

***************************************************************************/
#include <pthread.h>
#include <signal.h>

class Thread{
	
	public:
			
		void start();
	
		/*void join(Thread *t);
	
		void join(pthread_t hilo);*/

      void join();
	
		int thread_kill(int signal);
	
		pthread_t& get_hilo();
	
		virtual ~Thread();
	
		Thread();	
	
	private:
		pthread_t hilo;
		
		Thread(Thread &t);
			
		Thread& operator=(Thread& t);		
			
		virtual void run()=0;
		
		static void * funcion_auxiliar_run(void * param);
		
};

#endif
