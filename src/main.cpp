#include "parse.h"
#include <iostream>


int main() {

    parse myParser("2021");

    /*
    myParser.getSchoolRankVector();
    std::string lookup = "AllPublicSchools";
    myParser.getGroupVector(lookup);
    */

    auto vec = myParser.getSchoolByGroup(6);

    for (auto &vecItem: vec) {
        std::cout << "School: " << vecItem.first << "  Score: " << vecItem.second << "\n";
    }


    return 0;
}