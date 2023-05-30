#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include "Globalstuff.hpp"
#include "Team.hpp"
#include "User.hpp"

class Session
{
public:
    Session();
    void add_user(string team_name, string password, Team* team);
    bool is_username_available(string team_name);
    void login_user(string username, string password);
    void open_transfer_window();
    void close_transfer_window();
    void logout_user();
    void register_admin(string username, string password);
    bool is_admin_logged_in;
    bool is_user_logged_in;
    bool is_transfer_window_open;

private:
    int current_week_num;
    string admin_username;
    string admin_password;
    User current_user;
    vector <User> users;
};

#endif