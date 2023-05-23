#include "Club.hpp"

Club::Club(string _name){
    name = _name;
}

void Club::add_player(int pos, Player* p_player){
    players[pos].push_back(p_player);
}