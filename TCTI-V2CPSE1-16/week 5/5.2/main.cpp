#include <iostream>
#include "set.hpp"

int main(){
    set<int, 20> a;

    for(int i = 0; i <= a.max_size(); i++ ){
        a.add(i);
    }
    for(int i = 0; i <= a.max_size(); i+=2 ){
        a.remove(i);
    }
    for(int i = 0; i < a.max_size(); i++){
        std::cout << a.get(i) << std::endl;
    }

    std::cout << "\n\n\n\n";

    set< char, 26> b;
    
    for(int i = 0; i < b.max_size(); i++){
        b.add( 'A' + i);
    }

    for(int i = 1; i <= b.max_size(); i+=2 ){
        b.remove( 'A' + i);
    }

    for(int i = 0; i < b.max_size(); i++){
        std::cout << b.get(i) << std::endl;
    }


}