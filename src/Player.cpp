#include "Player.hpp"

Player::Player(string _name)
{
    name = _name;
}

string Player::get_name()
{
    return name;
}