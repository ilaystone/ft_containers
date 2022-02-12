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

namespace ft
{
	template < class Key,                                // map::key_type
		class T,                                         // map::mapped_type
		class Compare = std::less<Key>,                  // map::key_compare
		class Alloc = std::allocator<ft::pair<const Key,T> > // map::allocator_type
		>
	class map {
	public:

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
			rebind_alloc<value_type>::other	__pair_alloc_type;
		typedef	ft::avl_tree<value_type, __pair_alloc_type>						AVT_type;

		typedef typename AVT_type::__avl_tree_iterator							iterator;
		typedef typename AVT_type::__const_avl_tree_iterator					const_iterator;
		typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
		typedef	typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename allocator_type::size_type								size_type;
		typedef typename allocator_type::difference_type 						difference_type;



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
			for (Ite it = first, first != last, first++)
				__ptr.insert(*first);
		}
		map(const map &src)
		{
			if (this != *src)
			{
				*this = src;
			}
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
		const_reverse_iterator	rbegin(void) const;
		reverse_iterator		rend(void);
		const_reverse_iterator	rend(void) const;

	// ******************************* Capacity ********************************* //

		size_type	size(void) const;
		size_type	max_size(void) const;
		bool		empty(void) const;

	// ******************************* Ele Access ******************************* //

		mapped_type	&operator[](const key_type &k)
		{
			iterator		it = __ptr.find(ft::make_pair(k, mapped_type()));
			if (it == __ptr.end())
				std::cout << "it is the end\n"<< std::endl;
			std::cout << (*it).first << ", " << (*it).second << std::endl;
			return __ptr[k].second;
		}

	// ******************************** Modifiers ******************************* //

		ft::pair<iterator, bool>	insert(const value_type &val)
		{
			return __ptr.insert(val);
		}
		iterator					insert(iterator position, const value_type &val);
		template <class Ite> void	insert(Ite first, Ite last);

		void						erase(iterator position);
		size_type					erase(const key_type &k);
		void						erase(iterator first, iterator last);

		void						swap(map &x);
		void						clear(void);

	// ******************************* Observers ******************************** //

		key_compare		key_comp(void) const;
		value_compare	value_comp(void) const;

	// ******************************* Operations ******************************* //

		iterator							find(const key_type &k);
		const_iterator						find(const key_type &k) const;
		size_type							count(const key_type &k) const;

		iterator							lower_bound(const key_type &k);
		const_iterator						lower_bound(const key_type &k) const;
		iterator							upper_bound(const key_type &k);
		const_iterator						upper_bound(const key_type &k) const;
		pair<const_iterator,const_iterator>	equal_range(const key_type &k) const;
		pair<iterator,iterator>				equal_range(const key_type &k);

	// ************************** Allocator ************************************ //

		allocator_type get_allocator() const;

	// ******************************* Non-public ******************************* //

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

}

#endif