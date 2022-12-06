#pragma once
#include <unordered_map>
#include <vector>
#include <string>


class parse {
private:
    std::string year;
    struct dataObject {
        int group;
        std::string test;
        int proficient;
    };
    // string is the school, vector contains group and percent proficient, int is sum of the proficients
    std::unordered_map<std::string, std::pair<std::vector<dataObject>, int>> dataSet;

    void insert(int &subgroup, std::string &institution, std::string &assessment, int &proficient);


public:
    parse(std::string _year, const std::unordered_map<std::string, int> &gradeConversion,
          int grade = 0); // year is 2021 or 2022 data, grade can be 0 for all or any int 3-8
    std::vector<std::pair<std::string, int>>
    getSchoolByGroup(int group); // returns the proficiency of a selected group at every school
    std::vector<std::pair<std::string, int>> getSchoolRankVector(); // returns vector of school, average proficiency
    std::vector<std::pair<int, int>>
    getGroupVector(std::string &school); // returns all groups at a school (first) and their average scores (second)

    bool schoolLookup(std::string &school);

    int totalItems = 0;
};
