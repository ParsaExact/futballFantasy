#include "Globalstuff.hpp"
#include "Player.hpp"
class Team
{
public:
    Team(string team_name);

private:
    string team_name;
    vector<Player *> team_players;
};