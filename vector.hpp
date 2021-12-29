/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 07:49:21 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/29 13:21:33 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iostream>

#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include <algorithm>
#include <memory>
#include <limits>
#include <stdexcept>

namespace ft
{

	template < class T, class Alloc=std::allocator<T> >
	class vector
	{
	public:
		/*****************
		** Member types **
		*****************/
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::__wrap_iterator<pointer>				iterator;
		typedef ft::__wrap_iterator<const_pointer>		const_iterator;
		typedef ft::reverse_iterator<iterator>          	reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>    	const_reverse_iterator;
		typedef typename allocator_type::size_type       	size_type;
		typedef typename allocator_type::difference_type 	difference_type;

		/*********************
		** Member functions **
		*********************/

		// default constructor
		explicit vector(const allocator_type &alloc = allocator_type()) :
			__alloc(alloc),
			__capacity(0),
			__size(0)
		{
			return;
		}
		// fill constructor
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
			__alloc(alloc),
			__capacity(n),
			__size(n)
		{
			this->__ptr = this->__alloc.allocate(this->__capacity);
			for (size_type i = 0; i < this->__size; i++)
				this->__alloc.construct(this->__ptr + i, val);
			return ;
		}
		// range constructor
		template < class InputIterator >
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = 0) :
			__alloc(alloc),
			__capacity(distance(first, last)),
			__size(distance(first, last))
		{
			this->__ptr = this->__alloc.allocate(this->__capacity);
			for (size_type i = 0; first != last; i++, first++)
				this->__alloc.construct(this->__ptr + i, *first);
			return ;
		}
		// copy constructor
		vector(const vector &rhs) :
			__alloc(rhs.__alloc),
			__capacity(0),
			__size(0)
		{
			*this = rhs;
			return ;
		}
		// destructor
		~vector(void)
		{
			if (this->__capacity == 0)
				return ;
			this->clear();
			this->__alloc.deallocate(this->__ptr, this->__capacity);
			return ;
		}
		// assignment operator
		vector		&operator=(const vector &rhs)
		{
			this->~vector();
			this->__capacity = rhs.capacity();
			this->__size = rhs.size();
			this->__ptr = this->__alloc.allocate(this->__capacity);
			for (difference_type i = 0; i < distance(rhs.begin(), rhs.end()); i++)
				this->__alloc.construct(this->__ptr + i, *(rhs.begin() + i));
			return (*this);
		}

		/**************
		** Iterators **
		**************/

		iterator				begin(void)
		{
			return (__wrap_iterator<pointer>(__ptr));
		}
		const_iterator			begin() const
		{
			return (__wrap_iterator<const_pointer>(__ptr));
		}
		iterator				end(void)
		{
			return (__wrap_iterator<pointer>(__ptr + __size));
		}
		const_iterator			end(void) const
		{
			return (__wrap_iterator<const_pointer>(__ptr + __size));
		}
		reverse_iterator		rbegin(void)
		{
			return (reverse_iterator(end()));
		}
		const_reverse_iterator	rbegin(void) const
		{
			return (reverse_iterator(end()));
		}
		reverse_iterator		rend(void)
		{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator	rend(void) const
		{
			return (reverse_iterator(begin()));
		}

		/*************
		** Capacity **
		*************/

		size_type				size(void) const
		{
			return (this->__size);
		}
		size_type				max_size(void) const
		{
			return (std::min<size_type>(std::numeric_limits<difference_type>::max(), this->__alloc.max_size()));
		}
		void					resize(size_type n, value_type val = value_type())
		{
			if (n > this->__capacity)
				this->reserve(this->__capacity * 2);
			while (n < this->__size)
				this->pop_back();
			while (n > this->__size)
				this->push_back(val);
			return ;
		}
		size_type				capacity(void) const
		{
			return (this->__capacity);
		}
		bool					empty(void) const
		{
			return (__size == 0);
		}
		void					reserve(size_type n)
		{
			if (n > this->__capacity)
			{
				pointer		ptr;
				size_type	i;

				ptr = this->__alloc.allocate(n);
				i = 0;
				for (iterator it = this->begin(); it != this->end(); it++, i++)
					this->__alloc.construct(ptr + i, *it);

				this->~vector();
				this->__ptr = ptr;
				this->__capacity = n;
				this->__size = i;
			}
		}

		/*******************
		** Element access **
		*******************/

		reference				operator[](size_type n)
		{
			return (*(this->begin() + n));
		}
		const_reference			operator[](size_type n) const
		{
			return (*(this->begin() + n));
		}
		reference				at(size_type n)
		{
			if (n < 0 || n > this->__size)
				throw (std::out_of_range("ft::vector"));
			return (operator[](n));
		}
		const_reference			at(size_type n) const
		{
			if (n < 0 || n > this->__size)
				throw std::out_of_range("ft::vector");
			return (operator[](n));
		}
		reference				front(void)
		{
			return (operator[](0));
		}
		const_reference			front(void) const
		{
			return (operator[](0));
		}
		reference				back(void)
		{
			return (operator[](this->__size - 1));
		}
		const_reference			back(void) const
		{
			return (operator[](this->__size - 1));
		}

		/**************
		** Modifiers **
		**************/

		template < class InputIterator >
		void					assign(InputIterator first, InputIterator last,
			typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = 0)
		{
			this->clear();
			for (iterator it = first; it != last; it++)
				this->push_back(*it);
			return ;
		}
		void 					assign (size_type n, const value_type& val)
		{
			this->clear();
			for (; n != 0; n--)
				this->push_back(val);
			return ;
		}
		void					push_back(value_type const	&val)
		{
			if (this->__capacity == 0)
				this->reserve(1);
			else if (this->__size == this->__capacity)
				this->reserve(this->__capacity * 2);
			this->__alloc.construct(&(*(this->end())), val);
			this->__size++;
		}
		void					pop_back(void)
		{
			if (this->__size <= 0)
				return ;
			this->__size--;
			this->__alloc.destroy(&(*this->end()));
		}
		iterator				insert(iterator position, const value_type &val)
		{
			difference_type			dist = distance(this->begin(), position);

			this->insert(position, 1, val);
			return (iterator(&this->__ptr[dist]));
		}
		void					insert(iterator position, size_type n, const value_type &val)
		{
			difference_type			dist = distance(this->begin(), position);
			size_type				old_size = this->__size;
			iterator				new_pos;

			if (this->__size + n > this->__capacity)
				this->reserve(this->__capacity + n);
			this->__size = old_size;
			new_pos  = iterator((&this->__ptr[dist]));
			if (new_pos != this->end())
			{
				for (iterator ite = this->end() - 1; ite + 1 != new_pos; ite--)
				{
					this->__alloc.construct(&(*(ite + n)), *ite);
					this->__alloc.destroy(&(*ite));
				}
			}
			for (size_type i = 0; i < n; i++)
				this->__alloc.construct(&(*new_pos++), val);
			this->__size += n;
		}
		template < class InputIterator >
		void					insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = 0)
		{
			difference_type			dist = distance(this->begin(), position);
			size_type				n = distance(first, last);
			size_type				old_size = this->__size;
			iterator				new_pos;

			if (this->__size + n > this->__capacity)
				this->reserve(this->__capacity + n);
			this->__size = old_size;
			new_pos  = iterator((&this->__ptr[dist]));
			if (new_pos != this->end())
			{
				for (iterator ite = this->end() - 1; ite + 1 != new_pos; ite--)
				{
					this->__alloc.construct(&(*(ite + n)), *ite);
					this->__alloc.destroy(&(*ite));
				}
			}
			for (size_type i = 0; i < n; i++)
				this->__alloc.construct(&(*new_pos++), *first++);
			this->__size += n;
		}
		// iterator				erase(iterator position)
		// {
			
		// }
		void					clear(void)
		{
			for (iterator it = this->begin(); it != this->end(); it++)
				this->__alloc.destroy(&(*it));
			this->__size = 0;
			return ;
		}
		// return a copy of __alloc
		allocator_type get_allocator() const
		{
			return (allocator_type(this->__alloc));
		}

	protected:
		allocator_type		__alloc;
		pointer				__ptr;
		size_type			__capacity;
		size_type			__size;

	};

}

#endif