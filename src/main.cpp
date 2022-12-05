#include "parse.h"
#include "Sorter.h"
#include "display.h"
#include <iostream>


int main() {

    parse myParser("2021");

    /*
    myParser.getSchoolRankVector();
    std::string lookup = "AllPublicSchools";
    myParser.getGroupVector(lookup);
    */

    auto vec = myParser.getSchoolRankVector();

    /*
    for (auto &vecItem: vec) {
        std::cout << "School: " << vecItem.first << "  Score: " << vecItem.second << "\n";
    }
     */
    shellSort(vec);


    //display the opening screen and get the user choice
    int chosenInstitute = display::initialDisplay(vec);

    //group, score

    auto groupChosen = myParser.getGroupVector(myParser.groupConvert[chosenInstitute]);

    shellSort(groupChosen);


    return 0;
}