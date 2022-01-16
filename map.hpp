#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <memory>
#include <functional>
#include "pair.hpp"
#include "algorithm.hpp"
#include "avl_tree.hpp"
#include "iterator.hpp"

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
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map<key_type, mapped_type, key_compare, allocator_type>;
		protected:
			key_compare			comp;
			value_compare(key_compare c) : comp(c) { }
		public:
			bool				operator()(const value_type &lhs, const value_type &rhs)
			{
				return (comp(lhs.first, rhs.firs));
			}
		};
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;

		typedef avl_tree<value_type, allocator_type>				rep_tree;
		typedef typename rep_tree::__avl_tree_iterator				iterator;
		typedef	typename rep_tree::__const_avl_tree_iterator		const_iterator;
		typedef typename rep_tree::size_type						size_type;
		typedef typename rep_tree::diffrence_type					diffrence_type;
		typedef ft::reverse_iterator<iterator>						revese_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

	protected:
		allocator_type		__alloc;
		key_compare			__comp;
		rep_tree			__ptr;

	public:
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		:	__alloc(alloc),
			__comp(comp),
			__ptr()
		{ }

		mapped_type		&operator[](const key_type &k)
		{
			
		}

	}; // class map
} // namespace ft

#endif