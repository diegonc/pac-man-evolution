/*#include "App.h"

int main(int argc, char *argv[]){
	return (App::get_instancia(argc, argv))->ejecutar();
}
*/
#include "OutputBitStream.h"
#include <iostream>
#include <bitset>
#include <string>

int main(int argc, char *argv[]){
	OutputBitStream o;
	
	//o.append( 2, 0 ); // version
    //o.append( 3, 7 ); // tipo
    //o.append( 3, 2);  // aux
	//o.append(8,2,true);
	o.append( 3, 4 );
    //o.append( 4, 24 );
    //o.append( 1, 1 );
	o.skip();
	const unsigned char * data = o.get_data();
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
