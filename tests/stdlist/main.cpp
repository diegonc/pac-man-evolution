#include <list>
#include <iostream>

struct Data
{
	char c;
};

int main()
{
	std::list<Data> list;

	Data item = { 'c' };

	list.push_back( item );

	std::cout << (*(list.begin())).c << std::endl;

	(*(list.begin())).c = 'f';

	std::cout << (*(list.begin())).c << std::endl;

	return 0;
}
