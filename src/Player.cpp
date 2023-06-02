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
    week_num--;
    cnt_yellow_cards++;
    weekstats[week_num].set_yellow_card();
}

void Player::update_red_card(int week_num)
{
    week_num--;
    weekstats[week_num].set_red_card();
}

void Player::update_injured(int week_num)
{
    week_num--;
    weekstats[week_num].set_injured();
}

void Player::update_score(int week_num, float week_score)
{
    week_num--;
    weekstats[week_num].set_score(week_score);
}

void Player::update_availability(int week_num)
{
    week_num--;
    for (int i = week_num; i >= max(0, week_num - RED_CARD_SUS_DAYS); --i)
    {
        if (weekstats[i].get_has_red_card())
        {
            cnt_yellow_cards = 0;
            can_play = false;
            return;
        }
    }
    for (int i = week_num; i >= max(week_num - INJURY_SUS_DAYS, 0); --i)
    {
        if (weekstats[i].get_is_injured())
        {
            can_play = false;
            return;
        }
    }
    if (cnt_yellow_cards == 3)
    {
        cnt_yellow_cards = 0;
        can_play = false;
        return;
    }
    can_play = true;
}

float Player::find_player_score(int week_num)
{
    if(!week_num)
        return 0.0;
    cout<<week_num;
    return weekstats[week_num-1].get_score();
}

float Player::calculate_avarage_score()
{
    float sum = 0;
    int cnt = 0;
    for(WeekStats week : weekstats)
    {
        cnt++;
        sum+=week.get_score();
    }
    if(!cnt)
        return 0;
    return sum / cnt;
}
