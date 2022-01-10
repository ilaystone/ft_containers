#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <memory>
#include <functional>
#include "pair.hpp"
#include "algorithm.hpp"

namespace ft
{
	template < class Key, class T, class Compare, typename Node, bool B >
	class map_iterator
	{
	public:
		typedef Key                                             key_type;
		typedef Compare                                         key_compare;
		typedef T                                               mapped_type;
		
		typedef ft::pair<const key_type, mapped_type>           value_type;
		typedef long int                                        difference_type;
		typedef size_t                                          size_type;
		
		typedef std::bidirectional_iterator_tag                                     iterator_category;
		typedef typename chooseConst<B, value_type&, const value_type&>::type       reference;
		typedef typename chooseConst<B, value_type*, const value_type*>::type       pointer;
		typedef Node*                                                               nodePtr;
	};
	template <	class Key,
				class T,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
	protected:
		// * Attributes
		struct Node
		{
			ft::pair<const Key, T>		content;
			Node						*parent;
			Node						*left;
			Node						*right;
		};
	public:
		// * Aliases
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;
		typedef	allocator_type::reference				reference;
		typedef allocator_type::const_reference			const_reference;
		typedef	allocator_type::pointer					pointer;
		typedef allocator_type::const_pointer			const_pointer;
	}
}

#endif