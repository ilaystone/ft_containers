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
		public:
			node												*__ptr;
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
			return (__avl_tree_iterator(__root));
		}

		__const_avl_tree_iterator		end(void) const
		{
			return (__const_avl_tree_iterator(__root));
		}

		__const_avl_tree_iterator		cend(void) const
		{
			return (__const_avl_tree_iterator(__root));
		}

		reference						front(void)
		{
			__avl_tree_iterator		b = begin();
			return (*b);
		}

		const_reference					front(void) const
		{
			__const_avl_tree_iterator	b = begin();
			return (*b);
		}

		reference						back(void)
		{
			__avl_tree_iterator		b = end();
			return (*b);
		}

		const_reference					back(void) const
		{
			__const_avl_tree_iterator	b = end();
			return (*b);
		}

		__avl_tree_iterator				insert(const T &t)
		{
			__avl_tree_iterator		res;

			node					*parent = __root;
			// binary search tree normal insertion
			while (true)
			{
				++parent->n;
				if (parent == __root || t < parent->data)
				{
					if (parent->left_child)
						parent = parent->left_child;
					else
					{
						parent->left_child = alloc.allocate(1);
						alloc.construct(parent->left_child, t);
						parent->left_child->parent = parent;
						res = __avl_tree_iterator(parent->left_child);
						break ;
					}
				}
				else
				{
					if (parent->right_child)
						parent = parent->right_child;
					else
					{
						parent->right_child = alloc.allocate(1);
						alloc.construct(parent->right_child, t);
						parent->right_child->parent = parent;
						res = __avl_tree_iterator(parent->right_child);
						break ;
					}
				}
			}
			// Balancing
			short		branch_depth = 1;
			do
			{
				if (parent->depth > branch_depth)
					break ;
				parent->depth = 1 + branch_depth;
				if (parent == __root)
					break ;
				if (parent->imbalance() < -1)
				{
					// double rotation case check
					if (parent->left_child->imbalance() > 0)
						rotate_left(parent->left_child);
					rotate_right(parent);
					break ;
				}
				else if (parent->imbalance() > 1)
				{
					// double rotation case check
					if (parent->right_child->imbalance() < 0)
						rotate_right(parent->right_child);
					rotate_left(parent);
					break ;
				}
				branch_depth = parent->depth;
				parent = parent->parent;
			} while (parent);
			return (res);
		}

		__avl_tree_iterator						at(size_type i)
		{
			if (i >= size())
				throw std::out_of_range("tree::at out-of-range");
			size_type		j = i;
			node			*ptr = __root->left_child;
			while (true)
			{
				if (ptr->left_child)
				{
					if (j == ptr->left_child->n)
						break ;
					else if (j < ptr->left_child->n)
						ptr = ptr->left_child;
					else
					{
						j -= 1 + ptr->left_child->n;
						ptr = ptr->right_child;
					}
				}
				else
				{
					if (j == 0)
						break ;
					else
					{
						j--;
						ptr = ptr->right_child;
					}
				}
			}
			return (__avl_tree_iterator(ptr));
		}

		__const_avl_tree_iterator						at(size_type i) const
		{
			if (i >= size())
				throw std::out_of_range("tree::at out-of-range");
			size_type		j = i;
			node			*ptr = __root->left_child;
			while (true)
			{
				if (ptr->left_child)
				{
					if (j == ptr->left_child->n)
						break ;
					else if (j < ptr->left_child->n)
						ptr = ptr->left_child;
					else
					{
						j -= 1 + ptr->left_child->n;
						ptr = ptr->right_child;
					}
				}
				else
				{
					if (j == 0)
						break ;
					else
					{
						j--;
						ptr = ptr->right_child;
					}
				}
			}
			return (__const_avl_tree_iterator(ptr));
		}

		reference						operator[](size_type i)
		{
			return (*at(i));
		}

		const_reference					operator[](size_type i) const
		{
			return (*at(i));
		}

		__avl_tree_iterator				erase(__avl_tree_iterator it)
		{
			__avl_tree_iterator			itn(it);

			++itn;
			node						*ptr = it.ptr;
			node						*q;
			if (!ptr->left_child || !ptr->right_child)
				q = ptr;
			else
				q = itn.ptr;
			node						*s;
			if (q->left_child)
			{
				s = q->left_child;
				q->left_child = nullptr;
			}
			else
			{
				s = q->right_child;
				q->right_child = nullptr;
			}
			if (s)
				s->parent = q->parent;
			if (q == q->parent->left_child)
				q->parent->left_child = s;
			else
				q->parent->right_child = s;
			node						*q_parent = ptr->parent;
			if (q != ptr)
			{
				q->parent = ptr->parent;
				if (q->parent->left_child == ptr)
					q->parent->left_child = q;
				else
					q->parent->right_child = q;
				q->left_child = ptr->right_child;
				if (q->left_child)
					q->left_child->parent = q;
				q->right_child = ptr->right_child;
				if (q->right_child)
					q->right_child->parent = q;
				q->n = ptr->n;
				q->depth = ptr->depth;
				ptr->left_child = nullptr;
				ptr->right_child = nullptr;
			}
			if (q_parent == ptr)
				q_parent = q;
			node					*parent;
			for (parent = q_parent; parent; parent = parent->parent)
				--parent->n;
			for (parent = q_parent; parent; parent = parent->parent)
			{
				parent->update_depth();
				if (parent == __root)
					break ;
				if (parent->imbalace() < -1)
				{
					if (parent->left_child->imbalance() > 0)
						rotate_left(parent->left_child);
					rotate_right(parent);
					break ;
				}
				else if (parent->imbalance() > 1)
				{
					if (parent->right_child->imbalance() < 0)
						rotate_right(parent->right_child);
					rotate_left(parent);
					break ;
				}
			}
			alloc.destroy(ptr);
			alloc.deallocate(ptr, 1);
			return (itn);
		}

		__avl_tree_iterator		find(const_reference rhs)
		{
			node			*ptr = __root->left_child;
			while (ptr)
			{
				if (rhs == ptr->data)
					return (__avl_tree_iterator(ptr));
				else if (rhs < ptr->data);
					ptr = ptr->left_child;
				else
					ptr = ptr->right_child;
			}
			return (end());
		}

		void		remove(const_reference rhs)
		{
			__avl_tree_iterator		it = find(rhs);
			if (it == end())
				return ;
			do
			{
				it = erase(it);
			} while (*it == rhs);
		}

		void		clear()
		{
			clear_node(__root);
			__root->left_child = nullptr;
			__root->n = 0;
			__root->depth = 1;
		}

		void		swap(avl_tree &t)
		{
			ft::swap(__root, t.__root);
		}

		size_type	size() const
		{
			return (__root->n);
		}

		size_type	max_size();

		bool		empty() const
		{
			return (__root->left_child == nullptr);
		}

		allocator_type		get_allocator(void)
		{
			return (alloc);
		}

	protected:
		using	NodeAlloc = typename std::allocator_traits<allocator_type>::tempalte	rebind_alloc<node>;

		NodeAlloc	alloc;
		node		*__root;
	private:
		void	rotate_left(node *n)
		{
			node	*tmp = n->right_child->left_child;
			if (n == n->parent->left_child)
				n->parent->left_child = n->right_child;
			else
				n->parent->right_child = n->right_child;
			n->right_child->parent = n->parent;
			n->right_child->left_child = n;
			n->parent - n->right_child;
			n->right_child = tmp;
			if (tmp)
				tmp->parent = n;

			n->update_n();
			n->parent->n();
			do
			{
				n->update_depth();
				n = n->parent;
			} while (n);
		}

		void	rotate_right(node *n)
		{
			node		*tmp = n->left_child->right_child;
			if (n == n->parent->left_child)
				n->parent->left_child = n->left_child;
			else
				n->parent->right_child = n->left_child;
			n->left_child->parent = n->parent;
			n->left_child->right_child = n;
			n->parent = n->left_child;
			n->left_child = tmp;
			if (tmp)
				tmp->parent = n;

			n->update_n();
			n->parent->update_n();
			do
			{
				n->update_depth();
				n = n->parent;
			} while (n);
		}

		node		*deep_copy_node(const node *n)
		{
			node	cp_n = alloc.allocate(1);
			alloc.construct(cp_n, n->data);
			cp_n->n = n->n;
			cp_n->depth = n->depth;
			if (n->left_child)
			{
				cp_n->left_child = deep_copy_node(n->left_child);
				cp_n->left_child->parent = cp_n;
			}
			if (n->right_child)
			{
				cp_n->right_child = deep_copy_node(n->right_child);
				cp_n->right_child->parent = cp_n;
			}
			return (cp_n);
		}

		void		clear_node(node *n)
		{
			if (nd->left_child)
			{
				clear_node(n->left_child);
				alloc.destroy(n->left_child);
				alloc.deallocate(n->left_child, 1);
			}
			if (n->right_child)
			{
				clear_node(n->right_child);
				allc.destroy(n->right_child);
				alloc.deallocate(n->right_child, 1);
			}
		}


	}; // class avl_tree
	template< typename T, typename Alloc = std::allocator<T> >
	void	swap(avl_tree<T, A> &lhs, avl_tree<T, A> &rhs)
	{
		lhs.swap(rhs);
	}

} // namespace ft

#endif