/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:13:24 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/04 01:46:43 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <fstream>
#include <cctype>
#include <cstdlib>

class BitcoinExchange
{
    private:
        std::string _inputFile;
        std::string _csvFile;
        std::map<std::string, float> _db;
        bool isValidDate(const std::string &line, const std::string &date);
        bool isValidValue(const std::string &line, const std::string &sValue, float &valuef);
    public:
        BitcoinExchange(const std::string &inputFile, const std::string &csvFile = "data.csv");
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        void loadDataFromCSV();
        void processInputFile();
};

std::string trim(const std::string &str);
bool isNumber(const std::string &str);
int daysInMonth(int month, int year);
