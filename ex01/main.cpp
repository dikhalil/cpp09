/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:44:34 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/04 15:50:56 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
    RPN rpn;
    
    if (argc != 2)
    {
        std::cerr << "Error: Try " << argv[0] << " <RPN expression>" << std::endl;
        return 1;
    }
    try
    {
        rpn.operate(argv[1]);
        std::cout << "Result: " << rpn.getResult() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}