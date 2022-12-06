#include "shellsort.h"

long long int shellSort(std::vector<std::pair<std::string, int>> &data) {
    auto start = chrono::high_resolution_clock::now();

    double gap = data.size() / 2.0; //set the gap
    //for each gap
    for (double i = gap; i > 0; i /= 2.2) {
        //for each "set" of items to be swapped
        for (int j = i; j < data.size(); j++) {
            //swap them if need be
            pair<string, int> temp = data[j];
            int k;
            for (k = j; k >= i && data[k - i].second < temp.second; k -= i)
                data[k] = data[k - i];
            data[k] = temp;
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return duration;
}

//same as above, but with the first pair item being an int
long long int shellSort(std::vector<std::pair<int, int>> &data) {
    auto start = chrono::high_resolution_clock::now();

    double gap = data.size() / 2.0;
    for (double i = gap; i > 0; i /= 2.2) {
        for (int j = i; j < data.size(); j++) {
            pair<int, int> temp = data[j];
            int k;
            for (k = j; k >= i && data[k - i].second < temp.second; k -= i)
                data[k] = data[k - i];
            data[k] = temp;
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return duration;
}