#include "common_test_template.hpp"

int		main(void)
{
	std::cout << "\tVECTOR TEST" << std::endl;
	std::cout << "default constrctor: \n" << std::endl;
	TEST_NAME::vector<TEST_TYPE>	vec_default;
	std::cout << "fill constructor: \n" << std::endl;
	TEST_NAME::vector<TEST_TYPE>	vec_fill(4, 122);
	printSize(vec_fill);
	std::cout << "range constructor: \n" << std::endl;
	TEST_NAME::vector<TEST_TYPE>	vec_range(vec_fill.begin(), vec_fill.end());
	printSize(vec_range);
	std::cout << "iterator constructor: \n" << std::endl;
	int		my_ints[] = { 16, 2, 77, 29 };
	TEST_NAME::vector<TEST_TYPE>	vec_iter(my_ints, my_ints + sizeof(my_ints) / sizeof(int));
	printSize(vec_iter);
	std::cout << "assignment operator: \n" << std::endl;
	vec_default = vec_iter;
	printSize(vec_default);
	TEST_NAME::vector<TEST_TYPE>	foo(3, 0);
	TEST_NAME::vector<TEST_TYPE>	bar(5, 0);
	bar = foo;
	foo = TEST_NAME::vector<TEST_TYPE>();
	printSize(foo);
	printSize(bar);
}