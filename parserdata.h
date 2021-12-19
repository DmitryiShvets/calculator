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


class TokenNode {
public:
    TokenNode(Token *data, TokenNode *left, TokenNode *right) : data(data), left(left), right(right) {}

    Token *data;
    TokenNode *left;
    TokenNode *right;
};

struct ParserData {
    std::string _input;
    std::stack<Token *> _tokenRaw;
    std::list<Token *> _tokenPostfix;
    std::map<std::string, int> _precedence;
};


struct AstData {
    std::stack<TokenNode*> _stack;
    std::list<Token *> _tokens;
};


#endif //LESSON24_PARSERDATA_H
