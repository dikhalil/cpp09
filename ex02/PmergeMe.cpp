/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:15:12 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/08 17:01:19 by dikhalil         ###   ########.fr       */
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
        _vec = other._vec;
        _deq = other._deq;
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
        _vec.push_back(_tempData[i]);
}

void PmergeMe::fillDeque()
{
   for (size_t i = 0; i < _tempData.size(); i++)
        _deq.push_back(_tempData[i]);
}

void PmergeMe::printData() const
{
    for (size_t i = 0; i < _vec.size(); i++)
    {
        std::cout << _vec[i];
        if (i != _vec.size() - 1)
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

double PmergeMe::duration()
{
    return static_cast<double>(_end - _start) / CLOCKS_PER_SEC * 1000000.0;
}

int PmergeMe::size() const
{
    return _vec.size();
}


size_t PmergeMe::binarySearchInsertPos(const std::vector<int> &v, int val) const
{
    size_t l = 0;
    size_t r = v.size();
    size_t m;
    while (l < r)
    {
        m = l + (r - l) / 2;
        if (val < v[m])
            r = m;
        else
            l = m + 1;
    }
    return l;
}

size_t PmergeMe::binarySearchInsertPos(const std::deque<int> &d, int val) const
{
    size_t l = 0;
    size_t r = d.size();
    size_t m;
    while (l < r)
    {
        m = l + (r - l) / 2;
        if (val < d[m])
            r = m;
        else
            l = m + 1;
    }
    return l;
}

std::vector<int> PmergeMe::jacobsthalSequence(size_t n) const
{
    std::vector<int> seq;
    size_t t0;
    size_t t1;
    size_t tn;

    t0 = 0;
    t1 = 1;
    seq.push_back(1);
    while (t1 < n)
    {
        tn = t1 + 2 * t0;
        seq.push_back(tn);
        t0 = t1;
        t1 = tn;
    }
    return seq;
}

static int min(int a, int b)
{
    return (a < b) ? a : b;
}
void PmergeMe::insertPendingVector(std::vector<int> &mainChain, const std::vector<int> &pending)
{
    std::vector<int> seq = jacobsthalSequence(pending.size());
    int start, end;

    for (size_t i = 0; i < seq.size(); ++i)
    {
        start = (i == 0) ? 0 : seq[i - 1];
        end = min(seq[i], (int)pending.size());

        for (int j = end - 1; j >= start; --j)
        {
            size_t pos = binarySearchInsertPos(mainChain, pending[j]);
            if (pos == 0 || mainChain[pos - 1] != pending[j])
                mainChain.insert(mainChain.begin() + pos, pending[j]);
        }
    }
}

void PmergeMe::merg_insertion(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    std::vector<int> mainChain;
    std::vector<int> pending;
    
    for (size_t i = 0; i + 1 < arr.size(); i += 2)
    {
        if (arr[i] < arr[i + 1])
        {
            mainChain.push_back(arr[i + 1]);
            pending.push_back(arr[i]);
        }
        else
        {
            mainChain.push_back(arr[i]);
            pending.push_back(arr[i + 1]);
        }
    }
    if (arr.size() % 2 == 1)
        pending.push_back(arr[arr.size() - 1]);
    merg_insertion(mainChain);
    insertPendingVector(mainChain, pending);

    arr = mainChain;
}


void PmergeMe::insertPendingDeque(std::deque<int> &mainChain, const std::deque<int> &pending)
{
    std::vector<int> seq = jacobsthalSequence(pending.size());
    int start, end;

    for (size_t i = 0; i < seq.size(); ++i)
    {
        start = (i == 0) ? 0 : seq[i - 1];
        end = min(seq[i], (int)pending.size());

        for (int j = end - 1; j >= start; --j)
        {
            size_t pos = binarySearchInsertPos(mainChain, pending[j]);
            if (pos == 0 || mainChain[pos - 1] != pending[j])
                mainChain.insert(mainChain.begin() + pos, pending[j]);
        }
    }
}

void PmergeMe::merg_insertion(std::deque<int> &arr)
{
    if (arr.size() <= 1)
        return;

    std::deque<int> mainChain;
    std::deque<int> pending;
    
    for (size_t i = 0; i + 1 < arr.size(); i += 2)
    {
        if (arr[i] < arr[i + 1])
        {
            mainChain.push_back(arr[i + 1]);
            pending.push_back(arr[i]);
        }
        else
        {
            mainChain.push_back(arr[i]);
            pending.push_back(arr[i + 1]);
        }
    }
    if (arr.size() % 2 == 1)
        pending.push_back(arr[arr.size() - 1]);
    merg_insertion(mainChain);
    insertPendingDeque(mainChain, pending);
    arr = mainChain;
}

void PmergeMe::sortVector()
{
    merg_insertion(_vec);
}

void PmergeMe::sortDeque()
{
    merg_insertion(_deq);
}
