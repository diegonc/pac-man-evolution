#include "test_runner.h"
#include "common/smart_pointer.h"
#include <list>

typedef std::list<S_ptr<TestRunnerBase> > TestRunnerList;

TestRunnerList inicializar_pruebas()
{
	TestRunnerList list;
	#define ADD_TEST(X)	list.push_back( S_ptr<TestRunnerBase>( new TestRunner<X>() );

	/* Agregue aqui sus pruebas. =P */

	/********************************/
	#undef ADD_TEST
	return list;
}

int main()
{
	TestRunnerList trl = inicializar_pruebas();
	TestRunnerList::iterator it = trl.begin();

	while( it != trl.end() )
		(*it++)->run();
	
	return 0;
}
