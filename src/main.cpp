#include "display.h"
#include "parse.h"
#include <iostream>



int main() {
    // define all conversions for groups

    static const auto *groupMap = new std::unordered_map<int, std::string>{
            {0,  "All Students"},
            {1,  "General Education Students"},
            {2,  "Students with Disabilities"},
            {3,  "American Indian or Alaska Native"},
            {4,  "Asian or Native hawaiian/Other Pacific Islander"},
            {5,  "Black or African American"},
            {6,  "Hispanic or Latino"},
            {7,  "White"},
            {8,  "Multiracial"},
            {9,  "Small Group"},
            {10, "Female"},
            {11, "Male"},
            {12, "English Language Learner"},
            {13, "Non-English Language Learner"},
            {14, "Economically Disadvantaged"},
            {15, "Not Economically Disadvantaged"},
            {16, "Migrant"},
            {17, "Not Migrant"},
            {18, "Homeless"},
            {19, "Not Homeless"},
            {20, "In Foster Care"},
            {21, "Not in Foster Care"},
            {22, "Parent in Armed Forces"},
            {23, "Parent not in Armed Forces"}
    };

    // define conversions for grades

    static const auto *gradeMap = new std::unordered_map<std::string, int>{
            {"MATH3", 3},
            {"MATH4", 4},
            {"MATH5", 5},
            {"MATH6", 6},
            {"MATH7", 7},
            {"MATH8", 8}
    };


    auto pair = display::initialDisplay();
    parse myParser(pair.first, *gradeMap, pair.second);
    cout << "Data loaded, " << myParser.totalItems << " elements\n";
    int choice = display::optionsDisplay();
    // 0. Sort all schools by overall performance
    // 1. Sort all schools by group performance
    // 2. Sort performance of groups at a school

    std::vector<std::pair<std::string, int>> rankVec;
    std::vector<std::pair<int, int>> schoolGroupVec;

    int group;
    string school;

    switch (choice) {
        case 0:
            rankVec = myParser.getSchoolRankVector();
            display::schoolRank(rankVec);
            break;
        case 1:
            group = display::groupSelect(*groupMap);
            rankVec = myParser.getSchoolByGroup(group);
            display::groupRank(rankVec);
            break;
        case 2:
            // doing input here so I can check if the selected school exists
            cout << "Enter School: ";
            cin >> school;
            while (!myParser.schoolLookup(school)) {
                cout << "Invalid selection\nTry again: ";
                cin >> school;
            }
            schoolGroupVec = myParser.getGroupVector(school);
            display::schoolGroups(schoolGroupVec, *groupMap);
            break;
        default:
            cout << "Error";
            return -1;
    }


    return 0;
}