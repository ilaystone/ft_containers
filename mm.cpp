#include "map.hpp"
#include <map>
#include <iostream>

int		main()
{
	ft::map<int, int>		first;

	first.insert(ft::make_pair(0, 10));
	first.insert(ft::make_pair(1, 10));
	first.insert(ft::make_pair(2, 10));
	first.insert(ft::make_pair(3, 10));
	first.insert(ft::make_pair(4, 10));
	first.insert(ft::make_pair(5, 10));

	first.erase(first.begin(), ++(++(++first.begin())));

	for (ft::map<int, int>::iterator it = first.begin(); it != first.end(); it++)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
	return 0;
}