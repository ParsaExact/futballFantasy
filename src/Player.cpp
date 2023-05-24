#include "Player.hpp"

Player::Player(string _name, int _role)
{
    name = _name;
    role = _role;
}

int Player::get_role()
{
    return role;
}

string Player::get_name()
{
    return name;
}