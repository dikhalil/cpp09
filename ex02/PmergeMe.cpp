/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:15:12 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/04 19:51:01 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vectorData = other._vectorData;
        _dequeData = other._dequeData;
    }
    return *this;
}

void PmergeMe::parseData(const std::string &data)
{
    std::stringstream ss(data);
    int num;

    ss >> num;
    if (ss.fail() || !ss.eof())
        throw std::runtime_error("Error: Invalid input data");
    if (num < 0)
        throw std::runtime_error("Error: Negative numbers are not allowed");
    _tempData.push_back(num);
}

void PmergeMe::fillVector()
{
    for (size_t i = 0; i < _tempData.size(); i++)
        _vectorData.push_back(_tempData[i]);
}

void PmergeMe::fillDeque()
{
   for (size_t i = 0; i < _tempData.size(); i++)
        _dequeData.push_back(_tempData[i]);
}

void PmergeMe::printData() const
{
    for (size_t i = 0; i < _vectorData.size(); i++)
    {
        std::cout << _vectorData[i];
        if (i != _vectorData.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::startTimer()
{
    _start = clock();
}

void PmergeMe::endTimer()
{
    _end = clock();
}

long long PmergeMe::duration()
{
    return static_cast<long long>(_end - _start) * 1000000 / CLOCKS_PER_SEC;
}

int PmergeMe::size() const
{
    return _vectorData.size();
}

void PmergeMe::sortVector()
{
	mergeInsertionSort(_vectorData);
}

void PmergeMe::sortDeque()
{
	mergeInsertionSort(_dequeData);
}
