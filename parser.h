//
// Created by Dmitry on 10.12.2021.
//

#ifndef LESSON24_PARSER_H
#define LESSON24_PARSER_H

#include <string>
#include "token.h"


class Parser {
public:
    explicit Parser(std::string path);

    void printMap();

    friend void pars_tests(Parser p);

    std::string parse(std::string const &input);

    int getResult();

private:
    int parseInt();

    Token *nextToken();

    int _result;
    ParserData _data;
    int _curPos;

    void calculate();

};


#endif //LESSON24_PARSER_H
