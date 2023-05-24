#include "Club.hpp"

Club::Club(string _name)
{
    name = _name;
}

string Club::get_name()
{
    return name;
}

void Club::add_player(int role, Player* p_player){
    players[role].push_back(p_player);
}