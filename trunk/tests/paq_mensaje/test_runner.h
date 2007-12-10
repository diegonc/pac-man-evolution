#ifndef __TESTRUNNER_H__
#define __TESTRUNNER_H__

#include <sstream>
#include <iostream>

class TestRunnerBase
{
	public:
		virtual ~TestRunnerBase(){}

		virtual bool run() = 0;
};

template<class Test>
class TestRunner : public TestRunnerBase
{
	private:
		Test t;

	public:
		TestRunner( Test& t ) : t( t ) { }

		bool run();
};

template<class Test>
bool TestRunner<Test>::run()
{
	std::ostringstream o;
	std::cout << "Corriendo: " << t->name() << "...";
	t->run( o );
	bool result = t->status();
	std::cout << ( result ? "BIEN" : "FALLO" );
	std::cout << "\n" << o.str() << "\n";
	return result;
}
#endif
