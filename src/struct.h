#pragma once
#include "variable.h"
#include <cstring>
#include <vector>
#include <iostream>

class Struct { // class in Python

    public:
        Struct();
        ~Struct();
        int add_element_to_struct(bool is_function, std::string element_name, Variable element, bool is_array, size_t array_size);
        int remove_element_from_struct(int id);
        size_t get_size_of_struct();

    private: 
        size_t size;
        bool is_static;
        bool is_instance; 
        bool is_pointer_type;
        std::string struct_name;
        std::string instance_name;

        std::vector<Variable, std::string>variable;

};