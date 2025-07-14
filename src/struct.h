#pragma once
#include "variable.h"
#include <cstring>
#include <vector>
#include <iostream>

class Struct {

    public:
        Struct();
        ~Struct();
        int add_element_to_struct();
        int remove_element_from_struct();
        size_t get_size_of_struct();
        

    private: 
        std::vector<Variable>variable;


}