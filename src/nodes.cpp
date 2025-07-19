#include "nodes.h"

Vs_Node::Vs_Node()
{
    
}

int Vs_Node::make_node(Node_Type *t, int node_id, int x_pos, int y_pos, int* connection_size, std::vector<Connection>connections)
{  
    connection.clear();

    node_type = *t;
    id = node_id;
    node_x = x_pos;
    node_y = y_pos;
    
    // Node node = get_node_type_struct(*t);
    int count = node.connection_count;
    for(int i = 0; i < count; i++) {
        connection.push_back({});
        connection[i].set_connection_id(*connection_size++);
    }

    switch(node_type) {
        case BEGIN:
            connection[0].set_type(Connection::EXECUTE_NODE_FORWARD);
            connection[0].set_pos(Connection::TOP_RIGHT);
            break;
        case IF_STATEMENT:
            connection[0].set_type(Connection::EXECUTE_NODE_BACK);
            connection[0].set_pos(Connection::TOP_LEFT);
            connection[1].set_type(Connection::EXECUTE_NODE_FORWARD);
            connection[1].set_pos(Connection::TOP_RIGHT);
            connection[2].set_type(Connection::BRANCH);
            connection[2].set_pos(Connection::BOTTOM_RIGHT);
            break;
        case FOR_LOOP:
            connection[0].set_type(Connection::EXECUTE_NODE_BACK);
            connection[0].set_pos(Connection::TOP_LEFT);
            connection[1].set_type(Connection::EXECUTE_NODE_FORWARD);
            connection[1].set_pos(Connection::TOP_RIGHT);
            connection[2].set_type(Connection::VARIABLE);
            connection[2].set_pos(Connection::BOTTOM_LEFT);
            connection[3].set_type(Connection::BRANCH);
            connection[3].set_pos(Connection::BOTTOM_RIGHT);
            connection[4].set_type(Connection::BREAK);
            connection[4].set_pos(Connection::BOTTOM_RIGHT);
            break;
        case ASSIGNMENT:
            connection[0].set_type(Connection::EXECUTE_NODE_BACK);
            connection[0].set_pos(Connection::TOP_LEFT);
            connection[1].set_type(Connection::EXECUTE_NODE_FORWARD);
            connection[1].set_pos(Connection::TOP_RIGHT);
            break;
        default:
            std::cout << "out of range node type" << std::endl; 
            return -1;
    }

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

int Vs_Node::place_node(int x_pos, int y_pos)
{
    node_x = x_pos;
    node_y = y_pos;

    return 0;
}

std::vector<Connection> Vs_Node::get_connections_from_node()
{
    return std::vector<Connection>();
}
