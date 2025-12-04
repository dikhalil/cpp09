/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:32:46 by dikhalil          #+#    #+#             */
/*   Updated: 2025/12/04 15:53:58 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() : _result(0) {}

RPN::~RPN() {}

RPN::RPN(const RPN &other)
{
    *this = other;
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

void RPN::operate(const std::string &expretion)
{
    int a;
    int b;
    int result;

    for (size_t i = 0; i < expretion.length(); i++)
    {
        if (expretion[i] == ' ')
            continue;
        else if (isdigit(expretion[i]))
            _stack.push(expretion[i] - '0');
        else if (expretion[i] == '+' || expretion[i] == '-' || expretion[i] == '*' || expretion[i] == '/')
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error: Not enough operands in expression");
            b = _stack.top();
            _stack.pop();
            a = _stack.top();
            _stack.pop();
            switch (expretion[i])
            {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0)
                        throw std::runtime_error("Error: Division by zero");
                    result = a / b;
                    break;
                default:
                    throw std::runtime_error("Error: Unknown operator");
            }                
            _stack.push(result);
        }    
        else
            throw std::runtime_error("Error");
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Error: Invalid RPN expression");
    result = _stack.top();
    _stack.pop();
    _result = result;
}

int RPN::getResult() const
{
    return _result;
}