#ifndef __TESTPMSG_H__
#define __TESTPMSG_H__

#include <iostream>
#include <string>

class TestPaqueteMensaje
{
	private:
		bool _status;

	public:
		TestPaqueteMensaje() : _status( false ){ }

		bool status() { return _status; }

		void run( std::ostream& o );

		std::string name( ) { return "TestPaqueteMensaje"; }

		TestPaqueteMensaje* operator->(){ return this; }
};

#endif
