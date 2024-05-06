#include "set.hpp"
#include <iostream>



int main(){

   std::array<char , 4> b = { 'A', 'B', 'C', 'D'};
   std::array<char , 4> c = { 'A', 'B', 'C', 'F'};
   std::array<char , 4> d = { 'A', 'B', 'C', 'I'};


   set<std::array<char, 4>, 3> a;

   a.add(b);
   a.add(c);
   a.add(d);

   std::cout << a.max() << std::endl;
}