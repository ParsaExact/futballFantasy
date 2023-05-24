#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include "WeekStats.hpp"
#include "Globalstuff.hpp"

class Player
{
public:
    Player(string _name, int _role);
    string get_name();
    int get_role();
    void update_yellow_card(int week_num);
    void update_red_card(int week_num);
    void update_injured(int week_num);
    void update_score(int week_num, float week_score);
    void add_week_stats(int week_num);
    bool is_available(int week_num);
    void debug()
    {
        cout << "Player name: " << name << ' ' << weekstats[0].get_score() << endl;
    };

private:
    string name;
    int role;
    int cnt_yellow_cards;
    vector<WeekStats> weekstats;
};

#endif
