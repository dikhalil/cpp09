/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:15:21 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/08 16:33:51 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <exception>
#include <ctime>
#include <algorithm>

class PmergeMe
{
    private:
        std::vector<int> _vec;
        std::deque<int>  _deq;
        std::vector<int> _tempData;
        clock_t _start;
        clock_t _end;

       
        size_t binarySearchInsertPos(const std::vector<int> &v, int val) const;
        size_t binarySearchInsertPos(const std::deque<int> &d, int val) const;
        void insertPendingVector(std::vector<int> &mainChain, const std::vector<int> &pending);
        void insertPendingDeque(std::deque<int> &mainChain, const std::deque<int> &pending);
        void merg_insertion(std::vector<int> &arr);
        void merg_insertion(std::deque<int> &arr);
        std::vector<int> jacobsthalSequence(size_t n) const;
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        void parseData(const std::string &data);
        void fillVector();
        void fillDeque();
        void printData() const;
        void startTimer();
        void endTimer();
        double duration();
        int size() const;
        void sortVector();
        void sortDeque();
};