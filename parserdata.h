//
// Created by dmirty on 11.12.2021.
//

#ifndef LESSON24_PARSERDATA_H
#define LESSON24_PARSERDATA_H


#include <stack>
#include <list>
#include <map>
#include <string>
#include <numeric>
class Token;

struct ParserData {
    std::string _input;
    std::stack<Token *> _tokenRaw;
    std::list<Token *> _tokenPostfix;
    std::map<std::string, int> _precedence;
};


#endif //LESSON24_PARSERDATA_H
