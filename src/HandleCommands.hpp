#ifndef _HANDLE_COMMANDS_
#define _HANDLE_COMMANDS_

#include "Player.hpp"
#include "Globalstuff.hpp"

class HandleCommands
{
public:
    void get_commands();
    bool is_command_valid(string command_type);
    void print_players(vector<Player*> club_players);
};




#endif