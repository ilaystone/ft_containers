/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:26:35 by ikhadem           #+#    #+#             */
/*   Updated: 2021/12/05 21:56:09 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>
#include <utility>

int main () {
	// constructors used in the same order as described above:
	// ft::vector<int> first;                                // empty vector of ints
	ft::vector<int> second (4,100);                       // four ints with value 100
	// ft::vector<int> third (second.begin(), second.end());  // iterating through second
	// ft::vector<int> fourth (third);                       // a copy of third
	ft::vector<int>::iterator		it;

	it = second.begin();
	while (it != second.end())
		std::cout << *it++ << ", ";
	std::cout << std::endl;
	// // the iterator constructor can also be used to construct from arrays:
	// int myints[] = {16,2,77,29};
	// ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	// std::cout << "The contents of fifth are:";
	// for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	// 	std::cout << ' ' << *it;
	// std::cout << '\n';

  return 0;
}