#pragma once

#include "object.hpp"

struct buttonIdentifier {
public:
    ~buttonIdentifier(){};
    buttonIdentifier(){};
    buttonIdentifier( Object* _object, bool* _functionality = nullptr, bool _isSelected = false, std::string _name = "" );
    buttonIdentifier( Object* _object, std::string _name = "", bool _isSelected = false, bool* _functionality = nullptr  );

    void free();

    Object* object;
    std::string name;
    bool isSelected;
    bool* functionality;
};
