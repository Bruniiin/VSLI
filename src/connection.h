#pragma once
#include <cstring>
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

        void connect(Connection_Type *t, int dest_node_id, int dest_connection_id);
        void break_connection();
        int get_connection_id();
        int get_connected_id();
        bool is_connected();
        void hold_connection();
        void release_connection();

    private:
        Connection_Type connection_type;
        int id;
        int dest_connection_id;
        int dest_node_id; 
        float connection_x;
        float connection_y; 
        bool is_connected_to_node;
        bool is_held; 

};