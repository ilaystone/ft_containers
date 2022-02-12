#include "map.hpp"
#include <map>
#include <iostream>

int		main()
{
	ft::map<int, int>		first;

	first.insert(ft::make_pair(1, 10));
	first.insert(ft::make_pair(2, 20));
	std::cout << first[0] << std::endl;
	std::cout << first[1] << std::endl;
	return 0;
}