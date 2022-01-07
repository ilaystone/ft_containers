#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

namespace ft
{
	template < class InputIterator1, class InputIterator2 >
	bool lexographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		
	}
	/**
	 * @brief swaps two elements @a and @b classes that make use of this
	 * 	should have copy constructor implemented
	 * 
	 * @tparam U type of objects to swap
	 * @param a first object
	 * @param b second object
	 */
	template < typename T >
	void swap(T &a, T &b)
	{
		T tmp(a);
		a = b;
		b = tmp;
	}
}

#endif