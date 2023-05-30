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
    string login_user(vector <string> command);
    string logout_user(vector <string> command);
    string register_admin(vector <string> command);
    string close_transfer_window(vector <string> command);
    string open_transfer_window(vector <string> command);
    int find_command_num(vector <string> command);
    string signup_user(vector <string> command);
    void print_players(vector<Player*> club_players);
private:
    FutFan* futfan;
    Session* session;
};




#endif