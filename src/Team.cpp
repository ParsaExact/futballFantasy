#include "Team.hpp"
Team::Team(string team_name_)
{
    team_name = team_name_;
}

string Team::get_team_name()
{
    return team_name;
}