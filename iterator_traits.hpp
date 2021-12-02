/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:43:18 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/02 12:35:16 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATORS_HPP__
#define __ITERATORS_HPP__

namespace FT
{

template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::difference_type		difference_type;
    typedef typename Iterator::value_type			value_type;
    typedef typename Iterator::pointer				pointer;
    typedef typename Iterator::reference			reference;
    typedef typename Iterator::iterator_category	iterator_category;
};

template<class T>
struct iterator_traits<T*>
{
    typedef std::ptrdiff_t				difference_type;
    typedef T							value_type;
    typedef T*							pointer;
    typedef T&							reference;
    typedef random_access_iterator_tag	iterator_category;
};

template<class T>
struct iterator_traits<const T*>
{
    typedef std::ptrdiff_t				difference_type;
    typedef T							value_type;
    typedef const T*					pointer;
    typedef const T&					reference;
    typedef random_access_iterator_tag	iterator_category;
};

}

#endif