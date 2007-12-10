#include "test_runner.h"
#include "common/smart_pointer.h"
#include <list>

#include "test-2x2.h"
#include "test-3x3.h"

typedef std::list<S_ptr<TestRunnerBase> > TestRunnerList;

TestRunnerList inicializar_pruebas()
{
	TestRunnerList list;
	#define ADD_TEST(X)	list.push_back( S_ptr<TestRunnerBase>( new TestRunner<X>(X()) ))

	/* Agregue aqui sus pruebas. =P */
	ADD_TEST(TestPaqInitPruebaCircular);
	ADD_TEST(TestPaqInitPruebaBad);
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
