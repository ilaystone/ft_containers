/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:26:35 by ikhadem           #+#    #+#             */
/*   Updated: 2021/11/26 10:30:48 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cmath>

int		main(void)
{
float	a;
	a = 2.0;
	a *= a;
	a *= a;;
	a = std::sqrtf(a) * sqrtf(a);
	std::cout << a;
	return (0);
}