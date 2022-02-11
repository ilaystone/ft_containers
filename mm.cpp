#include "avl_tree.hpp"
#include "pair.hpp"
#include <iostream>

int		main()
{
	ft::avl_tree<ft::pair<int, int>>	f;

	// f[1] = 1;
	// f[2] = 3;
	std::cout << f[1] << std::endl;
	return 0;
}