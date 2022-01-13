#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

#include "iterator_traits.hpp"

namespace ft
{
	/**
	 * @brief Compares the lements of range [firts1, last1) with those in the range [fiorst2, last2)
	 * 	and returns true if first range is lexographicaly less than second range
	 * 
	 * @tparam InputIterator1 type of first range
	 * @tparam InputIterator2 type of second range
	 * @param first1 begining of first range
	 * @param last1 end of first range
	 * @param first2 begining of second range
	 * @param last2 end of second range
	 * @return true 
	 * @return false 
	 */
	template < class InputIterator1, class InputIterator2 >
	bool lexographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}
	/**
	 * @brief Compares the lements of range [firts1, last1) with those in the range [fiorst2, last2)
	 * 	and returns true if first range is equal to the second range
	 * 
	 * @tparam InputIterator1 type of first range
	 * @tparam InputIterator2 type of second range
	 * @param first1 begining of first range
	 * @param last1 end of first range
	 * @param first2 begining of second range
	 * @param last2 end of second range
	 * @return true 
	 * @return false 
	 */
	template < class InputIterator1, class InputIterator2 >
	bool	equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			first1++;
			first2++;
		}
		return (true);
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
	/**
	 * @brief returns the count of objects in the range [@first, @last)
	 * 
	 * @tparam InputIterator type if iterators
	 * @param first start of range
	 * @param last end of range
	 * @return ft::iterator_traits<InputIterator>::difference_type 
	 */
	template < class InputIterator >
	typename ft::iterator_traits<InputIterator>::difference_type		distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type result = 0;
		while (first != last)
		{
			first++;
			result++;
		}
		return (result);
	}
}

#endif