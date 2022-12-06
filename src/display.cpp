#include "display.h"
#include <iostream>

pair<string, int> display::initialDisplay() {
    string givenYear;
    int grade = 0;

    cout
            << "Welcome to our Final Project for COP3530\nThis tool allows for the evaluation of New York schools through standardized tests.\nResults are grouped by demographic for analysis of potential disparities in education.\nFurthermore, the efficiency of merge and shell sort is analyzed for a large dataset.\nGroup Members: Nicole Lambert, Tanner Garcia, Zachary Miller\n\n";
    cout << "Enter the year for which you wish to analyze\nValid options are 2021 or 2022\n";
    cin >> givenYear;

    while (givenYear != "2021" && givenYear != "2022") {
        cout << "\nInvalid Selection\nTry again: ";
        cin >> givenYear;
    }

    cout << "\nEnter the grade level, or enter '0' for all levels: ";
    cin >> grade;
    while (grade > 8 || (grade < 3 && grade != 0)) {
        cout << "\nInvalid Selection\nTry again: ";
        cin >> grade;
    }


    cout << "Loading selected data\n";

    return make_pair(givenYear, grade);

}

int display::optionsDisplay() {
    int option;

    cout
            << "Select an option: \n0. Sort all schools by overall performance\n1. Sort all schools by group performance\n2. Sort performance of groups at a school\n";
    cin >> option;
    while (option < 0 || option > 2) {
        cout << "\nInvalid Selection\nTry again: ";
        cin >> option;
    }

    return option;
}

int display::groupSelect(const std::unordered_map<int, std::string> &groupConversion) {
    cout << "Select a group by typing its code, or type o to see options\n";
    string _selected;
    int selected = 0;

    cin >> _selected;
    if (_selected != "o" && _selected != "O") {
        int tempSelected = stoi(_selected);
        if (tempSelected > -1 && tempSelected < 24) {
            selected = tempSelected;
        }
    } else {
        for (int i = 0; i < groupConversion.size(); i++) {
            cout << i << ". " << groupConversion.at(i) << "\n";
        }
        cin >> _selected;
        int tempSelected = stoi(_selected);
        if (tempSelected > -1 && tempSelected < 24) {
            selected = tempSelected;
        }
    }

    return selected;
}


int display::itemNumSelect() {
    int items = 0;
    cout << "Enter max number of items to display: \n";
    cin >> items;

    while (items < 1) {
        cout << "Invalid selection\nTry again: \n";
        cin >> items;
    }
    return items;
}

void display::schoolRank(std::vector<std::pair<std::string, int>> &vec) {
    int items = itemNumSelect();
    auto copy = vec;

    // first shell sort
    long long int shellTime = shellSort(vec);

    // then merge sort
    long long int mergeTime = mergeSort(copy, 0, copy.size() - 1);

    cout << "\n\nSorted Order: \n";
    cout << "School Name      Percent Proficient\n\n";

    for (int i = 0; i < items && i < vec.size(); i++) {
        cout << i << ". " << vec[i].first << " " << vec[i].second << "\n";
    }

    cout << "Shell sort took " << shellTime << " microseconds\n";

    cout << "Merge sort took " << mergeTime << " microseconds\n";
    if (shellTime < mergeTime) {
        cout << "Shell ";
    } else cout << "Merge ";
    cout << "sort performed faster\n";
}

void display::groupRank(vector<std::pair<std::string, int>> &vec) {
    int items = itemNumSelect();
    auto copy = vec;

    // first shell sort
    long long int shellTime = shellSort(vec);

    // then merge sort
    long long int mergeTime = mergeSort(copy, 0, copy.size() - 1);

    cout << "\n\nSorted Order: \n";
    cout << "School Name      Percent Proficient\n\n";

    for (int i = 0; i < items && i < vec.size(); i++) {
        cout << i << ". " << vec[i].first << " " << vec[i].second << "\n";
    }

    cout << "Shell sort took " << shellTime << " microseconds\n";

    cout << "Merge sort took " << mergeTime << " microseconds\n";
    if (shellTime < mergeTime) {
        cout << "Shell ";
    } else cout << "Merge ";
    cout << "sort performed faster\n";
}

void display::schoolGroups(std::vector<std::pair<int, int>> &vec,
                           const std::unordered_map<int, std::string> &groupConversion) {

    auto copy = vec;

    // first shell sort
    long long int shellTime = shellSort(vec);

    // then merge sort
    long long int mergeTime = mergeSort(copy, 0, copy.size() - 1);

    cout << "\n\nSorted Order: \n";
    cout << "Group Name      Percent Proficient\n\n";

    for (int i = 0; i < vec.size(); i++) {
        cout << i << ". " << groupConversion.at(vec[i].first) << " " << vec[i].second << "\n";
    }

    cout << "Shell sort took " << shellTime << " microseconds\n";

    cout << "Merge sort took " << mergeTime << " microseconds\n";
    if (shellTime < mergeTime) {
        cout << "Shell ";
    } else cout << "Merge ";
    cout << "sort performed faster\n";


}