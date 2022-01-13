#ifndef __AVL_TREE__
#define __AVL_TREE__

#include "iterator_traits.hpp"
#include "algorithm.hpp"

#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include <memory>
#include <iterator>
#include <exception>
#include <stdexcept>
#include <type_traits>

namespace ft
{
	template < typename T, typename Allocator = std::allocator<T> >
	class avl_tree
	{
	public:
		typedef Allocator									allocator_type;
		typedef typename allocator_type::value_type			value_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::diffrence_type		diffrence_type;


	private:
		class node
		{
		public:
			T				data;
			short			depth;
			size_type		n;
			node			*parent;
			node			*left_child;
			node			*right_child;

			node() : depth(1), n(1), left_child(nullptr), right_child(nullptr), parent(nullptr)
			{ }

			node(const T& t) : data(t), depth(1), n(1), left_child(nullptr), right_child(nullptr), parent(nullptr)
			{ }

			node(T &&t) : data(std::move(t)), depth(1), n(1), left_child(nullptr), right_child(nullptr), parent(nullptr)
			{ }

			void	update_depth(void)
			{
				depth = 1 + std::max(left_child ? left_child->depth : 0, right_child ? right_child->depth : 0);
			}

			void	update_n(void)
			{
				n = 1 + (left_child ? left_child->depth : 0) + (right_child ? right_child->depth : 0);
			}

			short	imbalance(void)
			{
				return ((right_child ? right_child->depth : 0) - (left_child ? left_child->depth : 0));
			}
		}; // class node

	public:
		class __avl_tree_iterator
		{
			template < typename Key, typename T >
			friend class avl_tree<Key, T>::__const_map_iterator;
			friend class avl_tree;
		protected:
			node												*__ptr;
		public:
			typedef ft::bidirectional_iterator_tag				iterator_category;
			typedef typename allocator_type::value_type			value_type;
			typedef typename allocator_type::diffrence_type		diffrence_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::pointer			pointer;

			__avl_tree_iterator()
			{
				__ptr = nullptr;
			}

			__avl_tree_iterator(node *p)
			{
				__ptr = p;
			}

			__avl_tree_iterator(const __avl_tree_iterator &rhs)
			{
				__ptr = rhs.__ptr;
			}

			__avl_tree_iterator	&operator=(const __avl_tree_iterator &rhs)
			{
				__ptr = rhs.__ptr;
				return (*this);
			}

			bool			operator==(const __avl_tree_iterator &rhs) const
			{
				return (__ptr == rhs.__ptr);
			}

			bool			operator!=(const __avl_tree_iterator &rhs) const
			{
				return (__ptr != rhs.__ptr);
			}

			bool			operator<(const __avl_tree_iterator &rhs) const
			{
				return (**this < *rhs);
			}

			bool			operator<=(const __avl_tree_iterator &rhs) const
			{
				return (**this <= *rhs);
			}

			bool			operator>(const __avl_tree_iterator &rhs) const
			{
				return (**this > *rhs);
			}

			bool			operator>=(const __avl_tree_iterator &rhs) const
			{
				return (**this >= *rhs);
			}

			__avl_tree_iterator		&operator++(void)
			{
				if (__ptr->right_child)
				{
					__ptr = __ptr->right_child;
					while (__ptr->left_child)
						__ptr = __ptr->left_child;
				}
				else
				{
					node		*before;
					do
					{
						before = __ptr;
						__ptr = ptr->parent;
					} while (ptr && before == ptr->right_child);
				}
				return (*this);
			}

			__avl_tree_iterator		operator++(int)
			{
				__avl_tree_iterator		old(*this);
				++(*this);
				return (old);
			}

			__avl_tree_iterator		&operator--(void)
			{
				if (__ptr->left_child)
				{
					__ptr = __ptr->left_child;
					while (__ptr->right_child)
						__ptr = __ptr->right_child;
				}
				else
				{
					node		*before;
					do
					{
						before = __ptr;
						__ptr = ptr->parent;
					} while (__ptr && before == __ptr->left_child);
				}
			}

			__avl_tree_iterator		operator--(int)
			{
				__avl_tree_iterator		old(*this);
				--(*this);
				return (old);
			}

			reference				operator*(void) const
			{
				return (__ptr->data);
			}

			pointer					operator->(void) const
			{
				return (&(__ptr->data));
			}

		} // class __avl_tree_iterator

		class __const_avl_tree_iterator
		{
		protected:
			node												*__ptr;
		public:
			typedef ft::bidirectional_iterator_tag				iterator_category;
			typedef typename allocator_type::value_type			value_type;
			typedef typename allocator_type::diffrence_type		diffrence_type;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::const_pointer		const_pointer;

			__const_avl_tree_iterator(void)
			{
				__ptr = nullptr;
			}

			__const_avl_tree_iterator(node *p)
			{
				__ptr = p;
			}

			__const_avl_tree_iterator(const __const_avl_tree_iterator &rhs)
			{
				__ptr = rhs.__ptr;
			}

			__const_avl_tree_iterator	&operator=(const __const_avl_tree_iterator &rhs)
			{
				__ptr = rhs.__ptr;
				return (*this);
			}

			bool						operator==(const __const_avl_tree_iterator &rhs) const
			{
				return (__ptr == rhs.__ptr);
			}

			bool						operator!=(const __const_avl_tree_iterator &rhs) const
			{
				return (__ptr != rhs.__ptr);
			}

			bool						operator<(const __const_avl_tree_iterator &rhs) const
			{
				return (**this < *rhs);
			}

			bool						operator<=(const __const_avl_tree_iterator &rhs) const
			{
				return (**this <= *rhs);
			}

			bool						operator>(const __const_avl_tree_iterator &rhs) const
			{
				return (**this > *rhs);
			}

			bool						operator>=(const __const_avl_tree_iterator &rhs) const
			{
				return (**this >= *rhs);
			}

			__const_avl_tree_iterator	&operator++(void)
			{
				if (__ptr->right_child)
				{
					__ptr = __ptr->right_child;
					while (__ptr->left_child)
						__ptr = __ptr->left_child;
				}
				else
				{
					const node		*before;
					do
					{
						before = __ptr;
						ptr = ptr->parent;
					} while (__ptr && before == __ptr->right_child);
				}
				return (*this);
			}

			__const_avl_tree_iterator	operator++(int)
			{
				__const_avl_tree_iterator	old(*this);
				++(*this);
				return (old);
			}

			__const_avl_tree_iterator	&operator--(void)
			{
				if (__ptr->left_child)
				{
					__ptr = __ptr->left_child;
					while (__ptr->right_child)
						__ptr = __ptr->right_child;
				}
				else
				{
					const node		*before;
					do
					{
						before = __ptr;
						ptr = ptr->parent;
					} while (__ptr && before == __ptr->left_child);
				}
				return (*this);
			}

			__const_avl_tree_iterator	operator--(int)
			{
				__const_avl_tree_iterator	old(*this);
				--(*this);
				return (old);
			}

			const_reference				operator*(void) const
			{
				return ((const_reference)(__ptr->data));
			}

			const_pointer				operator->(void) const
			{
				return (&(__ptr->data));
			}

		} // class __const_avl_tree_iterator

		avl_tree(void)
		{
			__root = alloc.allocate(1);
			alloc.construct(__root);
			__root->n = 0;
		}

		avl_tree(const avl_tree &rhs)
		{
			*this = rhs;
		}

		avl_tree(tree &&rhs)
		{
			__root = rhs.__root;
			rhs.__root = alloc.allocate(1);
			alloc.construct(rhs.__root);
			rhs.__root->n = 0;
		}

		~avl_tree(void)
		{
			clear_node(__root);
			alloc.destroy(__root);
			alloc.deallocate(__root, 1);
		}

		avl_tree						&operator=(const avl_tree &rhs)
		{
			__root = deep_copy_node(rhs.__root);
			return (*this);
		}

		avl_tree	&operator(avl_tree &&rhs)
		{
			clear();
			ft::swap(__root, rhs.__root);
			return (*this);
		}

		bool							operator==(const avl_tree &rhs) const
		{
			__const_avl_tree_iterator		it1, it2;
			for (it = cbegin(), it2 = rhs.cbegin(); it1 != cend() && it2 != rhs.cend(); ++it1, ++it2)
			{
				if (*it1 != *it2)
					return (false);
			}
			if (it1 == cend() && it2 == rhs.cend())
				return (true);
			else
				return (false);
		}

		bool							operator!=(const avl_tree &rhs)
		{
			return (!(*this == rhs));
		}

		__avl_tree_iterator				begin(void)
		{
			node		*ptr = root;
			while (ptr->left_child)
			{
				ptr = ptr->left_child;
			}
			return (__const_avl_tree_iterator(ptr));
		}

		__const_avl_tree_iterator		begin(void) const
		{
			const node		*ptr = root;
			while (ptr->left_child)
			{
				ptr = ptr->left_child;
			}
			return (__avl_tree_iterator(ptr));
		}

		__const_avl_tree_iterator				cbegin(void) const
		{
			const node		*ptr = root;
			while (ptr->left_child)
			{
				ptr = ptr->left_child;
			}
			return (__const_avl_tree_iterator(ptr));
		}

		__avl_tree_iterator				end(void)
		{
			
		}


	protected:
		using	NodeAlloc = typename std::allocator_traits<allocator_type>::tempalte	rebind_alloc<node>;

		NodeAlloc	alloc;
		node		*__root;

	}; // class avl_tree

} // namespace ft

#endif