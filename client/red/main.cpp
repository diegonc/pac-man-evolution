#include "Cliente.h"

int main()
{
	Cliente c( "127.0.0.1", 6000 );

	c.start();
	c.join();
}
