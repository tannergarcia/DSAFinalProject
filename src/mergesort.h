#pragma once

#include "parse.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

void merge(std::vector<std::pair<std::string, int>> &data, int left, int middle, int right);
long long int mergeSort(std::vector<std::pair<std::string, int>> &data, int left, int right);

void merge(std::vector<std::pair<int, int>> &data, int left, int middle, int right);
long long int mergeSort(std::vector<std::pair<int, int>> &data, int left, int right);