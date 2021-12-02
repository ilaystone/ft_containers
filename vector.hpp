/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 07:49:21 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/02 20:44:57 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include "iterator_traits.hpp"
#include <memory>

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
};
}

#endif
