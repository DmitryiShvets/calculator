//
// Created by dmirty on 11.12.2021.
//

#include <stdexcept>
#include "token.h"


void Number::update(ParserData &data) {
    data._tokenPostfix.push_back(this);
}

Number::operator std::string() {
    return std::string{std::to_string(_number)};
}


Number::Number(int number) : _number(number) {}

void Number::update(AstData &ast) {
    ast._stack.emplace(new TokenNode(this, nullptr, nullptr));
}

Operation::Operation(std::string op) : _op(std::move(op)) {}


Operation::operator std::string() {
    return std::string{_op};
}

void Operation::update(ParserData &data) {
    opsWithHigherPrecedence(data, data._precedence[_op]);
    data._tokenRaw.push(this);
}

void Operation::update(AstData &ast) {
    auto rhs = ast._stack.top();
    ast._stack.pop();
    auto lhs = ast._stack.top();
    ast._stack.pop();
    auto *tokenNode = new TokenNode(this, lhs, rhs);
    ast._stack.emplace(tokenNode);
}


LeftPar::operator std::string() {
    return "(";
}

void LeftPar::update(ParserData &data) {
    data._tokenRaw.push(this);
}

void LeftPar::update(AstData &ast) {
    throw std::runtime_error("логическая ошибка");
}


RightPar::operator std::string() {
    return ")";
}

void RightPar::update(ParserData &data) {
    untilLeftPar(data);
}

void RightPar::update(AstData &ast) {
    throw std::runtime_error("логическая ошибка");
}

void Token::untilLeftPar(ParserData &pd) {
    while (true) {
        Token *t = pd._tokenRaw.top();
        pd._tokenRaw.pop();
        if (std::string(*t) == "(")
            return;
        pd._tokenPostfix.push_back(t);
    }
}

void Token::opsWithHigherPrecedence(ParserData &pd, int precedence) {
    Token *tmp = pd._tokenRaw.top();
    if (pd._precedence[std::string(*tmp)] >= precedence) {
        pd._tokenPostfix.push_back(tmp);
        pd._tokenRaw.pop();
    } else return;
}
