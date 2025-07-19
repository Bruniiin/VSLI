#pragma once
#include <iostream>

class Connection {

    public: 
        Connection();
        ~Connection();

        typedef enum Connection_Type {
            EXECUTE_NODE_BACK,
            EXECUTE_NODE_FORWARD,
            BRANCH,
            SWITCH_CASE, 
            SWITCH_DEFAULT,
            INPUT_INT,
            INPUT_DOUBLE,
            INPUT_FLOAT,
            INPUT_STRING, 
            OUTPUT_INT,
            OUTPUT_DOUBLE,
            OUTPUT_FLOAT,
            OUTPUT_STRING,
        };

        typedef enum Connection_Pos {
            TOP,
            BOTTOM,
            LEFT,
            RIGHT,
            TOP_LEFT,
            TOP_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_RIGHT,
        };

        void connect(Connection_Type *t, int dest_node_id, int dest_connection_id);
        void set_type(Connection_Type *t);
        void set_pos(Connection_Pos *p);
        void break_connection();
        int get_connection_id();
        int get_connected_id();
        Connection_Type get_type();
        Connection_Pos get_pos();
        bool is_connected();
        void hold_connection();
        void release_connection();

    private:
        Connection_Type connection_type;
        Connection_Pos connection_pos;
        int id;
        int dest_connection_id;
        int dest_node_id; 
        // float connection_x;
        // float connection_y; 
        bool is_connected_to_node;
        bool is_connection_held;
        std::vector<Variable>var;
        std::string error_message;

};