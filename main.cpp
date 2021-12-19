#include <iostream>
#include "parser.h"
#include "vector"
#include "rwlib.h"

int main() {

    Print("Вывод текстового файла с приоритетом операции:",'\n');
    Parser parser{"..//op"};
    parser.printMap();
    Print();
    pars_tests(parser);
    Print("Тестовый пример: (1 + 2) * 3",'\n');

    std::cout << parser.parse("(1 + 2) * 3") << " = " << parser.getResult() << std::endl;

    Print();
    Print("Вывод дерева тестового примера: (1 + 2) * 3",'\n');
    parser.printTree();

    Print("Остальные тесты:",'\n');
    std::vector<std::string> vector{" 3 * 4", "( 2 + 3 ) * 4", "( 5  + 3 ) / 5 - 1", "10 * 10 * 10", "10-999"};
    for (auto inf: vector) {
        auto postfix = parser.parse(inf);
        Print(inf, " = ", postfix, " = ", parser.getResult(), '\n');
    }
}

//Вывод текстового файла с приоритетом операции:
//* 2
//+ 1
//- 1
// 2
//^ 3
//
//Тестовый пример: (1 + 2) * 3
//12+3* = 9
//
//Вывод дерева тестового примера: (1 + 2) * 3
//   3
//*
//      2
//   +
//      1
//Остальные тесты:
// 3 * 4 = 34* = 12
//( 2 + 3 ) * 4 = 23+4* = 20
//( 5  + 3 ) / 5 - 1 = 53+5/1- = 0
//10 * 10 * 10 = 1010*10* = 1000
//10-999 = 10999- = -989
