#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "avl_tree.hpp"

#include <memory>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <map>

namespace ft
{
	template < class Key,                                // map::key_type
		class T,                                         // map::mapped_type
		class Compare = std::less<Key>,                  // map::key_compare
		class Alloc = std::allocator<ft::pair<const Key,T> > // map::allocator_type
		>
	class map {
		typedef ft::map<Key, T, Compare, Alloc>									__base;
	public:
		// ******************************* Aliases ******************************* //
		typedef Key																key_type;
		typedef T																mapped_type;
		typedef pair<const key_type, mapped_type>								value_type;
		typedef Compare															key_compare;
		class																	value_compare;

		typedef Alloc															allocator_type;
		typedef typename allocator_type::reference								reference;
		typedef typename allocator_type::const_reference						const_reference;
		typedef typename allocator_type::pointer								pointer;
		typedef typename allocator_type::const_pointer							const_pointer;

		typedef typename std::allocator_traits<Alloc>::template
			rebind_alloc<value_type>::other										__pair_alloc_type;
		typedef	avl_tree<value_type, mapped_type, key_type, key_compare, __pair_alloc_type>	
			AVT_type;

		typedef typename AVT_type::__avl_tree_iterator							iterator;
		typedef typename AVT_type::__const_avl_tree_iterator					const_iterator;
		typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
		typedef	typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename allocator_type::size_type								size_type;
		typedef typename allocator_type::difference_type 						difference_type;


	// ******************************* Non-public ******************************* //
	private:
		AVT_type		__ptr;
		key_compare		__comp;
		allocator_type	__alloc;

	public:

	// ************************** Member functions ****************************** //

		explicit map(const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type())
		:	__ptr(),
			__comp(comp),
			__alloc(alloc)
		{
			return ;
		}
		template <class Ite>
		map(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
				Ite last, const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type())
		:	__ptr(),
			__comp(comp),
			__alloc(alloc)
		{
			for (Ite it = first; it != last; it++)
			{
				if (count((*it).first) == 0)
					__ptr.insert(*it);
			}
		}
		map(const map &src)
		{
			*this = src;
		}
		virtual ~map(void)
		{
			return ;
		}

		map	&operator=(map const &rhs)
		{
			__ptr = rhs.__ptr;
			__comp = rhs.__comp;
			__alloc = rhs.__alloc;
			return *this;
		}

	// ****************************** Iterators ********************************* //

		iterator				begin(void)
		{
			return __ptr.begin();
		}
		const_iterator			begin(void) const
		{
			return __ptr.begin();
		}
		iterator				end(void)
		{
			return __ptr.end();
		}
		const_iterator			end(void) const
		{
			return __ptr.end();
		}

		reverse_iterator		rbegin(void)
		{
			return ft::reverse_iterator<iterator>(__ptr.end());
		}
		const_reverse_iterator	rbegin(void) const
		{
			return ft::reverse_iterator<iterator>(__ptr.end());
		}
		reverse_iterator		rend(void)
		{
			return ft::reverse_iterator<iterator>(__ptr.begin());
		}
		const_reverse_iterator	rend(void) const
		{
			return ft::reverse_iterator<iterator>(__ptr.begin());
		}

	// ******************************* Capacity ********************************* //

		size_type	size(void) const
		{
			return __ptr.size();
		}
		size_type	max_size(void) const
		{
			return __ptr.max_size();
		}
		bool		empty(void) const
		{
			return this->size() == 0;
		}

	// ******************************* Ele Access ******************************* //

		mapped_type	&operator[](const key_type &k)
		{
			return (insert(ft::make_pair(k, mapped_type())).first)->second;
		}

	// ******************************** Modifiers ******************************* //

		ft::pair<iterator, bool>	insert(const value_type &val)
		{
			if (count(val.first))
				return (make_pair(find(val.first), 0));
			__ptr.insert(val);
			return make_pair(find(val.first), 1);
		}
		iterator					insert(iterator position, const value_type &val)
		{
			position = insert(val).first;
			return (position);
		}
		template <class Ite> void	insert(Ite first, Ite last)
		{
			for (Ite it = first; it != last; it++)
			{
				if (count(it->first) == 0)
				{
					__ptr.insert(ft::make_pair(it->first, it->second));
				}
			}
		}

		void						erase(iterator position)
		{
			__ptr.erase(position);
		}
		size_type					erase(const key_type &k)
		{
			if (count(k) == 0)
				return 0;
			for (iterator it = begin(); it != end(); it++)
			{
				if (it->first == k)
					__ptr.erase(it);
			}
			return 1;
		}
		void						erase(iterator first, iterator last)
		{
			iterator		tmp;
			while (first != last)
			{
				tmp = first;
				first++;
				__ptr.erase(tmp);
			}
		}

		void						swap(map &x)
		{
			this->__ptr.swap(x.__ptr);
		}
		void						clear(void)
		{
			__ptr.clear();
		}

	// ******************************* Observers ******************************** //

		key_compare		key_comp(void) const
		{
			return __comp;
		}
		value_compare	value_comp(void) const
		{
			return value_compare(__comp);
		}

	// ******************************* Operations ******************************* //

		iterator							find(const key_type &k)
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (it->first == k)
					return it;
			}
			return end();
		}
		const_iterator						find(const key_type &k) const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if (it->first == k)
					return it;
			}
			return end();
		}
		size_type							count(const key_type &k) const
		{
			return this->find(k) == this->end() ? 0 : 1;
		}

		iterator							lower_bound(const key_type &k)
		{
			iterator begin;

			for (begin = this->begin(); begin != this->end(); begin++)
			{
				if (!__comp((*begin).first, k))
					return begin;
			}
			return begin;
		}
		const_iterator						lower_bound(const key_type &k) const
		{
			const_iterator	begin;

			for (begin = this->begin(); begin != this->end(); begin++)
			{
				if (!__comp((*begin).first, k))
					return begin;
			}
			return begin;
		}
		iterator							upper_bound(const key_type &k)
		{
			iterator	begin;

			for (begin = this->begin(); begin != this->end(); begin++)
			{
				if (__comp(k, (*begin).first))
					return begin;
			}
			return begin;
		}
		const_iterator						upper_bound(const key_type &k) const
		{
			const_iterator	begin;

			for (begin = this->begin(); begin != this->end(); begin++)
			{
				if (__comp(k, (*begin).first))
					return begin;
			}
			return begin;
		}
		pair<const_iterator,const_iterator>	equal_range(const key_type &k) const
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		pair<iterator,iterator>				equal_range(const key_type &k)
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

	// ************************** Allocator ************************************ //

		allocator_type get_allocator() const
		{
			return allocator_type();
		}

	// ************************** Base ************************************ //
	public:
		AVT_type	&_m_base()
		{
			return __ptr;
		}

		const AVT_type	&_m_base() const
		{
			return __ptr;
		}

	};

	template <class Key, class T, class Compare, class Alloc>
	class	map<Key, T, Compare, Alloc>::value_compare {
		public:
		Compare comp;
		value_compare(Compare c) : comp(c) { };

		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;
		bool	operator()(const value_type &x, const value_type &y) const {
			return comp(x.first, y.first);
		}
	};

	// define relational operations
	template <class Key, class T, class Compare, class Alloc>
	inline bool
	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs._m_base() == rhs._m_base();
	}
	template <class Key, class T, class Compare, class Alloc>
	inline bool
	operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs._m_base() != rhs._m_base();
	}
	template <class Key, class T, class Compare, class Alloc>
	inline bool
	operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs._m_base() < rhs._m_base();
	}
	template <class Key, class T, class Compare, class Alloc>
	inline bool
	operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs._m_base() <= rhs._m_base();
	}
	template <class Key, class T, class Compare, class Alloc>
	inline bool
	operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs._m_base() > rhs._m_base();
	}
	template <class Key, class T, class Compare, class Alloc>
	inline bool
	operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs._m_base() >= rhs._m_base();
	}
}

#endif