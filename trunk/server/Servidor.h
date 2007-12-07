#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

#include "Cliente.h"
#include "ClientPool.h"
#include "../common/server_socket.h"
#include "../common/thread.h"
#include <map>
#include <string>

class Servidor : public Thread{
	typedef unsigned int Tipo_Id_Cliente;
	
	private:
		//clientes conectados
		ClientPool pool;
		/* se fue al pool.
		std::map<Tipo_Id_Cliente, Cliente>  clientes;
		//TODO forma de asignar los ids....por el momento, a manopla
		unsigned int ultimo_id;
		*/
		//socket que permite la conexion
		Socket_Server * socket;
	
	public:
		/** @brief Constructor de la clase.
		 *
		 *  @param direccion Direccion ip de la cual va a escuchar
		 *  @param puerto    Puerto del que va a escuchar
		 */
		Servidor(std::string &direccion, unsigned short int puerto);
		
		/** @brief Constructor de la clase. En este caso escucha todas
	     *         las ip
		 *
		 *  @param puerto Puerto a traves del cual se va a comunicar
		 */
		Servidor(unsigned short int puerto);
	
		/** @brief Destructor de la clase.
		 */
		~Servidor();	
	
		/** @brief Implementacion del run de thread
		 *
		 */
		void run();
};
#endif /*__SERVIDOR_H__*/
