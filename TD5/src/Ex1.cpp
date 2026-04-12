#include <iostream>

size_t folding_string_hash(std::string const& s, size_t max){
    size_t hash {0};
    for(size_t i{0};i < s.size();i++){
        hash +=s[i]*(i+1);
        hash%=max;
    }
    hash %=max;
    return hash;
}

int main(){
    std::string str {0};
    std::cout << "Entrez un string : ";
    std::cin >> str;
    std::cout << folding_string_hash(str,120);
}