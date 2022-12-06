#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "mergesort.h"
#include "shellsort.h"


using namespace std;

class display {
public:
    static pair<string, int> initialDisplay();

    static int optionsDisplay();

    static int groupSelect(const std::unordered_map<int, std::string> &groupConversion);

    static int itemNumSelect();


    static void schoolRank(std::vector<std::pair<std::string, int>> &vec);

    static void groupRank(std::vector<std::pair<std::string, int>> &vec);

    static void
    schoolGroups(std::vector<std::pair<int, int>> &vec, const std::unordered_map<int, std::string> &groupConversion);
};