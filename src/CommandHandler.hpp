#ifndef _COMMAND_HANDLER_
#define _COMMAND_HANDLER_

#include "FutFan.hpp"
#include "Globalstuff.hpp"
#include "Session.hpp"

class CommandHandler
{
public:
    CommandHandler(FutFan* futfan_);
    void handle_commands();
    int find_command_num(vector <string> command_words);
    string signup_user(vector <string> command);
    void print_players(vector<Player*> club_players);
private:
    FutFan* futfan;
    Session* session;
};




#endif