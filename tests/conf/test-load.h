#ifndef __TESTLOAD_H__
#define __TESTLOAD_H__

#include <iostream>
#include <string>

class TestConfLoad
{
	private:
		bool _status;

	public:
		TestConfLoad() : _status( false ){ }

		bool status() { return _status; }

		void run( std::ostream& o );

		std::string name( ) { return "TestConfLoad"; }

		TestConfLoad* operator->(){ return this; }
};
#endif
