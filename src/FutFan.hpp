#ifndef _FUTFAN_HPP_
#define _FUTFAN_HPP_

#include "Globalstuff.hpp"
#include "Club.hpp"
#include "Player.hpp"

class FutFan {
public:
    ~FutFan();
    void get_league_data(string file_address);
    Player* find_player_by_name(string player_name);
    Club* find_club_by_name(string club_name);
    void add_player(string player_name, int role);
    void add_club(string club_name);
    void add_player_to_club(string club_name, string player_name);
    void debug(){
        for (Club* club : clubs)
            club->debug();
    };
private:
    vector <Player*> players;
    vector <Club*> clubs;
    vector<vector<string>> make_file_lines(string file_address, char delimiter);
};

#endif