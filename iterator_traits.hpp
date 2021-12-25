/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:43:18 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/25 15:30:51 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__

#include <cstddef>  // For std::ptrdiff_t
namespace ft
{

struct input_iterator_tag  {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template< class Iterator >
struct iterator_traits
{
    typedef typename Iterator::difference_type		difference_type;
    typedef typename Iterator::value_type			value_type;
    typedef typename Iterator::pointer				pointer;
    typedef typename Iterator::reference			reference;
    typedef typename Iterator::iterator_category	iterator_category;
};

template< class T >
struct iterator_traits<T*>
{
    typedef std::ptrdiff_t				        difference_type;
    typedef T						        	value_type;
    typedef T*						        	pointer;
    typedef T&						        	reference;
    typedef random_access_iterator_tag	        iterator_category;
};

template< class T >
struct iterator_traits<const T*>
{
    typedef std::ptrdiff_t			        	difference_type;
    typedef T						        	value_type;
    typedef const T*					        pointer;
    typedef const T&					        reference;
    typedef random_access_iterator_tag          iterator_category;
};

template< class Category, class T, class Distance = std::ptrdiff_t,
         class Pointer = T*, class Reference = T& >
struct __iterator__
{
    typedef T         							value_type;
    typedef Distance  							difference_type;
    typedef Pointer   							pointer;
    typedef Reference 							reference;
    typedef Category  							iterator_category;
};


// __wrap_iterator__

template < class Iterator >
class __wrap_iterator__ :
	public __iterator__ <	typename iterator_traits<Iterator>::iterator_category,
                      		typename iterator_traits<Iterator>::value_type,
                    		typename iterator_traits<Iterator>::difference_type,
                    		typename iterator_traits<Iterator>::pointer,
                       		typename iterator_traits<Iterator>::reference >
{
public:
    typedef Iterator                                           			iterator_type;
	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type			value_type;
    typedef typename iterator_traits<iterator_type>::difference_type 	difference_type;
    typedef typename iterator_traits<iterator_type>::reference       	reference;
    typedef typename iterator_traits<iterator_type>::pointer         	pointer;

	__wrap_iterator__(void) : __base_ptr__() {}
	__wrap_iterator__(pointer ptr) : __base_ptr__(ptr) {}
	__wrap_iterator__(__wrap_iterator__ const &rhs) : __base_ptr__(rhs.base()) {}
	~__wrap_iterator__(void) { return; }

	__wrap_iterator__		operator=(__wrap_iterator__ const &rhs) { __base_ptr__ = rhs.base(); return (*this); }

	reference				operator*(void) { return (*__base_ptr__); }
	pointer					operator->(void) { return (&(*__base_ptr__)); }
	__wrap_iterator__		&operator++(void) { ++__base_ptr__; return (*this); }
	__wrap_iterator__		operator++(int) { __wrap_iterator__ tmp(*this); ++(*this); return (tmp); }
	__wrap_iterator__		operator+(difference_type n) const { return (__wrap_iterator__(__base_ptr__ + n)); }
	__wrap_iterator__		operator-(difference_type n) const { return (__wrap_iterator__(__base_ptr__ - n)); }
	bool					operator==(__wrap_iterator__ const &rhs) const { return (__base_ptr__ == rhs.__base_ptr__); }
	bool					operator!=(__wrap_iterator__ const &rhs) const { return (__base_ptr__ != rhs.__base_ptr__); }
	bool					operator>(__wrap_iterator__ const &rhs) const { return (__base_ptr__ > rhs.__base_ptr__); }
	bool					operator>=(__wrap_iterator__ const &rhs) const { return (__base_ptr__ >= rhs.__base_ptr__); }
	bool					operator<(__wrap_iterator__ const &rhs) const { return (__base_ptr__ < rhs.__base_ptr__); }
	bool					operator<=(__wrap_iterator__ const &rhs) const { return (__base_ptr__ <= rhs.__base_ptr__); }

	pointer					base(void) const { return (__base_ptr__); }

	template < class Iter1, class Iter2 >
	friend
	typename __wrap_iterator__<Iter1>::diffrence_type
	operator-(const __wrap_iterator__<Iter1> &, __wrap_iterator__<Iter2> &);
protected:
	pointer			__base_ptr__;
};

template < class Iter1, class Iter2 >
typename __wrap_iterator__<Iter1>::difference_type
operator-(const __wrap_iterator__<Iter1> &x, __wrap_iterator__<Iter2> &y)
{
	return (x.base() - y.base());
}

// end of __wrap_iterator__
// reverse_iterator
template < class Iterator >
class reverse_iterator
    : public __iterator__<	typename iterator_traits<Iterator>::iterator_category,
                      		typename iterator_traits<Iterator>::value_type,
                    		typename iterator_traits<Iterator>::difference_type,
                    		typename iterator_traits<Iterator>::pointer,
                       		typename iterator_traits<Iterator>::reference >
{
public:
    typedef Iterator                                            iterator_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::reference       reference;
    typedef typename iterator_traits<Iterator>::pointer         pointer;

    reverse_iterator(void) : current() { return; }
    reverse_iterator(Iterator const &iter) : current(iter) { return; }
	template < class __iter >
    reverse_iterator(reverse_iterator<__iter> const &rev_iter) : current(rev_iter.base()) { return; }
	template < class __iter >
    reverse_iterator				&operator=(reverse_iterator<__iter> const &rev_iter) { current = rev_iter.base(); return (*this); }
    ~reverse_iterator() {}

    Iterator                        base(void) const { return (this->current); }

    reference                       operator*(void) const { Iterator tmp = this->current; return (*--tmp); }
	reverse_iterator				operator+(difference_type n) const { return (reverse_iterator(current - n)); }
    reverse_iterator                &operator++(void) { --current; return (*this); }
    reverse_iterator                operator++(int) {reverse_iterator tmp(*this); --current; return (tmp); }
	reverse_iterator				&operator+=(difference_type n) { current -= n; return (*this); }
	reverse_iterator				operator-(difference_type n) const { return (reverse_iterator(current + n)); }
	reverse_iterator				&operator--(void) { ++current; return (*this); }
	reverse_iterator				operator--(int) {reverse_iterator tmp(*this); ++current; return (tmp); }
	reverse_iterator				&operator-=(difference_type n) {current += n; return (*this); }
	pointer							operator->(void) const { return (&(operator*())); }
	reference						operator[](difference_type n) { return (*(*this + n)); }
protected:
    iterator_type    current;
};

template < class Iterator >
bool	operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() == rhs.base());
}

template < class Iterator >
bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() != rhs.base());
}

template < class Iterator >
bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() < rhs.base());
}

template < class Iterator >
bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() <= rhs.base());
}

template < class Iterator >
bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() > rhs.base());
}

template < class Iterator >
bool	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() >= rhs.base());
}
// end of reveser Iterator
template < class InputIterator >
typename ft::iterator_traits<InputIterator>::difference_type		distance(InputIterator first, InputIterator last)
{
	typename ft::iterator_traits<InputIterator>::difference_type result = 0;
	while (first != last)
	{
		first++;
		result++;
	}
	return (result);
}

}

#endif