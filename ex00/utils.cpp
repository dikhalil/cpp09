/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 01:37:55 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/04 01:39:01 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


std::string trim(const std::string &str)
{
    size_t first;
    size_t last;

    first = str.find_first_not_of(" \t\n\r");
    last = str.find_last_not_of(" \t\n\r");
    if (first == std::string::npos || last == std::string::npos)
        return "";
    return str.substr(first, last - first + 1);
}

bool isNumber(const std::string &str)
{
    size_t i;
    bool point;
    
    i = 0;
    point = false;
    if (str.empty())
        return false;
    if (str[i] == '-' || str[i] == '+')
        i++;
    for (; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            if (point)
                return false;
            point = true;
        }
        else if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}

static bool isLeapYear(int year) 
{
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

int daysInMonth(int month, int year)
{
    if (month == 2)
        return isLeapYear(year) ? 29 : 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}

