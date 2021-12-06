/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:08:37 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/06 18:41:59 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __IS_INTEGRAL_HPP__
#define __IS_INTEGRAL_HPP__

namespace ft
{
struct false_type
{
	static bool value = false;
};

struct true_type
{
	static bool value = true;
};

template < class T > struct is_integral : public false_type {};
template < class T > struct is_integral<const T> : public is_integral<T> {};
template<> struct is_integral<unsigned char> : public true_type {};
template<> struct is_integral<unsigned short> : public true_type{};
template<> struct is_integral<unsigned int> : public true_type{};
template<> struct is_integral<unsigned long> : public true_type{};
template<> struct is_integral<signed char> : public true_type{};
template<> struct is_integral<short> : public true_type{};
template<> struct is_integral<int> : public true_type{};
template<> struct is_integral<long> : public true_type{};
template<> struct is_integral<char> : public true_type{};
template<> struct is_integral<bool> : public true_type{};

}

#endif