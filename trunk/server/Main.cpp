/*#include "App.h"

int main(int argc, char *argv[]){
	return (App::get_instancia(argc, argv))->ejecutar();
}*//*
#include "OutputBitStream.h"
#include <iostream>
#include <bitset>
#include <string>

int main(int argc, char *argv[]){
	OutputBitStream o;
	
	o.append(8,'A',true);
	//o.append(2,2,true);
	
	const unsigned char * data = o.get_data();
	std::bitset<8> bits(data[0]);
	std::cout << bits << "\n";
	std::cout << data[0];
		
	
	
		
}*/
