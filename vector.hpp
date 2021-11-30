/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 07:49:21 by ikhadem           #+#    #+#             */
/*   Updated: 2021/11/29 10:47:54 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <memory>
#include <vector>
#include <traits>
#include <iterator>

namespace ft
{
template < class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef Alloc											allocator_type;
	typedef typename std::allocator_traits<allocator_type>	__alloc_traits;
protected:
	typedef T												value_type;
	typedef value_type&										reference;
	typedef const value_type&								const_reference;
	typedef typename __alloc_traits::pointer				pointer;
	typedef typename __alloc_traits::const_pointer			const_pointer;
	typedef pointer											iterator;
	typedef const_pointer									const_iterator;

	pointer													__begin__;
	pointer													__end__;
	vector(void);
	~vector(void);
	vector	&operator=(vector const &rhs);

	iterator			begin(void)
	{
		return (iterator(value_type::begin(), this));
	}
	const_iterator		begin(void)
	{
		return (const_iterator(value_type::begin(), this));
	}
	void				push_back(const_reference __x)
	{
		
	}
};
} // namespace FT

#endif
