#ifndef __TESTPSTART_H__
#define __TESTPSTART_H__

#include <iostream>
#include <string>

class TestPaqueteStart
{
	private:
		bool _status;

	public:
		TestPaqueteStart() : _status( false ){ }

		bool status() { return _status; }

		void run( std::ostream& o );

		std::string name( ) { return "TestPaqueteStart"; }

		TestPaqueteStart* operator->(){ return this; }
};

#endif
