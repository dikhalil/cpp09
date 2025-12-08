/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:43:41 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/06 17:19:03 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iomanip>

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
        double durationV;
        double durationD;

        for (int i = 1; i < argc; i++)
            pmerge.parseData(argv[i]);
        
        pmerge.fillVector();
        pmerge.fillDeque();
        
        std::cout << "Before: ";
        pmerge.printData();
        
        pmerge.startTimer();
        pmerge.sortVector();
        pmerge.endTimer();
        durationV = pmerge.duration();
        
        std::cout << "After: ";
        pmerge.printData();
        
        std::cout << "Time to process a range of " << pmerge.size() 
                  << " elements with std::vector : " 
                  << std::fixed << std::setprecision(5) << durationV << " us" << std::endl;
        
        pmerge.startTimer();
        pmerge.sortDeque();
        pmerge.endTimer();
        durationD = pmerge.duration();
        
        std::cout << "Time to process a range of " << pmerge.size() 
                  << " elements with std::deque : " 
                  << std::fixed << std::setprecision(5) << durationD << " us" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}