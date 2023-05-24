#ifndef _FUTFAN_HPP_
#define _FUTFAN_HPP_

#include "Globalstuff.hpp"
#include "Club.hpp"
#include "Player.hpp"
#include "Match.hpp"

bool cmp(Club* i, Club* j);

class FutFan {
public:
    ~FutFan();
    void get_league_data(string file_address);
    Player* find_player_by_name(string player_name);
    Club* find_club_by_name(string club_name);
    void add_player(string player_name, int role);
    void add_club(string club_name);
    void add_player_to_club(string club_name, string player_name);
    void make_new_week_stats(int week_num);
    void update_match_stats(int week_num, vector <string> &data);
    void update_week_stats( int week_num);
    string output_standing();
    void team_of_the_week(int week_num);
    void matchs_of_the_week(int week_num);
private:
    vector <Player*> players;
    vector <Club*> clubs;
    vector<vector<Match>> all_matches;
    vector<vector<string>> make_file_lines(string file_address, char delimiter);
};

#endif