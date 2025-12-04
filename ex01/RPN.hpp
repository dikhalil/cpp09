/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:32:49 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/04 15:48:22 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream> 
#include <stack>
#include <string>
#include <exception>

class RPN
{
    private:
        int _result; 
        std::stack<int> _stack;
    public:
        RPN();
        ~RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        void operate(const std::string &expression);
        int getResult() const;
    };