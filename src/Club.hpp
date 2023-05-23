#ifndef _CLUB_HPP_
#define _CLUB_HPP_

#include "Globalstuff.hpp"
#include "Player.hpp"

class Club
{
public:
    Club(string _name);
    void add_player(int pos, Player* p_player);
private:
    string name;
    vector<Player*> players[POS_CNT];
};

#endif