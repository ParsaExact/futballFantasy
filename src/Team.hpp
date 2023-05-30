#ifndef _TEAM_HPP_
#define _TEAM_HPP_
#include "Globalstuff.hpp"
#include "Player.hpp"
class Team
{
public:
    Team(string team_name);
    string get_team_name();
private:
    string team_name;
    vector<Player*> squad;
};

#endif