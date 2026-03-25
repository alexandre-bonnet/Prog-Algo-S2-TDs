#include <iostream>
#include <vector>
#include <algorithm>

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
    std::vector<int> array {9, 8, 6, 7, 5, 4, 1, 2, 3};
    if (!is_sorted(array)) {
        merge_sort(array);
    }
    std::cout << "Le tableau est trie, voici les valeurs : ";
    printVec(array);
    return 0;
}