#ifndef __TEST3x3_H__
#define __TEST3x3_H__

#include <iostream>
#include <string>

class TestPaqInitPruebaBad
{
	private:
		bool _status;

	public:
		TestPaqInitPruebaBad() : _status( false ){ }

		bool status() { return _status; }

		void run( std::ostream& o );

		std::string name( ) { return "TestPaqInitPruebaBad"; }

		TestPaqInitPruebaBad* operator->(){ return this; }
};
#endif
