#include "parse.h"
#include <fstream>
#include <sstream>
#include <iostream>


parse::parse(std::string _year, const std::unordered_map<std::string, int> &gradeConversion, int grade) {
    year = _year;

    std::fstream fin;

    fin.open("../csvEMMATH_trunc.csv", std::ios::in); // open file, hardcoded position as of right now

    std::string line, temp, name, dataYear, assessment, group, proficient; // strings to hold all values

    fin >> temp; // get rid of first line


    while (fin >> temp) {
        std::stringstream stream(temp);

        std::getline(stream, name, ',');
        std::getline(stream, dataYear, ',');

        if (dataYear != year) continue; // only get values for given year
        //if (name == "AllPublicSchools") continue; // ignore these
        std::getline(stream, assessment, ',');
        if (grade != 0) {
            auto find = gradeConversion.find(assessment);
            if (find != gradeConversion.end() && find->second != grade)
                continue; // only get values for grade if specified
        }
        std::getline(stream, group, ',');
        std::getline(stream, proficient, ',');

        int groupInt = std::stoi(group);
        int profInt = std::stoi(proficient);

        insert(groupInt, name, assessment, profInt);
    }


}

void parse::insert(int &subgroup, std::string &institution, std::string &assessment, int &proficient) {
    auto location = dataSet.find(institution);

    dataObject newItem;
    newItem.proficient = proficient;
    newItem.test = assessment;
    newItem.group = subgroup;

    if (location != dataSet.end()) { // if institution exists in map
        location->second.first.push_back(newItem);
        location->second.second += proficient;
    } else { // if subgroup doesn't already exist
        // have to create new vector
        std::vector<dataObject> newVec;
        newVec.push_back(newItem);
        int newInt = proficient;
        auto myPair = std::make_pair(newVec, newInt);

        dataSet.insert(std::make_pair(institution, myPair));
    }
    totalItems++;
}

std::vector<std::pair<std::string, int>> parse::getSchoolRankVector() {
    auto myVec = std::vector<std::pair<std::string, int>>();

    for(auto &itr : dataSet) { // loop through each institution
        int avg = (itr.second.second/itr.second.first.size()); // calculate average
        myVec.emplace_back(itr.first, avg); // add to vector

        //std::cout << itr.first << " " << avg << "\n";
    }

    return myVec;
}

std::vector<std::pair<int, int>> parse::getGroupVector(std::string &school) {
    auto myVec = std::vector<std::pair<int, int>>();

    std::unordered_multimap<int, int> multimap;

    auto location = dataSet.find(school);
    if (location == dataSet.end()) return myVec; // return empty vector if location doesn't exist

    // this probably inefficient, fix later
    // putting into unordered multimap so averages for each group over different tests can be calculated

    for(auto & itr: location->second.first) {
        //myVec.emplace_back(itr.group, itr.proficient);
        multimap.insert(std::make_pair(itr.group, itr.proficient));
        //std::cout << "Group: " << itr.group << "  Score: " << itr.proficient << "\n";
    }

    //std::cout << "NEW AVERAGES\n\n";

    // now average group scores for the different tests
    for(auto &itr: multimap) {
        int count = multimap.count(itr.first);
        int repeat = count;
        int totalVal = 0;
        while (repeat > 1) {
            auto location = multimap.find(itr.first); // gives one location of the element
            totalVal += location->second; // store value of element
            multimap.erase(location);
            repeat--;
        }
        auto location = multimap.find(itr.first);
        location->second = (location->second + totalVal)/count;
    }

    for(auto &itr: multimap) { // looping through again just to be safe so not accessing bad memory
        myVec.emplace_back(itr.first,itr.second);
        //std::cout << "Group: " << groupConvert[itr.first] << "  Score: " << itr.second << "\n";
    }


    return myVec;

}

std::vector<std::pair<std::string, int>> parse::getSchoolByGroup(int group) {
    auto myVec = std::vector<std::pair<std::string, int>>();
    std::unordered_multimap<std::string, int> multimap;


    for (auto &itr: dataSet) {
        for(auto &vecItem: itr.second.first) {
            if (vecItem.group == group) { // look through every entry in every school for group
                multimap.insert(std::make_pair(itr.first, vecItem.proficient));
            }
        }
    }

    // now average together duplicates

    for(auto &itr: multimap) {
        int count = multimap.count(itr.first);
        int repeat = count;
        int totalVal = 0;
        while (repeat > 1) {
            auto location = multimap.find(itr.first); // gives one location of the element
            totalVal += location->second; // store value of element
            multimap.erase(location);
            repeat--;
        }
        auto location = multimap.find(itr.first);
        location->second = (location->second + totalVal)/count;
    }

    for (auto &itr: multimap) { // looping through again just to be safe so not accessing bad memory
        myVec.emplace_back(itr.first, itr.second);
        //std::cout << "Group: " << groupConvert[itr.first] << "  Score: " << itr.second << "\n";
    }


    return myVec;
}

bool parse::schoolLookup(std::string &school) {
    auto location = dataSet.find(school);
    if (location != dataSet.end()) return true;
    return false;
}

