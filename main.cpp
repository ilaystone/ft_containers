/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:26:35 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/10 21:20:50 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>
#include <utility>


int main ()
{
	ft::vector<int>		my_vector(100, 1);
	for (ft::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); it++)
		std::cout << *it;
	std::cout << std::endl << my_vector.capacity() << std::endl;
  	return 0;
}