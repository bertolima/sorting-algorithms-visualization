#include "include/QuickSort.hpp"
#include <ctime>
#include <iostream>

int generateNumber(int start, int range)
{
    return (start + rand() % range);
}


int main(){
    srand(static_cast<unsigned>(time(NULL)));
    std::vector<int> v;

    for (int i = 0; i<20;i++){
        v.push_back(generateNumber(0, 30));
    }

    for (int i = 0;i<v.size();i++){
        std::cout << v[i] << ", ";
    }
    std::cout << std::endl;

    QuickSort(v, 0, static_cast<int>(v.size()-1));

    for (int i = 0;i<v.size();i++){
        std::cout << v[i] << ", ";
    }
    std::cout << std::endl;
}


