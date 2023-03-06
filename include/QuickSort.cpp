#include "QuickSort.hpp"

int Partition(std::vector<int> &v, int low, int high){
    int i = low-1;
    int pivot=v[high];
    for (int j = low; j < high; j++){
        if (v[j] <= pivot){
            i++;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i+1], v[high]);
    return i+1;
}

void QuickSort(std::vector<int> &v, int low , int high){
    if (low < high){
        int p = Partition(v, low, high);
        QuickSort(v, low, p-1);
        QuickSort(v, p+1, high);
    }
}