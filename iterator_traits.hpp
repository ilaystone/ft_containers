/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:43:18 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/02 20:34:30 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATORS_HPP__
#define __ITERATORS_HPP__

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
struct __iterator
{
    typedef T         							value_type;
    typedef Distance  							difference_type;
    typedef Pointer   							pointer;
    typedef Reference 							reference;
    typedef Category  							iterator_category;
};

template < class Iterator >
class reverse_iterator
    : public __iterator< typename iterator_traits<Iterator>::iterator_category,
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

}

#endif