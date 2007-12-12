#ifndef __TESTEQUAL_H__
#define __TESTEQUAL_H__

#include <iostream>
#include <string>

class TestConfEqual
{
	private:
		bool _status;

	public:
		TestConfEqual() : _status( false ){ }

		bool status() { return _status; }

		void run( std::ostream& o );

		std::string name( ) { return "TestConfEqual"; }

		TestConfEqual* operator->(){ return this; }
};
#endif
