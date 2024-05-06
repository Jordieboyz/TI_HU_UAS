#pragma once

#include <exception>

#define where(line, file) std::string{ static_cast<std::string>(file) + ":" + std::to_string(line) }
#define eof end_of_file(__LINE__, __FILE__)
#define uknown_clr(msg) uknown_color(msg, __LINE__, __FILE__)
#define uknown_shp(msg) uknown_shape(msg, __LINE__, __FILE__)
#define invalid_pos(msg) invalid_position(msg, __LINE__, __FILE__)
#define invalid_rad(msg) invalid_radius(msg, __LINE__, __FILE__)
#define failed_img(msg) failed_image(msg, __LINE__, __FILE__)
#define out_of_bnd(msg) out_of_bounds(msg, __LINE__, __FILE__)

class out_of_bounds : public std::exception {
public:
    out_of_bounds( const int coor, int line, const char * file ):
        s{ std::string{ "\n\tout of bounds coordinate ["} + std::to_string(coor) + "]\n\t" + where(line, file) + "\n" }
    {}

    const char* what() const noexcept{
        return s.c_str();
    }
private:
    std::string s;
};


class uknown_color : public std::exception {
public:
    uknown_color( const std::string & name, int line, const char * file ):
        s{ std::string{ "\n\tuknown color ["} + name + "]\n\t" + where(line, file) + "\n" }
    {}

    const char* what() const noexcept{
        return s.c_str();
    }
private:
    std::string s;
};


class uknown_shape : public std::exception {
public:
    uknown_shape( const std::string & name, int line, const char * file ):
        s{ std::string{ "\n\tuknown shape ["} + name + "]\n\t" + where(line, file) + "\n" }
    {}

    const char* what() const noexcept{
        return s.c_str();
    }
private:
    std::string s;
};

class end_of_file : public std::exception {
public:
    end_of_file( int line, const char * file ) :
        s{ std::string{ "\n\tEnd Of File!\n\t" } + where(line, file) + "\n" }
    {}

    const char* what() const noexcept{
        return s.c_str();
    }
private:
    std::string s;
};

class invalid_position : public std::exception {
public:
    invalid_position( const char & name, int line, const char * file ) :
        s{ std::string{ "\n\tinvalid position["} + name + "]\n\t" + where(line, file) + "\n" }
    {}
    
    const char* what() const noexcept{
        return s.c_str();
    }
private:
    std::string s;
};

class failed_image : public std::exception {
public:
    failed_image( const std::string & name, int line, const char * file ) :
        s{ std::string{ "\n\tcannot load image["} + name + "]\n\t" + where(line, file) + "\n" }
    {}
    
    const char* what() const noexcept{
        return s.c_str();
    }
private:
    std::string s;
};

class invalid_radius : public std::exception {
public:
    invalid_radius( const char rad, int line, const char * file) :
        s{ std::string{ "\n\tinvalid radius[ " } + std::to_string(rad) + where(line, file) + "\n" }
    {}
    
    const char* what() const noexcept{
        return s.c_str();
    }
private:
    std::string s;
};