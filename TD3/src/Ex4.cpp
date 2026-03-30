#include <iostream>
#include <vector>
#include <algorithm>

bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

int search(std::vector<int> const& vec, int const num, size_t const left, size_t const right){
    size_t middle = left + (right - left) / 2;
    if(num<vec[middle]){
        return search(vec,num,left,middle-1);
    } else if(num>vec[middle]){
        return search(vec,num,middle+1,right);
    } else if(num==vec[middle]){
        return middle;
    } return -1;
}

int main(){
    std::vector<int> array {1,2,3,4,5,6,7,8,9};
    int num = 5;
    if (is_sorted(array)) {
        std::cout << "Le nombre "<< num << " est a l'indice "<< search(array, num, 0, array.size()-1);
    }
    return 0;
}