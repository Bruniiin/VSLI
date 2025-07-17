#include "node_connection.h"

Connection::Connection()
{
    
}

Connection::~Connection()
{

}

void Connection::connect(Connection_Type *t, int dest_node, int dest_connection)
{
    connection_type = *t;
    dest_node_id = dest_node;
    dest_connection_id = dest_connection;
}

void Connection::break_connection()
{
    dest_connection_id = NULL;
    is_connected_to_node = false;
}

int Connection::get_connection_id()
{
    return id;
}

int Connection::get_connected_id()
{
    return dest_connection_id;
}

bool Connection::is_connected()
{
    return is_connected_to_node;
}

void Connection::hold_connection()
{
    is_held = true;
}

void Connection::release_connection()
{
    is_held = false;
}
