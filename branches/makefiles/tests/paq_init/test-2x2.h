#ifndef __TEST2x2_H__
#define __TEST2x2_H__

#include <iostream>
#include <string>

class TestPaqInitPruebaCircular
{
	private:
		bool _status;

	public:
		TestPaqInitPruebaCircular() : _status( false ){ }

		bool status() { return _status; }

		void run( std::ostream& o );

		std::string name( ) { return "TestPaqInitPruebaCircular"; }

		TestPaqInitPruebaCircular* operator->(){ return this; }
};
#endif
