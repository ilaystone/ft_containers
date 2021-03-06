#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__

#include <cstddef>  // For std::ptrdiff_t
namespace ft
{
	/**
	 * @brief a list of tags that semantically defines the behavior of an iterator
	 * 
	 */
	struct input_iterator_tag  {};

	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag         {};
	struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/**
	 * @brief a pseudo-interface defining basic info about an iterator(its traits)
	 * 
	 * @tparam Iterator 
	 */
	template< class Iterator >
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template< class T >
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t				        difference_type;
		typedef T						        	value_type;
		typedef T*						        	pointer;
		typedef T&						        	reference;
		typedef random_access_iterator_tag	        iterator_category;
	};

	template< class T >
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t			        	difference_type;
		typedef T						        	value_type;
		typedef const T*					        pointer;
		typedef const T&					        reference;
		typedef random_access_iterator_tag          iterator_category;
	};

	/**
	 * @brief pseudo-interface defining basic info about an iterato
	 * basiacly forcing an iterator class to have these typedefs
	 * (usally extraced from the iterator_traits class)
	 * 
	 * @tparam Category 
	 * @tparam T 
	 * @tparam Distance 
	 * @tparam Pointer 
	 * @tparam Reference 
	 */
	template< class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T& >
	struct __iterator__
	{
		typedef T         							value_type;
		typedef Distance  							difference_type;
		typedef Pointer   							pointer;
		typedef Reference 							reference;
		typedef Category  							iterator_category;
	};

}

#endif