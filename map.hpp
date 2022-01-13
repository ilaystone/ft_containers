#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <memory>
#include <functional>
#include "pair.hpp"
#include "algorithm.hpp"

namespace ft
{
	template <	class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const key_type, mapped_type>			value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::diffrence_type		diffrence_type;

	}; // class map
} // namespace ft

#endif