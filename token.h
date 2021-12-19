//
// Created by dmirty on 11.12.2021.
//

#ifndef LESSON24_TOKEN_H
#define LESSON24_TOKEN_H

#include "parserdata.h"

class Token {
public:
    virtual void update(ParserData &data) = 0;

    virtual  operator std::string() = 0;

    virtual ~Token() = default;

    void untilLeftPar(ParserData &pd);

    void opsWithHigherPrecedence(ParserData &pd, int precedence);
};


class Number : public Token {
public:

    explicit Number(int number);

    void update(ParserData &data) override;

    explicit operator std::string() override;

    ~Number() override = default;

private:
    int _number;

};

class Operation:public Token{
public:
    explicit Operation(std::string  op);

    explicit operator std::string() override;

    void update(ParserData &data) override;

    ~Operation() override = default;

private:
    std::string _op;
};

class LeftPar : public Token {
public:
    explicit operator std::string() override;

    void update(ParserData &data) override;

    ~LeftPar() override = default;

};

class RightPar : public Token {
public:
    explicit operator std::string() override;

    void update(ParserData &data) override;

    ~RightPar() override = default;

};



#endif //LESSON24_TOKEN_H
