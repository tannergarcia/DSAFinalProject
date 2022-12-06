#include "mergesort.h"

void merge(std::vector<std::pair<std::string, int>> &data, int left, int middle, int right) {
    int n1 = middle - left + 1; //size of left subarray
    int n2 = right - middle; //size of right subarray
    std::pair<std::string, int> X[n1], Y[n2]; //X[] is left array, Y[] is right

    for(int i = 0; i < n1; i++) {
        X[i] = data[left + i]; //fill left subarray
    }
    for(int j = 0; j < n2; j++) {
        Y[j] = data[middle + 1 + j]; //fill right subarray
    }

    int i = 0; //starting index of left subarray
    int j = 0; //starting index of right subarray
    int k = left; //starting index of sorted array

    while(i < n1 && j < n2) { //combines both arrays into a sorted array, making sure to sort the values as it does so
        if(X[i] <= Y[j]) { //if the next val in the left subarray is less than the next val in the right subarray
            data[k] = X[i]; //the next element of the sorted array is the next val in the left subarray
            i++; //move onto next val in left subarray
        }
        else { //if not, next val of right subarray is less than next val of left subarray
            data[k] = Y[j]; //so next val in sorted array is the next val in the right subarray
            j++; //move onto next val in right subaray
        }
        k++; //move onto next val in sorted array
    }

    while(i < n1) {
        data[k] = X[i];
        i++;
        k++;
    }

    while(j < n2) {
        data[k] = Y[j];
        j++;
        k++;
}
}
long long int mergeSort(std::vector<std::pair<std::string, int>> &data, int left, int right) {
    auto start = chrono::high_resolution_clock::now();
    //sort
    if (left < right) {
        int middle = left + ((right - left) / 2); //gets middle of array
        mergeSort(data, left, middle); //sorts left sub array
        mergeSort(data, middle + 1, right); //sorts right subarray

        merge(data, left, middle, right); //merges the sorted subarrays
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return duration;
}

void merge(std::vector<std::pair<int, int>> &data, int left, int middle, int right) {
    int n1 = middle - left + 1; //size of left subarray
    int n2 = right - middle; //size of right subarray
    std::pair<int, int> X[n1], Y[n2]; //X[] is left array, Y[] is right

    for(int i = 0; i < n1; i++) {
        X[i] = data[left + i]; //fill left subarray
    }
    for(int j = 0; j < n2; j++) {
        Y[j] = data[middle + 1 + j]; //fill right subarray
    }

    int i = 0; //starting index of left subarray
    int j = 0; //starting index of right subarray
    int k = left; //starting index of sorted array

    while(i < n1 && j < n2) { //combines both arrays into a sorted array, making sure to sort the values as it does so
        if(X[i] <= Y[j]) { //if the next val in the left subarray is less than the next val in the right subarray
            data[k] = X[i]; //the next element of the sorted array is the next val in the left subarray
            i++; //move onto next val in left subarray
        }
        else { //if not, next val of right subarray is less than next val of left subarray
            data[k] = Y[j]; //so next val in sorted array is the next val in the right subarray
            j++; //move onto next val in right subaray
        }
        k++; //move onto next val in sorted array
    }

    while(i < n1) {
        data[k] = X[i];
        i++;
        k++;
    }

    while(j < n2) {
        data[k] = Y[j];
        j++;
        k++;
    }
}
long long int mergeSort(std::vector<std::pair<int, int>> &data, int left, int right) {
    auto start = chrono::high_resolution_clock::now();
    //sort
    if (left < right) {
        int middle = left + ((right - left) / 2); //gets middle of array
        mergeSort(data, left, middle); //sorts left sub array
        mergeSort(data, middle + 1, right); //sorts right subarray

        merge(data, left, middle, right); //merges the sorted subarrays
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return duration;
}