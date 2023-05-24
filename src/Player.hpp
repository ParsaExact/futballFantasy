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
    void add_week_stats(int week_num);
    bool is_available(int week_num);
    void debug()
    {
        cout << "Player name: " << name << " and plays in " << ROLE_NAME[role] << endl;
    };

private:
    string name;
    int role;
    int cnt_yellow_cards;
    vector<WeekStats> weekstats;
};

#endif
