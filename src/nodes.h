#pragma once
#include <iostream>
#include <vector>
#include "var.h"
#include "connection.h"

class Vs_Node {

    public:

        typedef enum Node_Type {
            VARIABLE,
            IF_STATEMENT, 
            FOR_LOOP,
            ASSIGNMENT,
            ADD,
            DIVIDE,
            MULTIPLY,
            SUBTRACT, 
            MOD,
            CALL,
            RETURN,
            SWITCH,
        };

        Vs_Node();
        ~Vs_Node();
        int make_node();
        int place_node();
        Node_Type get_node_type();
        std::vector<Variable> get_data_from_node();
        std::vector<Connection, int>get_connections_from_node();
        std::string exec_node();
        // int move_node();


    private: 

        Node_Type node_type;
        float node_x; 
        float node_y;
        bool is_visible;
        std::string error_message;

};