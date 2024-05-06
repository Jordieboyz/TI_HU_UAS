#include <iostream>
#include <fstream>
#include <string>

#include "../07-library/compressor.hpp"

int main( void ){	
   lz_compressor< 4096 > compressor;
 
   std::ifstream f1;
   f1.open( "wilhelmus.txt" );
   if( ! f1.is_open()){
      std::cerr << "input file not opened";
      return -1;      
   }
   
   std::ofstream f2;
   f2.open( "wilhelmus.asm" );
   f2 << ".global msg"
      << "\n\n.data\nmsg:\n.asciz \"";

   if( ! f2.is_open()){
      std::cerr << "output file not opened";
      return -1;      
   }
   
   compressor.compress( 
      [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; },
      [ &f2 ]( char c ){ f2.put( c );}
  );
   
   f2 << "\"";
   f1.close();
   f2.close();
}
