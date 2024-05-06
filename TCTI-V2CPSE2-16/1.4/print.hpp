template<typename T, typename E>
std::ostream & operator<<(std::ostream & os, const std::pair<T, E>& rhs){
    return os   
        << "[  "  << rhs.first << ", " << rhs.second << "  ]";
}

template<typename T>
void print( T comment, bool new_line = true){
    std::cout << comment;
    if(new_line){ std::cout << std::endl; }
};

template< typename T >
void print_container( T begin, T end, bool new_line = false){
    for( T p = begin; p != end; p++ ){
        std::cout << *p;
        if (new_line){
            std::cout << std::endl;
        }
   } std::cout << "\n"; 
};

template<typename T>
void print_container( std::vector<T> & v, bool new_line = true ){
    print_container(v.begin(), v.end(), new_line);
};

template<typename T, size_t N>
void print_container( std::array<T, N> & v, bool new_line = true ){
    print_container(v.begin(), v.end(), new_line);
};