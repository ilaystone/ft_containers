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

	template <class _T1, class _T2 = _T1>
	struct __equal_to
	{
		bool operator()(const _T1& __x, const _T1& __y) const {return __x == __y;}
	};
	/**
	 * @brief 
	 * 
	 * @tparam InputIterator1 
	 * @tparam InputIterator2 
	 * @tparam BinaryPredicate 
	 * @param first1 
	 * @param last1 
	 * @param first2 
	 * @param pred 
	 * @return true 
	 * @return false 
	 */
	template < class InputIterator1, class InputIterator2, class BinaryPredicate >
	bool	equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, (void) ++first2)
			if (!pred(*first1, *first2))
				return (false);
		return (true);
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
		typedef typename ft::iterator_traits<InputIterator1>::value_type	v1;
		typedef typename ft::iterator_traits<InputIterator2>::value_type	v2;
		return (ft::equal(first1, last1, first2, ft::__equal_to<v1, v2>()));
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
	template <class T>
    struct less
    {
        typedef T       first_argument_type;
        typedef T       second_argument_type;
        typedef bool    result_type;
        
        bool operator() (const T& x, const T& y) const {return x<y;}
        
    }; // less
}

#endif