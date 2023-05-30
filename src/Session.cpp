#include "Session.hpp"

User::User(string username_, string password_, Team* team_)
{
    username = username_;
    password = password_;
    team = team_;
}

Session::Session()
{
    current_week_num = 0;
    is_admin_logged_in = false;
    is_user_logged_in = false;
    admin_username = ADMIN_USERNAME;
    admin_password = ADMIN_PASSWORD;
}

bool Session::is_username_available(string team_name)
{
    for (User user : users)
    {
        if (user.username == team_name)
            return false;
    }
    return true;
}

void Session::add_user(string team_name, string password, Team* team)
{
    User new_user(team_name, password, team);
    new_user.username = team_name;
    users.push_back(new_user);
}