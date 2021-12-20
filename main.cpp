/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:26:35 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/20 08:48:25 by ikhadem          ###   ########.fr       */
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
	TEST_NAME::vector<int>					my_vector(3, 100);
	TEST_NAME::vector<int>					copy_vec = my_vector;


	for (TEST_NAME::vector<int>::iterator it = copy_vec.begin(); it != copy_vec.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	std::cout << copy_vec.size() << ' ' << copy_vec.capacity() << std::endl;
  	return 0;
}