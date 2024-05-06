#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <map>
#include "print.hpp"

template<typename T>
int amount_of_bible_lines( std::vector<T>& bible ){
    return std::count( bible.begin(), bible.end(), '\n');
};

template<typename T>
int amount_of_alpha_chars_in_bible( std::vector<T>& bible ){
    return std::count_if( bible.begin(), bible.end(), [](char c){ return isalpha(c); } );
};

template<typename T>
void lowercase_all_chars_in_bible( std::vector<T>& bible ){
    std::for_each(  bible.begin(), bible.end(), 
                    [](char &c){ 
                        if(isupper(c)){ 
                            c = tolower(c); 
                        }
                    } 
                 );
};

template<typename T>
std::array<int, 26> appearances_alpha_chars_in_bible( std::vector<T>& bible ){
std::array<int, 26> alphabet_chars = {};
std::for_each(  bible.begin(), bible.end(), 
                [&](char c){ 
                    if(isalpha(c)){
                        if(islower(c)){
                            alphabet_chars[ c - 'a' ]++;
                        } else{
                            alphabet_chars[ c - 'A' ]++;
                        }
                    }            
                } 
             );
    return alphabet_chars;
};

template<size_t N, typename T, typename E, typename P>
void sort_based_on_most_frequent_char( std::array<T, N>& alphabet_chars, std::array<std::pair<E, P>, N> &new_alphabet ){
    for(int i = 0; i < (int)alphabet_chars.size(); i++){ 
        new_alphabet[i] = std::make_pair(('a' + i) , alphabet_chars[i]);
    }

    std::sort(  new_alphabet.begin(), new_alphabet.end(), 
                [&](std::pair<char, int> a, std::pair<char, int> b){
                    return a.second > b.second;
                }
            );
};

template<typename T, typename E>
void sort_map( std::map<std::string, int> words, std::vector<std::pair<T, E>>& pairs ){
    for (auto i = words.begin(); i != words.end(); i++){
        pairs.push_back(*i);
    }

    std::sort(   pairs.begin(), pairs.end(), 
            [&](std::pair<std::string, int> a, std::pair<std::string, int> b){
                return a.second > b.second;
            }
        );
}


int main(){
    std::array<std::pair<char, int>, 26> new_alphabet = {};
    std::vector<char> bible;

    std::ifstream iStream("bible.txt");  

    char c;
    while(!iStream.eof()){
        iStream.get(c);
        bible.push_back(c);        
    }
    iStream.close();

    auto bible_lines        (bible);
    auto bible_alpha_chars  (bible);

    /**
     *  This function returns the amount of elements in the given vector
     */
    auto bibleSize = bible.size();
    
    /**
     *  This function returns the amout of lines in the given file
     * 
     *  @param bible_lines, std::vector<char>
     */
    auto bibleLines = amount_of_bible_lines( bible_lines );

    /**
     *  This function returns the amount of alphabet chars in the given vector
     * 
     *  @param bible_alpha_chars, std::vector<char>
     */
    auto bibleAlphaChars = amount_of_alpha_chars_in_bible( bible_alpha_chars );

    /**
     *  This function needs a std::vector with all the characters and turns them to lowercase in case it was uppercase
     * 
     *  @param bible, std::vector<char>
     */
    lowercase_all_chars_in_bible( bible );

    /**
     *  This function returns a std::vector whit frequencies of all the alphabet chars in the given vector
     * 
     *  @param bible, std::vector<char>
     */
    auto alphabet = appearances_alpha_chars_in_bible( bible );
    
    
    /**
     *  Sort a given vector based on the frequency of chars in the bible
     *  The "old alphabet" (1st @param) gets copied in another vector which has std::pairs as elements to keep the right char with the right value.
     * 
     *  @param alphabet, std::array<int, 26> 
     *  @param new_alphabet, std::array<std::pair<char, int>, 26>
     */
    sort_based_on_most_frequent_char( alphabet, new_alphabet );



    /**
     *  Print all the info about the given file
     */

    print("Amount of chars in bible: " + std::to_string(bibleSize), true);
    print("Amount of bible Lines: " + std::to_string(bibleLines), true);
    print("Amount of alphabet chars: " + std::to_string(bibleAlphaChars), true);
    print("\nBible lowercase: ", true);
    // print_container( bible, false);
    print("\nApppearances of all the alphabet chars: ");

    for( int i = 0; i < (int)alphabet.size(); i++ ){
        print( std::string{(char)('a' + i)} + ": " + std::to_string(alphabet[i]) );
    }

    print("\n\nSorted apppearances of all the alphabet chars: ");
    print_container(new_alphabet, true);

    print("top 10 most common words in the bible: ");
    
    std::ifstream iStream2("bible.txt");
    std::map<std::string, int> words;

    std::vector<std::pair<std::string, int>> pairs;

    std::string word;
    char w;
    while(!iStream2.eof()){
        iStream2.get(w);
        if(isalpha(w)){
            if(isupper(w)){
                w = tolower(w);
            }
            word += w;
        } 
        else if(w == ' '){
            words[word]++;
            word = "";
        }
        else{}
    }
    iStream2.close();

    sort_map( words, pairs );

    int i = 1;
    for(auto ptr = pairs.begin(); ptr < (pairs.begin()+10); ptr++){
        std::cout << i << ":\t";
        print(ptr->first, false);
        print("\t", false);
        print(ptr->second, true);
        i++;
    }

 

    
}