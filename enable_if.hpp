/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:23:06 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/06 18:08:58 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ENABLE_IF_HPP__
#define __ENABLE_IF_HPP__

namespace ft
{
template < bool B, class T = void >
struct enable_if_c
{
	typedef T	type;
};

template < class T >
struct enable_if_c<false, T> {};

template < class Cond, class T = void >
struct enable_if : public enable_if_c<Cond::value, T> {};

}

#endif