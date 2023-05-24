#include "Player.hpp"

Player::Player(string _name, int _role)
{
    name = _name;
    role = _role;
    cnt_yellow_cards = 0;
}

int Player::get_role()
{
    return role;
}

string Player::get_name()
{
    return name;
}

void Player::add_week_stats(int week_num)
{
    weekstats.push_back(WeekStats(week_num));
}

void Player::update_yellow_card(int week_num)
{
    cnt_yellow_cards++;
    weekstats[week_num].set_yellow_card();
}

void Player::update_red_card(int week_num)
{
    weekstats[week_num].set_red_card();
}

void Player::update_injured(int week_num)
{
    weekstats[week_num].set_injured();
}
bool Player::is_available(int week_num)
{

    for (int i = week_num-1; i >= max(0, week_num-RED_CARD_SUS_DAYS) ; --i)
    {
        if(weekstats[i].get_has_red_card()){
            cnt_yellow_cards=0;
            return false;
        }
    }
    for (int i = week_num - 1; i >= max(week_num - INJURY_SUS_DAYS, 0); --i)
    {
        if (weekstats[i].get_is_injured()){
            return false;
        }
    }
    if(cnt_yellow_cards == 3)
    {
        cnt_yellow_cards=0;
        return false;
    }
    return true;
}