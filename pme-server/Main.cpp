#include "App.h"

int main(int argc, char *argv[]){
	return (App::get_instancia(argc, argv))->ejecutar();
}
/*
#include <server/OutputBitStream.h>
#include <iostream>
#include <bitset>
#include <string>

int main(int argc, char *argv[]){
	OutputBitStream obs;
	OutputBitStream obs2;
	obs.append( 2, 0 ); // version
    obs.append( 3, 7 ); // tipo
    obs.append( 3, 2);  // aux
	//o.append(8,2,true);
	obs2.append( 16, 0 );
	//obs.append( 3, 0 );
	//obs.append( 3, 1 );
	//obs2.append( 3, 3 );
	
	//obs.append( 4, 12 );
	////obs.append( 1, 1 );
	//obs.skip();
	obs.append(obs2);
	//obs.append( 3, 2 );
	
	//obs2.append( 8, 2 );
	//obs2.append( 8, 2 );
	//obs2.append( 1, 0 );
	//obs2.append( 7, 0 );
	//obs2.append( 1, 1 );
	const unsigned char * data = obs.get_data();
	{
	std::bitset<8> bits(data[0]);
	std::cout << bits << " ";
	//std::cout << data[0];
	}	
	{
	std::bitset<8> bits(data[1]);
	std::cout << bits << " ";
	//std::cout << data[0];
	}
	{
	std::bitset<8> bits(data[2]);
	std::cout << bits << "\n";
	}
	
		
}

*/
