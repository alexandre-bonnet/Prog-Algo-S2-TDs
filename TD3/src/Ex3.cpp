#include <iostream>
int main(){
    int a {11};
    std::cout << "la valeur est  :" << a<<std::endl;
    std::cout << "la valeur est  :" << static_cast<float>(a)/2.f <<std::endl;
    return 0;
}