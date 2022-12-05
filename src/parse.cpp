#include "parse.h"
#include <fstream>
#include <sstream>
#include <iostream>


parse::parse(std::string _year, int grade) {
    year = _year;
    // define all conversions for groups
    groupConvert[0] = "All Students";
    groupConvert[1] = "General Education Students";
    groupConvert[2] = "Students with Disabilities";
    groupConvert[3] = "Students with Disabilities";
    groupConvert[4] = "Asian or Native hawaiian/Other Pacific Islander";
    groupConvert[5] = "Black or African American";
    groupConvert[6] = "Hispanic or Latino";
    groupConvert[7] = "White";
    groupConvert[8] = "Multiracial";
    groupConvert[9] = "Small Group";
    groupConvert[10] = "Female";
    groupConvert[11] = "Male";
    groupConvert[12] = "English Language Learner";
    groupConvert[13] = "Non-English Language Leaner";
    groupConvert[14] = "Economically Disadvantaged";
    groupConvert[15] = "Not Economically Disadvantaged";
    groupConvert[16] = "Migrant";
    groupConvert[17] = "Not Migrant";
    groupConvert[18] = "Homeless";
    groupConvert[19] = "Not Homeless";
    groupConvert[20] = "In Foster Care";
    groupConvert[21] = "Not in Foster Care";
    groupConvert[22] = "Parent in Armed Forces";
    groupConvert[23] = "Parent not in Armed Forces";
    // define conversions for grades
    gradeConvert["MATH3"] = 3;
    gradeConvert["MATH4"] = 4;
    gradeConvert["MATH5"] = 5;
    gradeConvert["MATH6"] = 6;
    gradeConvert["MATH7"] = 7;
    gradeConvert["MATH8"] = 8;
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
            if (gradeConvert[assessment] != grade) continue; // only get values for grade if specified
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

    for(auto &itr: multimap) { // looping through again just to be safe so not accessing bad memory
        myVec.emplace_back(itr.first,itr.second);
        //std::cout << "Group: " << groupConvert[itr.first] << "  Score: " << itr.second << "\n";
    }




    return myVec;
}

