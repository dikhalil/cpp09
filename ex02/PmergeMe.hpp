/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:15:21 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/04 19:48:59 by dikhalil         ###   ########.fr       */
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
        std::vector<int> _vectorData;
        std::deque<int> _dequeData;
        std::vector<int> _tempData;
        clock_t _start;
        clock_t _end;

        void mergeInsertionSort(std::vector<int> &data);
        void mergeInsertionSort(std::deque<int> &data);
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
        long long duration();
        int size() const;
        void sortVector();
        void sortDeque();      
};