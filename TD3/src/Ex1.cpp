#include <iostream>
#include <vector>
#include <algorithm>

bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

void bubble_sort(std::vector<int> & vec){
    size_t const size = vec.size();
    for (size_t i {0}; i<size;i++){
        for (size_t j {0};j<size-(i+1);j++){
            if(vec[j]>vec[j+1]){
                std::swap(vec[j], vec[j+1]);
            }
        }
    }
}

int main(){
    std::vector<int> array {9, 8, 6, 7, 5, 4, 1, 2, 3};
    if (!is_sorted(array)) {
        bubble_sort(array);
    }
    std::cout << "Le tableau est trie, voici les valeurs : ";
    for ( int i : array){
        std::cout<< i << ", ";
    } std::cout << std::endl;
    return 0;
}