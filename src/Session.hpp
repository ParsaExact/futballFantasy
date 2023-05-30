#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include "Globalstuff.hpp"
#include "Team.hpp"

class User 
{
public:
    User();
    User(string username, string password, Team* team);
    string username;
    string password;
    Team* team;
private:
};

class Session
{
public:
    Session();
    void add_user(string team_name, string password, Team* team);
    bool is_username_available(string team_name);
    bool is_admin_logged_in;
    bool is_user_logged_in;

private:
    int current_week_num;
    string admin_username;
    string admin_password;
    User current_user;
    vector <User> users;
};

#endif