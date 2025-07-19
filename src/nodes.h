#pragma once
#include <iostream>
#include <vector>
#include "var.h"
#include "node_connection.h"

class Vs_Node {

    public:
        Vs_Node();
        ~Vs_Node();

        typedef enum Node_Type {
            BEGIN,
            INT_VARIABLE,
            FLOAT_VARIABLE, 
            DOUBLE_VARIABLE,
            STRING_VARIABLE,
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

        int make_node(Node_Type *t, int node_id, int x_pos, int y_pos, std::vector<Connection>connections);
        bool set_node_id(int id);
        int get_node_id();
        int place_node();
        Node_Type get_node_type();
        int grab_node_connection();
        int place_node_connection();
        std::vector<Variable, std::string> get_data_from_node();
        std::vector<Connection> get_connections_from_node();
        std::string exec_node();

    private: 
        Node_Type node_type;
        int id; 
        float node_x; 
        float node_y;
        bool is_commented;
        bool is_visible;

        std::vector<Connection>connection;
        std::string error_message;

};