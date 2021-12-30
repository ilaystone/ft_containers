#include "common_test_template.hpp"

int		main(void)
{
	std::cout << "\tVECTOR TEST" << std::endl;
	std::cout << "default constrctor" << std::endl;
	TEST_NAME::vector<TEST_TYPE>	vec_default;
	std::cout << "fill constructor" << std::endl;
	TEST_NAME::vector<TEST_TYPE>	vec_fill(4, 122);
	printSize(vec_fill);
}