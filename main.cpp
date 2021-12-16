/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:26:35 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/16 11:51:43 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>
#include <utility>
#include <string>


int main ()
{
	ft::vector<int>					my_vector(3, 100);
	ft::vector<int>::iterator		it;

	it = my_vector.begin();
	it = my_vector.insert(it, 200);
	my_vector.insert(it, 2, 300);
	it = my_vector.begin();
	ft::vector<int> anothervector (2,400);
	my_vector.insert(it+2,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	my_vector.insert (my_vector.begin(), myarray, myarray+3);

	std::cout << "size: " << my_vector.size() << '\n';
	std::cout << "myvector contains:";
	for (it=my_vector.begin(); it < my_vector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

  	return 0;
}