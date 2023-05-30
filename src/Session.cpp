#include "Session.hpp"

Session::Session()
{
    current_week_num = 0;
    is_admin_logged_in = false;
    is_user_logged_in = false;
    is_transfer_window_open = false;
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

void Session::login_user(string username, string password)
{
    User selected_user;
    bool flg = 0;
    for (User user : users)
    {
        if (user.username == username)
            selected_user = user, flg = 1;
    }
    if (!flg)
        throw NotFound();
    if (password != selected_user.password)
        throw PermissionDenied();
    current_user = selected_user;
    is_user_logged_in = true;
}

void Session::logout_user()
{
    is_admin_logged_in = false;
    is_user_logged_in = false;
}

void Session::register_admin(string username, string password)
{
    if (username != admin_username || password != admin_password)
        throw BadRequest();
    is_admin_logged_in = true;
}

void Session::close_transfer_window()
{
    if (!is_admin_logged_in)
        throw PermissionDenied();
    is_transfer_window_open = false;
}

void Session::open_transfer_window()
{
    if (!is_admin_logged_in)
        throw PermissionDenied();
    is_transfer_window_open = true;
}

void Session::add_user(string team_name, string password, Team* team)
{
    User new_user(team_name, password, team);
    new_user.username = team_name;
    users.push_back(new_user);
}