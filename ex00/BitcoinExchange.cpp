/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:14:44 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/08 18:25:50 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &inputFile, const std::string &csvFile) 
    : _inputFile(inputFile), _csvFile(csvFile) {}
    
BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        _inputFile = other._inputFile;
        _csvFile = other._csvFile;  
        _db = other._db;
    }
    return *this;
}


void BitcoinExchange::processCsvFile()
{
    std::ifstream file(_csvFile.c_str());
    std::string line;
    std::string date;
    bool header;
    size_t comma;
   
    header = false;
    if (!file.is_open())
        throw std::runtime_error("Error: Could not open file.");
    if (file.peek() == std::ifstream::traits_type::eof())
        throw std::runtime_error("CSV file is empty.");
    while (std::getline(file, line))
    {
        std::string noSpaces;
        
        line = trim(line);
        if (line.empty())
            continue;
        comma = line.find(',');
        if (comma == std::string::npos || comma == 0 || comma == line.length() - 1)
            throw std::runtime_error("Invalid CSV format.");
        if (!header)
        {
            std::string left;
            std::string right;
            left = trim(line.substr(0, comma));
            right = trim(line.substr(comma + 1));
            if (left == "date" && right == "exchange_rate")
            {
                header = true;
                continue;
            }
        }
        if (!header)
            throw std::runtime_error("CSV header missing.");
        date = trim(line.substr(0, comma));
        if (!isValidDate(line, date) 
            || !isNumber(trim(line.substr(comma + 1))))
            throw std::runtime_error("Invalid data in CSV file.");
    }
    file.close();
}

void BitcoinExchange::loadDataFromCSV()
{
    std::ifstream file(_csvFile.c_str());
    std::string line;
    std::string data;
    float value;
    size_t comma;
    
    processCsvFile();
    if (!file.is_open())
        throw std::runtime_error("Error: Could not open CSV file");
    while (std::getline(file, line))
    {
        if (line.empty() || line == "date,exchange_rate" )
            continue;
        comma = line.find(',');
        if (comma == std::string::npos)
            throw std::runtime_error("Invalid format in CSV file");
        data = trim(line.substr(0, comma));
        value = std::atof(trim(line.substr(comma + 1)).c_str());
        _db[data] = value;
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string &line, const std::string &date)
{
    int year;
    int month;
    int day;
    
    if (date.length() != 10 || date[4] != '-' || date[7] != '-'
        || date[0] == '+' || date[0] == '-')
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return false;
    }
    if (!isNumber(date.substr(0, 4)) 
        || !isNumber(date.substr(5, 2)) 
        || !isNumber(date.substr(8, 2)))
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return false;
    }
    year = atoi(date.substr(0, 4).c_str());
    month = atoi(date.substr(5, 2).c_str());
    day = atoi(date.substr(8, 2).c_str());
    if (year < 1000 || year > 9999 || month < 1 || month > 12 
        || day < 1 || day > daysInMonth(month, year))
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return false;
    }
    return true;
}

bool BitcoinExchange::isValidValue(const std::string &line, const std::string &value, float &amount)
{
    if (!isNumber(value))
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return false;
    }
    amount = atof((trim(value).c_str()));
    if (amount < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return false;
    }
    if (amount > 1000)
    {
        std::cout << "Error: too large number." << std::endl;
        return false;
    }
    return true;
}
void BitcoinExchange::processInputFile()
{
    std::ifstream file(_inputFile.c_str());
    std::string line;
    std::string date;
    float amount;
    bool header;
    size_t pipe;
   
    header = false;
    if (!file.is_open())
        throw std::runtime_error("Error: Could not open file.");
    if (file.peek() == std::ifstream::traits_type::eof())
    {
        std::cout << "Error: file is empty." << std::endl;
        return;
    }
    while (std::getline(file, line))
    {
        std::string noSpaces;
        
        line = trim(line);
        if (line.empty())
            continue;
        pipe = line.find('|');
        if (pipe == std::string::npos || pipe == 0 || pipe == line.length() - 1)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (!header)
        {
            std::string left;
            std::string right;
            left = trim(line.substr(0, pipe));
            right = trim(line.substr(pipe + 1));
            if (left == "date" && right == "value")
            {
                header = true;
                continue;
            }
        }
        if (!header)
        {
            std::cout << "Error: header missing." << std::endl;
            header = true;
        }
        date = trim(line.substr(0, pipe));
        if (!isValidDate(line, date) 
            || !isValidValue(line, trim(line.substr(pipe + 1)), amount))
            continue;
        std::map<std::string, float>::iterator it = _db.lower_bound(date);
        if (it == _db.end() || it->first != date)
        {
            if (it == _db.begin())
            {
                std::cout << "Error: no exchange rate available for date " << date << std::endl;
                continue;
            }
            --it;
        }
        std::cout << date << " => " << amount << " = " << amount * it->second << std::endl;
    }
    file.close();
}

