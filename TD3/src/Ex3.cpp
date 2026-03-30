#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "ScopedTimer.hpp"

std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}

bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

void printVec(std::vector<int> & vec){
    for ( int i : vec){
            std::cout<< i << ", ";
        } std::cout << std::endl;
}

void merge_sort_merge(std::vector<int>& vec, size_t left, size_t middle, size_t right) {
    std::vector<int> temp = vec;
    size_t i = left;
    size_t j = middle + 1; 
    size_t k = left;
    while (i <= middle && j <= right) {
        if (temp[i] <= temp[j]) {
            vec[k] = temp[i];
            ++i;
        } else {
            vec[k] = temp[j];
            ++j;
        } k++;
    }
    while (i <= middle) {
        vec[k] = temp[i];
        ++i;
        ++k;
    }
    while (j <= right) {
        vec[k] = temp[j];
        ++j;
        ++k;
    }
}

void merge_sort(std::vector<int> & vec, size_t const left, size_t const right){
    if (left >= right) {
        return;
    }
    size_t middle = left + (right - left) / 2;
    merge_sort(vec, left, middle);
    merge_sort(vec, middle + 1, right);
    merge_sort_merge(vec, left, middle, right);
}

void merge_sort(std::vector<int> & vec) {
    merge_sort(vec, 0, vec.size() - 1);
}

int main(){
    std::vector<int> vec =  generate_random_vector(500,100);
    std::vector<int> vec2 = vec;
    {
        ScopedTimer timer("sort-timer");
        std::sort(vec2.begin(), vec2.end());
    }
    if (!is_sorted(vec)) {
    ScopedTimer timer("merge-timer");
    merge_sort(vec);
    }
    std::cout << "Le tableau est trie, voici les valeurs : ";
    //printVec(vec);
    return 0;
}