/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:26:35 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/23 15:40:31 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>
#include <utility>
#include <string>

#ifndef TEST_NAME
# define TEST_NAME std
#endif

int main ()
{
	std::vector<int>				myvec(4, 100);
	std::vector<int>::iterator		it = myvec.begin();
	std::vector<int>::iterator		ite = myvec.end();

	std::cout << (ite + it) << "\n";
  	return 0;
}