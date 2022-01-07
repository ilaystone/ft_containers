#include "common_test_template.hpp"

int		main(void)
{
	std::cout << "\tVECTOR TEST" << std::endl;
	std::cout << "default constrctor: \n" << std::endl;
	TEST_NAME::vector<TEST_TYPE>	vec_default;
	std::cout << "fill constructor: \n" << std::endl;
	TEST_NAME::vector<TEST_TYPE>	vec_fill(4, 122);
	printSize(vec_fill);
	std::cout << "copy constructor: \n" << std::endl;
	TEST_NAME::vector<TEST_TYPE>	vec_copy(vec_fill);
	printSize(vec_copy);
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
	std::cout << std::boolalpha << myvec.empty() << std::endl;
	myvec.clear();
	std::cout << std::boolalpha << myvec.empty() << std::endl;
	printSize(myvec);
	myvec.reserve(100);
	printSize(myvec);
	myvec.reserve(150);
	printSize(myvec);
	try
	{
		myvec.reserve(myvec.max_size() + 1);
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	myvec.clear();
	for (int c = 0; c < 50; c++)
		myvec.push_back(c + 1);
	std::cout << "Element Access: \n" << std::endl;
	std ::cout << myvec[17] << std::endl;
	std::cout << myvec.at(17) << std::endl;
	try
	{
		myvec.at(88);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << myvec.front() << std::endl;
	std::cout << myvec.back() << std::endl;
	myvec.front() = 115;
	std::cout << myvec.front() << std::endl;
	std::cout << "modifiers: \n" << std::endl;
	TEST_NAME::vector<TEST_TYPE> first;
	TEST_NAME::vector<TEST_TYPE> second;
	TEST_NAME::vector<TEST_TYPE> third;

	first.assign (7,100);             // 7 ints with a value of 100

	TEST_NAME::vector<TEST_TYPE>::iterator it = first.begin() + 1;

	second.assign(it,first.end() - 1); // the 5 central values of first

	int myints[] = {1776, 7, 4};
	third.assign (myints, myints + 3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	std::cout << "Size of third: " << int (third.size()) << '\n';
	first.clear();
	for (int i = 0; i < 50; i++)
		first.push_back(i * 10 + 5);
	printSize(first);
	for (int i = 0; i < 50; i++)
		first.pop_back();
	printSize(first);
	int		sum(0);
	first.push_back(100);
	first.push_back(200);
	first.push_back(300);
	while (!first.empty())
	{
		sum += first.back();
		first.pop_back();
	}
	std::cout << "The elements of myvector add up to " << sum << '\n';
	first.clear();
	second.clear();
	first = TEST_NAME::vector<TEST_TYPE>(3, 100);
	it = first.begin();
	it = first.insert(it, 200);
	first.insert(it + 2, 300);
	it = first.begin();
	second = TEST_NAME::vector<TEST_TYPE>(2, 400);
	first.insert(it + 2, second.begin(), second.end());

	int		arr[] = { 501, 502, 503 };
	first.insert(first.begin(), arr, arr + 3);
	printSize(first);
	first = TEST_NAME::vector<TEST_TYPE>();
	for (int i = 1; i <= 10; i++)	first.push_back(i);
	first.erase(first.begin() + 5);
	first.erase(first.begin(), first.begin() + 3);
	printSize(first);
	foo = TEST_NAME::vector<TEST_TYPE>(3, 100);
	bar = TEST_NAME::vector<TEST_TYPE>(5, 200);
	printSize(foo);
	foo.swap(bar);
	printSize(foo);
	printSize(bar);
	foo.clear();
	printSize(foo);
	foo = TEST_NAME::vector<TEST_TYPE>(3, 100);
	bar = TEST_NAME::vector<TEST_TYPE>(2, 200);
	std::cout << std::boolalpha << (foo == bar) << std::endl;
	std::cout << std::boolalpha << (foo != bar) << std::endl;
	std::cout << std::boolalpha << (foo < bar) << std::endl;
	std::cout << std::boolalpha << (foo > bar) << std::endl;
	std::cout << std::boolalpha << (foo <= bar) << std::endl;
	std::cout << std::boolalpha << (foo >= bar) << std::endl;
	return 0;
}