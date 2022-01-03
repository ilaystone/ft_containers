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
	std::cout << "Iterators: \n" << std::endl;
	TEST_NAME::vector<TEST_TYPE>		myvec(4, 100);
	TEST_TYPE		i = TEST_TYPE();
	for (TEST_NAME::vector<TEST_TYPE>::iterator it = myvec.begin(); it < myvec.end(); it++)
	{
		std::cout << ' ' << *it;
		*it = i;
		i++;
	}
	std::cout << std::endl;
	for (TEST_NAME::vector<TEST_TYPE>::iterator it = myvec.begin(); it < myvec.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	myvec = TEST_NAME::vector<TEST_TYPE>();
	for (int c = 0; c < 50; c++)
		myvec.push_back(c);
	for (TEST_NAME::vector<TEST_TYPE>::iterator it = myvec.begin(); it < myvec.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	std::cout << *myvec.begin() << ' ' << *myvec.end() << std::endl;
	for (TEST_NAME::vector<TEST_TYPE>::reverse_iterator it = myvec.rbegin(); it != myvec.rend(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	std::cout << "Capacity: \n" << std::endl;
	std::cout << myvec.size() << ' ' << myvec.capacity() << ' ' << myvec.max_size() << std::endl;
	myvec.resize(40);
	printSize(myvec);
	myvec.resize(64);
	printSize(myvec);
	myvec.resize(65);
	printSize(myvec);
}