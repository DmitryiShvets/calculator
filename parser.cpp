//
// Created by Dmitry on 10.12.2021.
//

#include "parser.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include "rwlib.h"

template<typename T>
std::string toString(T const &list) {
    std::string res;
    for (auto x: list) {
        res += (std::string) *x;
    }
    return res;
}

Parser::Parser(std::string path) {
    _curPos = 0;
    std::ifstream stream{path, std::ios::in};

    for (std::string line; std::getline(stream, line);) {
        _data._precedence.insert({std::string{line[0]}, std::stoi(std::string{line[2]})});
    }
}

void Parser::printMap() {
    for (auto &x: _data._precedence) {
        Print(x.first, " ", x.second, '\n');
    }
}

/**
 * Парсит строку _input на числа начиная с текущей позиции _curPos
 * @return число которое было в строке
 */
int Parser::parseInt() {
    auto end = _data._input.find_first_not_of("0123456789", _curPos);
    std::string numStr = _data._input.substr(_curPos, end - _curPos);
    std::istringstream iss(numStr);
    int n;
    iss >> n;
    _curPos = end;
    return n;
}


Token *Parser::nextToken() {
    while (true) {
        auto ch = _data._input[_curPos];
        switch (ch) {
            case ' ':
                _curPos++;
                ch = _data._input[_curPos];
                continue;
            case '(':
                _curPos++;
                return new LeftPar;
            case ')':
                _curPos++;
                return new RightPar;
            case '0' ... '9' :
                return new Number(parseInt());
            default:
                auto key = std::string(&ch);
                if (_data._precedence.contains(key)) {
                    _curPos++;
                    return new Operation(key);
                } else throw std::invalid_argument("ERROR - INCORRECT INPUT");
        }

    }
}

std::string Parser::parse(const std::string &input) {
    _data._input = input;
    _data._tokenRaw.emplace(new LeftPar);
    _data._input += ")";
    _curPos = 0;
    while (!_data._tokenRaw.empty()) {
        auto tmp = nextToken();
        tmp->update(_data);
    }

    auto result = toString(_data._tokenPostfix);

    calculate();

    for (auto &x: _data._tokenPostfix) {
        delete x;
    }

    _data._tokenPostfix.clear();
    return result;
}

void pars_tests(Parser p) {
// * - + находятся в файле операторов
    p._data._input = " 35   * ( 4 - 11   ) + 27";

    Token *t = p.nextToken();
    assert((std::string) (*t) == "35");
    assert(dynamic_cast<Number *>(t));
    delete t;

    t = p.nextToken();
    assert((std::string) (*t) == "*");
    assert(dynamic_cast<Operation *>(t));
    delete t;

    t = p.nextToken();
    assert((std::string) (*t) == "(");
    assert(dynamic_cast<LeftPar *>(t));
    delete t;

    t = p.nextToken();
    assert((std::string) (*t) == "4");
    assert(dynamic_cast<Number *>(t));
    delete t;

    t = p.nextToken();
    assert((std::string) (*t) == "-");
    assert(dynamic_cast<Operation *>(t));
    delete t;

    t = p.nextToken();
    assert((std::string) (*t) == "11");
    assert(dynamic_cast<Number *>(t));
    delete t;

    t = p.nextToken();
    assert((std::string) (*t) == ")");
    assert(dynamic_cast<RightPar *>(t));
    delete t;
}

void Parser::calculate() {
    auto res = 0;
    int lhs;
    int rhs;
    std::stack<Token *> stack;
    for (auto x: _data._tokenPostfix) {
        auto ch = std::string(*x);
        switch (ch[0]) {
            case '0' ... '9' :
                stack.push(new Number(std::stoi(std::string(*x))));
                break;
            case '+':
                lhs = std::stoi(std::string(*stack.top()));
                stack.pop();
                rhs = std::stoi(std::string(*stack.top()));
                stack.pop();
                stack.push(new Number(lhs + rhs));
                break;
            case '-':
                lhs = std::stoi(std::string(*stack.top()));
                stack.pop();
                rhs = std::stoi(std::string(*stack.top()));
                stack.pop();
                stack.push(new Number(rhs - lhs));
                break;
            case '*':
                lhs = std::stoi(std::string(*stack.top()));
                stack.pop();
                rhs = std::stoi(std::string(*stack.top()));
                stack.pop();
                stack.push(new Number(lhs * rhs));
                break;
            case '/':
                lhs = std::stoi(std::string(*stack.top()));
                stack.pop();
                rhs = std::stoi(std::string(*stack.top()));
                stack.pop();
                stack.push(new Number(rhs / lhs));
                break;

        }
    }
    res = std::stoi(std::string(*stack.top()));

    _result = res;
}

int Parser::getResult() {
    return _result;
}


