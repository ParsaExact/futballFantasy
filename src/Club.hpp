#ifndef _CLUB_HPP_
#define _CLUB_HPP_

#include "Globalstuff.hpp"
#include "Player.hpp"

class Club
{
public:
    Club(string _name);
    string get_name();
    void add_player(int pos, Player* p_player);
    void debug(){
        cout << "Club name: " << name << endl;
        for (int i = 0; i < ROLE_CNT; ++i){
            cout << "ROLE: " << ROLE_NAME[i] << endl;
            for (Player* player : players[i])
                player->debug();
        }
    };
private:
    string name;
    vector<Player*> players[ROLE_CNT];
};

#endif