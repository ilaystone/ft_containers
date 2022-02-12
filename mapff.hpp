#ifndef MAP_HPP
#define MAP_HPP

#include <functional>

#include "utils/binary_search_tree.hpp"

namespace ft
{

	// define the map container
	template <class Key,										// map::key_type
			  class T,											// map::mapped_type
			  class Compare = std::less<Key>,					// map::key_compare
			  class Alloc = std::allocator<pair<const Key, T> > // map::allocator_type
			  >
	class map
	{
	private:
	public:
		// typedef typenames
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;

		private:
			key_compare comp;

		public:
			value_compare(const key_compare &x) : comp(x) {}
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef BinarySearchTree<value_type, value_compare> tree_type;
		typedef TreeIterator<value_type> iterator;
		typedef ConstTreeIterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		// define construtors

		// empty (1)
		explicit map(const key_compare &compr = key_compare(),
					 const allocator_type &alloct = allocator_type()) : tree(compr), comp(compr), alloc(alloct) {}

		// range (2)
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &compr = key_compare(),
			const allocator_type &alloct = allocator_type()) : tree(compr), comp(compr), alloc(alloct)
		{
			this->insert(first, last);
		}

		// copy (3)
		map(const map &x) : tree(x.tree), comp(x.comp), alloc(x.alloc) {}
		
		//destructor
		~map() {}

		// operator=
		map &operator=(const map &x)
		{
			if (this != &x)
			{
				this->clear();
				this->insert(x.begin(), x.end());
			}
			return *this;
		}

		// Iterators:

		iterator begin()
		{
			return tree.getStart();
		}

		const_iterator begin() const
		{
			return const_iterator(tree.getStart());
		}

		iterator end()
		{
			return tree.getEnd();
		}

		const_iterator end() const
		{
			return const_iterator(tree.getEnd());
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(tree.getEnd());
		}
		const_reverse_iterator rbegin() const
		{
			return reverse_iterator(tree.getEnd());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(tree.getStart());
		}
		const_reverse_iterator rend() const
		{
			return reverse_iterator(tree.getStart());
		}

		// Capacity:

		bool empty() const
		{
			return this->size() == 0;
		}

		size_type size() const
		{
			return tree.getSize();
		}

		size_type max_size() const
		{
			return tree.max_size();
		}

		// Element access:

		mapped_type &operator[](const key_type &k)
		{
			return (this->insert(make_pair(k, mapped_type())).first)->second;
		}

		// Modifiers:

		// insert
		// single element (1)
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			return tree.insert(val);
		}
		// with hint (2)
		iterator insert(iterator hint, const value_type &val)
		{
			return tree.insert(hint, val);
		}
		// range (3)
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
				tree.insert(*first++);
		}

		// erase

		// (1)
		void erase(iterator position)
		{
			tree.removeByPosition(position);
		}
		// single element (2)
		size_type erase(const key_type &k)
		{
			iterator it = find(k);
			if (it == this->end())
				return 0;
			tree.removeByPosition(it);
			return 1;
		}
		// range (3)
		iterator erase(iterator first, iterator last)
		{
			while (first != last)
				tree.removeByPosition(first++);
			return first;
		}

		void swap(map &x)
		{
			tree.swap(x.tree);
		}

		void clear()
		{
			tree.clear();
		}

		// Observers:

		key_compare key_comp() const
		{
			return comp;
		}

		value_compare value_comp() const
		{
			return value_compare(tree.getComp());
		}

		// Operations:
		iterator find(const key_type &k)
		{
			return tree.findByKey(k);
		}
		const_iterator find(const key_type &k) const
		{
			return tree.findByKey(k);
		}

		size_type count(const key_type &k) const
		{
			iterator it = this->begin();
			while (it != this->end())
			{
				if ((*it).first == k)
					return 1;
				++it;
			}
			return 0;
		}

		iterator lower_bound(const key_type &k)
		{
			iterator curr = this->begin();
			iterator ite = this->end();

			while (curr != ite)
			{
				if (!comp((*curr).first, k))
					return curr;
				curr++;
			}
			return curr;
		}
		const_iterator lower_bound(const key_type &k) const
		{
			return this->lower_bound(k);
		}

		iterator upper_bound(const key_type &k)
		{
			iterator curr = this->begin();
			iterator ite = this->end();

			while (curr != ite)
			{
				if (comp(k, (*curr).first))
					return curr;
				curr++;
			}
			return curr;
		}
		const_iterator upper_bound(const key_type &k) const
		{
			return this->upper_bound(k);
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		
		pair<iterator, iterator> equal_range(const key_type &k)
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		// Allocator:
		allocator_type get_allocator() const
		{
			return this->alloc;
		}

	private:
		// define data members
		tree_type tree;
		key_compare comp;
		allocator_type alloc;
	}; // map class

} // namespace ft

#endif // MAP_HPP
