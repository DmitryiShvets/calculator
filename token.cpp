//
// Created by dmirty on 11.12.2021.
//

#include "token.h"


void Number::update(ParserData &data) {
    data._tokenPostfix.push_back(this);
}

Number::operator std::string() {
    return std::string{std::to_string(_number)};
}


Number::Number(int number) : _number(number) {}

Operation::Operation(std::string op) : _op(std::move(op)) {}


Operation::operator std::string() {
    return std::string{_op};
}

void Operation::update(ParserData &data) {
    opsWithHigherPrecedence(data, data._precedence[_op]);
    data._tokenRaw.push(this);
}


LeftPar::operator std::string() {
    return "(";
}

void LeftPar::update(ParserData &data) {
    data._tokenRaw.push(this);
}


RightPar::operator std::string() {
    return ")";
}

void RightPar::update(ParserData &data) {
    untilLeftPar(data);
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
    while (true) {
        Token *tmp = pd._tokenRaw.top();
        if (pd._precedence[std::string(*tmp)] >= precedence) {
            pd._tokenPostfix.push_back(tmp);
            pd._tokenRaw.pop();
        } else return;
    }
}
