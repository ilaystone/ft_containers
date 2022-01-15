/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:41:06 by ikhadem           #+#    #+#             */
/*   Updated: 2022/01/14 15:06:44 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TYPE_TRAITS_HPP__
#define __TYPE_TRAITS_HPP__

namespace ft
{

	template <class T, T v>
	struct integral_constant {
	typedef T value_type;
	typedef integral_constant<T,v> type;
		enum {
			value = v
		};
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template < class T > struct is_integral : public false_type {};
	template < class T > struct is_integral<const T> : public is_integral<T> {};
	template<> struct is_integral<unsigned char> : public true_type {};
	template<> struct is_integral<unsigned short> : public true_type {};
	template<> struct is_integral<unsigned int> : public true_type {};
	template<> struct is_integral<unsigned long> : public true_type {};
	template<> struct is_integral<signed char> : public true_type {};
	template<> struct is_integral<short> : public true_type {};
	template<> struct is_integral<int> : public true_type {};
	template<> struct is_integral<long> : public true_type {};
	template<> struct is_integral<char> : public true_type {};
	template<> struct is_integral<bool> : public true_type {};
	template < bool B, class T = void >
	struct enable_if {};

	template < class T >
	struct enable_if< true, T>
	{
		typedef T	type;
	};

}

#endif