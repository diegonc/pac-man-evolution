#include "App.h"
#include <string>
#include <fstream>
#include "ModeloServidor.h"
#include "Servidor.h"

//para realizar las conversiones
#include "traductor.h"
//#include "../map_editor/mundo.h"


S_ptr<App> App::instancia;

App::App(int argc, char *argv[]){
	this->argc = argc;
	this->argv = argv;
}
App::App(App& a){}
	
App::~App(){}
	
S_ptr<App> App::get_instancia(int argc, char *argv[]){
	if( instancia.es_nulo())
		instancia = S_ptr<App>(new App(argc, argv));
	return instancia;
}

void App::validar_linea_comando()
{
	if( argc != 2 ) {
		throw std::runtime_error(
"Numero incorrecto de parametros.\n"
"Uso de la aplicacion:\n"
"\tpme-server archivo\n\n"
"\t\tarchivo\t\tRuta al archivo de configuracion.\n\n"
"Para conocer la sintaxis del archivo de configuracion vea la configuracion de "
"ejemplo en el archivo 'sample.conf'." );
	} else {
		std::ifstream ifs( argv[1] );

		if( ! ifs.is_open() ) {
			std::string s("Error abriendo archivo para lectura: ");
			s += argv[1];
			s += "\nVerifique la ruta y los permisos del archivo.";
			throw s;
		}
	}
}

void App::cargar_configuracion()
{
	// Inicializacion de valores por omision.
	conf.set_conf( "direccion", ConfValue( std::string("0.0.0.0") ) );
	conf.set_conf( "min-jugadores", ConfValue( 2U ) );
	conf.set_conf( "max-jugadores", ConfValue( 5U ) );
	conf.set_conf( "com-fantasmas", ConfValue( false ) );
	conf.set_conf( "vidas", ConfValue( 1U ) );
	// Se agregan las opciones del archivo de configuracion.
	conf.load_conf( argv[1] );
}

std::string App::get_mundo_xml()
{
	try {
		ConfValue cv = conf.get_conf( "mundo" );
		return cv.get_texto();
	}catch( ... ) { /* TODO: ajustar excepcion." */
		throw std::runtime_error( "Establezca la opcion 'mundo' con la ruta al archivo descriptor del mundo en el archivo de configuracion." );
	}
}

unsigned int App::get_cl_min()
{
	try {
		ConfValue cv = conf.get_conf( "min-jugadores" );
		return cv.get_numero();
	}catch( ... ) { /* TODO: ajustar excepcion." */
		/* Opcion con valor por omision faltante. */
		assert( "Configuracion opcional no encontrada" == 0 );
	}
}

unsigned int App::get_cl_max()
{
	try {
		ConfValue cv = conf.get_conf( "max-jugadores" );
		return cv.get_numero();
	}catch( ... ) { /* TODO: ajustar excepcion." */
		/* Opcion con valor por omision faltante. */
		assert( "Configuracion opcional no encontrada" == 0 );
	}
}

unsigned int App::get_puerto_servidor()
{
	try {
		ConfValue cv = conf.get_conf( "puerto" );
		return cv.get_numero();
	}catch( ... ) { /* TODO: ajustar excepcion." */
		throw std::runtime_error( "Establezca la opcion 'puerto' con el puerto en el que el servidor debe escuchar en el archivo de configuracion." );
	}
}

int App::ejecutar(){
	try{
		validar_linea_comando();
		cargar_configuracion();
		conf.dump( std::cout ); // TODO: quitar linea.
		//creo el mundo de alto nivel y lo cargo del xml
		Mundo mundo_alto_nivel;
		if( mundo_alto_nivel.fromXml( get_mundo_xml().c_str() ) ) {
			//lo traduzo a un mundo de bajo nivel y lo meto en un smart Pointer
			Traductor traductor;
			S_ptr<MundoBajoNivel> mundo_bajo_nivel(traductor.traducir(&mundo_alto_nivel));
			//crea el modelo	
			//S_ptr<ModeloServidor> modelo(new ModeloServidor());
			//lo meto en el modelo
			ModeloServidor::get_instancia()->set_mundo(mundo_bajo_nivel);
			//modelo->set_mundo(mundo_bajo_nivel);
			//crea el servidor


			int puerto = get_puerto_servidor();
			S_ptr<Servidor> servidor(new Servidor(puerto) );
			// Configura numero de clientes.
			servidor->set_cant_min_clientes( get_cl_min() );
			servidor->set_cant_max_clientes( get_cl_max() ); 

			//inicia el hilo del modelo
			//modelo->start();
			//inicia el hilo del servidor
			servidor->start();
			
			//se une a los hilos
			//modelo->join();
			servidor->join();
			
		}
		else
			//TODO PROVISORIO
			std::cerr << "Hubo un error con la carga del xml\n";
	}
	catch(std::runtime_error &e){
		std::cerr << e.what()<<"\n";	
	}
	return 0;
}
