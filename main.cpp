#include <iostream>
#include "parser.h"
#include "vector"
#include "rwlib.h"

int main() {


    Parser parser{"..//op"};
    parser.printMap();

    pars_tests(parser);
    Print();
    std::cout << parser.parse("1 + 2 * 3") << " = " << parser.getResult() << std::endl;

    std::vector<std::string> vector{" 3 * 4", "( 2 + 3 ) * 4", "( 5  + 3 ) / 5 - 1", "10 * 10 * 10"};
    for (auto inf:vector) {
        auto postfix = parser.parse(inf);
        Print(inf, " = ", postfix, " = ", parser.getResult(), '\n');
    }
}
