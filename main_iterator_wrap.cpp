#include "common_test_template.hpp"

int main ()
{
	TEST_NAME::vector<int>				myvec;
	myvec.push_back(1);
	myvec.push_back(2);
	myvec.push_back(3);
	myvec.push_back(4);

	std::cout << "\tVECTOR ITERATOR" << std::endl;
	std::cout << "Forward iterator requirement :" << std::endl;
	TEST_NAME::vector<int>::iterator	it = myvec.begin();
	std::cout << *it << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *it << std::endl;
	std::cout << *++it << std::endl;
	it++;
	std::cout << *it << std::endl;
	std::cout << std::boolalpha << (it == myvec.begin()) << std::endl;
	std::cout << std::boolalpha << (it != myvec.begin()) << std::endl;
	it++;
	std::cout << std::boolalpha << (it == myvec.end()) << std::endl;
	std::cout << std::boolalpha << (it != myvec.end()) << std::endl;
	std::cout << "Biderectional iterator requirement :" << std::endl;
	it = myvec.begin();
	TEST_NAME::vector<int>::const_iterator 	ite(it); // 
	std::cout << *it << std::endl;
	it++;
	std::cout << *it-- << std::endl;
	it++;
	std::cout << *--it << std::endl;
	std::cout << "Random access iterator requirement :" << std::endl;
	it = myvec.begin();
	std::cout << it[0] << ' ' << it[2] << std::endl;
	it += 3;
	std::cout << *it << std::endl;
	it -= 2;
	std::cout << *it << std::endl;
	it = it + 1;
	std::cout << *it << std::endl;
	it = it - 2;
	std::cout << *it << std::endl;
	std::cout << std::boolalpha << (myvec.begin() < myvec.begin()) << std::endl;
	std::cout << std::boolalpha << (myvec.begin() < myvec.end()) << std::endl;
	std::cout << std::boolalpha << (myvec.begin() <= myvec.begin()) << std::endl;
	std::cout << std::boolalpha << (myvec.begin() > myvec.begin()) << std::endl;
	std::cout << std::boolalpha << (myvec.begin() > myvec.end()) << std::endl;
	std::cout << std::boolalpha << (myvec.begin() >= myvec.begin()) << std::endl;
	it = myvec.begin();
	TEST_NAME::vector<int>::iterator	end = myvec.end();
	std::cout << it - end << std::endl;
	std::cout << end - it << std::endl;
	return 0;
}