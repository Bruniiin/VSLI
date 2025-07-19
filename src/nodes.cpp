#include "nodes.h"

Vs_Node::Vs_Node()
{
    
}

int Vs_Node::make_node(Node_Type *t, int node_id, int x_pos, int y_pos, std::vector<Connection>connections)
{  
    connection.clear();

    node_type = *t;
    id = node_id;
    node_x = x_pos;
    node_y = y_pos;
    
    return 0;
}

bool Vs_Node::set_node_id(int node_id)
{
    id = node_id;
}

int Vs_Node::get_node_id()
{
    return id;
}

int Vs_Node::place_node()
{
    return 0;
}

std::vector<Connection> Vs_Node::get_connections_from_node()
{
    return std::vector<Connection>();
}
