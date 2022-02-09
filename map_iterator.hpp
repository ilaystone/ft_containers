#ifndef __MAP_ITERATOR_HPP__
#define __MAP_ITERATOR_HPP__

#include "map_base.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	template <typename T, typename node_type>
	class map_iterator {
		protected:
			node_type						*_node;
			map_iterator(node_type *src);

		public:
			typedef T											value_type;
			typedef ptrdiff_t									difference_type;
			typedef value_type&									reference;
			typedef value_type*									pointer;
			typedef	ft::random_access_iterator_tag		iterator_category;
			map_iterator(void);
			map_iterator(const map_iterator &src);
			virtual ~map_iterator(void);
			map_iterator	&operator=(map_iterator const &rhs);

			template <class U> bool	operator==(const map_iterator<U, node_type> &rhs) const;
			template <class U> bool	operator!=(const map_iterator<U, node_type> &rhs) const;

			map_iterator		&operator++(void);
			map_iterator		operator++(int);
			map_iterator		&operator--(void);
			map_iterator		operator--(int);

			reference	operator*(void) const;
			pointer		operator->(void) const;

			operator map_iterator<const T, node_type>(void) const {
				return map_iterator<const T, node_type>(this->_node);
			}

			template <class, class, class, class>
			friend class map;

			template <class, class>
			friend class map_iterator;

	};

	template <typename T, typename node_type>
	map_iterator<T, node_type>::map_iterator(void) : _node(NULL) { return ; }

	template <typename T, typename node_type>
	map_iterator<T, node_type>::map_iterator(node_type *src) { this->_node = src; }

	template <typename T, typename node_type>
	map_iterator<T, node_type>::map_iterator(const map_iterator &src) { *this = src; }

	template <typename T, typename node_type>
	map_iterator<T, node_type>::~map_iterator(void) { return ; }

	template <typename T, typename node_type>
	map_iterator<T, node_type> &map_iterator<T, node_type>::operator=(const map_iterator &rhs) {
		if (this == &rhs)
			return (*this);
		this->_node = rhs._node;
		return (*this);
	}

	template <typename T, typename node_type> template <class U>
	bool	map_iterator<T, node_type>::operator==(const map_iterator<U, node_type> &rhs) const {
		return (this->_node == rhs._node);
	}

	template <typename T, typename node_type> template <class U>
	bool	map_iterator<T, node_type>::operator!=(const map_iterator<U, node_type> &rhs) const {
		return (this->_node != rhs._node);
	}

	template <typename T, typename node_type>
	map_iterator<T, node_type> &map_iterator<T, node_type>::operator++(void) {
		if (this->_node->right != NULL)
			this->_node = farLeft(this->_node->right);
		else
		{
			node_type	*child = this->_node;

			this->_node = this->_node->parent;
			while (this->_node && child == this->_node->right)
			{
				child = this->_node;
				this->_node = this->_node->parent;
			}
		}
		return (*this);
	}

	template <typename T, typename node_type>
	map_iterator<T, node_type> map_iterator<T, node_type>::operator++(int) {
		map_iterator	tmp(*this);
		++(*this);
		return (tmp);
	}

	template <typename T, typename node_type>
	map_iterator<T, node_type>& map_iterator<T, node_type>::operator--(void) {
		if (this->_node->left != NULL)
			this->_node = farRight(this->_node->left);
		else
		{
			node_type	*child = this->_node;

			this->_node = this->_node->parent;
			while (this->_node && child == this->_node->left)
			{
				child = this->_node;
				this->_node = this->_node->parent;
			}
		}
		return (*this);
	}

	template <typename T, typename node_type>
	map_iterator<T, node_type> map_iterator<T, node_type>::operator--(int) {
		map_iterator	tmp(*this);
		--(*this);
		return (tmp);
	}

	template <typename T, typename node_type>
	typename map_iterator<T, node_type>::reference map_iterator<T, node_type>::operator*(void) const {
		return (this->_node->data);
	}

	template <typename T, typename node_type>
	typename map_iterator<T, node_type>::pointer map_iterator<T, node_type>::operator->(void) const {
		return &this->operator*();
	}

}

#endif