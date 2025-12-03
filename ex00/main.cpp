/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:07:42 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/04 01:46:58 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        if (argc < 2)
            std::cout << "Error: Could not open file." << std::endl;
        else
        std::cout << "Error: to many argumants." << std::endl;
        return 1;
    }
    std::string inputFile = argv[1];
    std::string csvFile = "data.csv";
    try 
    {
        BitcoinExchange btcExchange(inputFile, csvFile);
        btcExchange.loadDataFromCSV();
        btcExchange.processInputFile();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}