#ifndef __COMMON_TEMPLATE_HPP
#define __COMMON_TEMPLATE_HPP

#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include "vector.hpp"

#ifndef TEST_NAME
# define TEST_NAME std
#endif

# ifndef TEST_TYPE
# define TEST_TYPE int
#endif

#define T_SIZE_TYPE typename TEST_NAME::vector<T>::size_type

template <typename T>
void	printSize(TEST_NAME::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity:" << capacity << std::endl;
	std::cout << "is capacity ok: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TEST_NAME::vector<T>::const_iterator it = vct.begin();
		typename TEST_NAME::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

#endif