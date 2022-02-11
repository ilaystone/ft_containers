#ifndef MAP_HPP
#define MAP_HPP

#include "map_base.hpp"
#include "map_iterator.hpp"
#include "pair.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "iterator_traits.hpp"
#include "iterator.hpp"

namespace ft
{
	template < class Key,                                // map::key_type
		class T,                                         // map::mapped_type
		class Compare = std::less<Key>,                  // map::key_compare
		class Alloc = std::allocator<pair<const Key,T> > // map::allocator_type
		>
	class map {
		public:

		typedef Key													key_type;
		typedef T													mapped_type;
		typedef pair<const key_type, mapped_type>					value_type;
		typedef Compare												key_compare;
		class														value_compare;

		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef ft::mapNode<value_type>								node_type;
		typedef node_type*											node_ptr;

		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;

		typedef ft::map_iterator<value_type, node_type>				iterator;
		typedef ft::map_iterator<const value_type, node_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

	// ************************** Member functions ****************************** //

		explicit map(const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type());
		template <class Ite>
		map(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
				Ite last, const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type());
		map(const map &src);
		virtual ~map(void);

		map	&operator=(map const &rhs);

	// ****************************** Iterators ********************************* //

		iterator				begin(void);
		const_iterator			begin(void) const;
		iterator				end(void);
		const_iterator			end(void) const;

		reverse_iterator		rbegin(void);
		const_reverse_iterator	rbegin(void) const;
		reverse_iterator		rend(void);
		const_reverse_iterator	rend(void) const;

	// ******************************* Capacity ********************************* //

		size_type	size(void) const;
		size_type	max_size(void) const;
		bool		empty(void) const;

	// ******************************* Ele Access ******************************* //

		mapped_type	&operator[](const key_type &k);

	// ******************************** Modifiers ******************************* //

		ft::pair<iterator, bool>	insert(const value_type &val);
		iterator					insert(iterator position, const value_type &val);
		template <class Ite> void	insert(Ite first, Ite last);

		void		erase(iterator position);
		size_type	erase(const key_type &k);
		void		erase(iterator first, iterator last);

		void		swap(map &x);
		void		clear(void);

	// ******************************* Observers ******************************** //

		key_compare		key_comp(void) const;
		value_compare	value_comp(void) const;

	// ******************************* Operations ******************************* //

		iterator		find(const key_type &k);
		const_iterator	find(const key_type &k) const;
		size_type		count(const key_type &k) const;

		iterator		lower_bound(const key_type &k);
		const_iterator	lower_bound(const key_type &k) const;
		iterator		upper_bound(const key_type &k);
		const_iterator	upper_bound(const key_type &k) const;
		pair<const_iterator,const_iterator>	equal_range(const key_type &k) const;
		pair<iterator,iterator>				equal_range(const key_type &k);

	// ************************** Allocator ************************************ //

		allocator_type get_allocator() const;

	// ******************************* Non-public ******************************* //

		protected:
		private:
		node_ptr				_data;
		key_compare				_key_cmp;
		allocator_type			_alloc;
		size_type				_size;
		const static size_type	_max_size;
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