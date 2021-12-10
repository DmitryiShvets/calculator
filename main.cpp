#include <iostream>
#include <vector>
#include "parser.h"


int main() {

    std::cout << "Hello, World!" << std::endl;

    Parser parser{"..\\op"};
    parser.printMap();

    pars_tests(parser);

    std::cout << parser.parse("1 + 2 * 3") << " = " << parser.getResult() << std::endl;

    for (const std::string &inf: std::vector<std::string>{"2 + 3 * 4", "( 2 + 3 ) * 4", "( 5 + 7 + 3 ) / 5 - 1", "5 + ( 7 + 3 ) / 5 - 1", "15 / 5 - 1", "5 + 10 / 5 - 1", "10 * 10 * 10"}) {
        auto postfix = parser.parse(inf);
        std::cout << inf << " = " << postfix << " = " << parser.getResult() << std::endl;
    }
    return 0;
}
