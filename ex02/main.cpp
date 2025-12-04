/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:43:41 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/04 19:13:53 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: Try " << argv[0] << " <numbers>" << std::endl;
        return 1;
    }
    try
    {
        PmergeMe pmerge;

        for (int i = 1; i < argc; i++)
            pmerge.parseData(argv[i]);
        std::cout << "Before: ";
        pmerge.printData();
        pmerge.startTimer();
        pmerge.fillVector();
        pmerge.sortVector();
        pmerge.endTimer();
        std::cout << "After: ";
        pmerge.printData();
        std::cout << "Time to process a range of " << pmerge.size() << " elements with std::vector : " 
                  << pmerge.duration() << " us" << std::endl;
        pmerge.startTimer();
        pmerge.fillDeque();
        pmerge.sortDeque();
        pmerge.endTimer();
        std::cout << "Time to process a range of " << pmerge.size() << " elements with std::deque : " 
                  << pmerge.duration() << " us" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}