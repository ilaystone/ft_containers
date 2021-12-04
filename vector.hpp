/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 07:49:21 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/04 13:49:50 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include "iterator_traits.hpp"
#include <iostream>
#include <algorithm>
#include <memory>
#include <limits>

namespace ft
{
template < class T >
class vector_iterator
	: public __iterator<	typename iterator_traits<T *>::iterator_category,
							typename iterator_traits<T *>::value_type,
							typename iterator_traits<T *>::difference_type,
							typename iterator_traits<T *>::pointer,
							typename iterator_traits<T *>::reference >
{
public:
	typedef typename iterator_traits<T *>::difference_type difference_type;
	typedef typename iterator_traits<T *>::reference       reference;
	typedef typename iterator_traits<T *>::pointer         pointer;

	vector_iterator(void) : m_ptr() { return; };
	vector_iterator(pointer ptr) : m_ptr(ptr) { return; }

	reference			operator*(void) { return (*m_ptr); }
	vector_iterator		operator+(difference_type n) const { return (vector_iterator(m_ptr + n)); }
	vector_iterator		&operator++(void) { m_ptr++; return (*this); }
	vector_iterator		operator++(int) { vector_iterator tmp(*this); m_ptr++; return (tmp); }
	vector_iterator		&operator+=(difference_type n) { m_ptr += n; return (*this); }
	vector_iterator		operator-(difference_type n) const { return (vector_iterator(m_ptr - n)); }
	vector_iterator		&operator--(void) { m_ptr--; return (*this); }
	vector_iterator		operator--(int) { vector_iterator tmp(*this); m_ptr--; return (tmp); }
	vector_iterator		&operator-=(difference_type n) { m_ptr -= n; return (*this); }
	pointer				operator->(void) const { return (&(operator*())); }
	reference			operator[](difference_type n) { return (*(*this + n)); }
	bool				operator==(vector_iterator const &rhs) const { return (m_ptr == rhs.m_ptr); }
	bool				operator!=(vector_iterator const &rhs) const { return (m_ptr != rhs.m_ptr); }
	bool				operator<(vector_iterator const &rhs) const { return (m_ptr > rhs.m_ptr); }
	bool				operator<=(vector_iterator const &rhs) const { return (m_ptr >= rhs.m_ptr); }
	bool				operator>(vector_iterator const &rhs) const { return (m_ptr < rhs.m_ptr); }
	bool				operator>=(vector_iterator const &rhs) const { return (m_ptr <= rhs.m_ptr); }
protected:
	pointer			m_ptr;
};
template < class T, class Alloc=std::allocator<T> >
class vector
{
public:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef ft::vector_iterator<T>						iterator;
	typedef ft::vector_iterator<const T>				const_iterator;
	typedef ft::reverse_iterator<iterator>          	reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    	const_reverse_iterator;
	typedef typename allocator_type::size_type       	size_type;
    typedef typename allocator_type::difference_type 	difference_type;

	explicit vector(const allocator_type &alloc = allocator_type()) : __alloc(alloc), __capacity(0), __size(0) { return; }
	explicit vector(std::size_t n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
		__alloc(alloc),
		__capacity(0),
		__size(0)
	{
		
		return;
	}
	template < class InputIterator >
	vector(InputIterator first, input_iterator_tag last, const allocator_type &alloc = allocator_type())
	{
		return ;
	}
	vector(const vector &rhs)
	{
		*this = rhs;
		return ;
	}
	~vector(void) { return; }

	vector		&operator=(const vector &rhs)
	{
		return (*this);
	}

	iterator				begin(void) { return (vector_iterator<value_type>(__ptr)); }
	const_iterator			begin() const { return (vector_iterator<const value_type>(__ptr)); }
	iterator				end(void) { return (vector_iterator<value_type>(__ptr + __size)); }
	const_iterator			end(void) const { return (vector_iterator<const value_type>(__ptr + __size)); }
	reverse_iterator		rbegin(void) { return (reverse_iterator(end())); }
	const_reverse_iterator	rbegin(void) const { return (reverse_iterator(end())); }
	reverse_iterator		rend(void) { return (reverse_iterator(begin())); }
	const_reverse_iterator	rend(void) const { return (reverse_iterator(begin())); }
	size_type				size(void) const { return (this->__size); }
	size_type				max_size(void) const { return (std::min<size_type>(std::numeric_limits<difference_type>::max(), this->__alloc.max_size())); }
	void					resize(size_type n, value_type val = value_type()) { return; }
	size_type				capacity(void) const { return (__capacity); }
	bool					empty(void) const { return (__size == 0); }
	void					reserve(size_type n)
	reference				operator[](size_type n) { return (*(__ptr + n)); }
	const_reference			operator[](size_type n) { return (*(__ptr + n)); }
	reference				at(size_type n) { return (operator[](n)); }

	void					push_back(value_type const	&val)
	{
		__reserve_space__();
		__alloc.construct(__ptr + __size, val);
		__size += 1;
	}


protected:
	allocator_type		__alloc;
	pointer				__ptr;
	size_type			__capacity;
	size_type			__size;

private:
	void		__reserve_space__(void)
	{
		if (__capacity == 0)
		{
			__ptr = __alloc.allocate(1);
			__capacity = 1;
		}
		else if (__size == __capacity)
		{
			pointer new_space = __alloc.allocate(__capacity * 2);
			for (int i = 0; i < __size; i++)
			{
				__alloc.construct(new_space + i , __ptr[i]);
				__alloc.destroy(__ptr + i);
			}
			__alloc.deallocate(__ptr, __capacity);
			__ptr = new_space;
			__capacity *= 2;
		}
		return ;
	}
};
}

#endif