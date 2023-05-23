#ifndef _FUTFAN_HPP_
#define _FUTFAN_HPP_

#include "Globalstuff.hpp"
#include "Club.hpp"
#include "Player.hpp"

class FutFan {
public:
    void get_league_data(string file_address);
    Player* find_player_by_name(string player_name);
    void add_player(string player_name);
private:
    vector <Player*> players;
    vector<vector<string>> make_file_lines(string file_address, char delimiter);
};

#endif