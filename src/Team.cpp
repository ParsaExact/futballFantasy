#include "Team.hpp"
Team::Team(string team_name_ , string password_)
{
    team_name = team_name_;
    password = password_;
}
string Team::get_team_name()
{
    return team_name;
}
string Team::get_team_password()
{
    return password;
}