#include "FutFan.hpp"

FutFan::~FutFan()
{
    for (Player *player : players)
        delete player;
    for (Club *club : clubs)
        delete club;
}

void FutFan::add_player(string player_name, int role)
{
    for (Player *player : players)
        if (player->get_name() == player_name)
            return; // throw duplicate name error
    players.push_back(new Player(player_name, role));
}

Player *FutFan::find_player_by_name(string player_name)
{
    for (Player *player : players)
        if (player->get_name() == player_name)
            return player;
    // throw not found exception
}
Club *FutFan::find_club_by_name(string club_name)
{
    for (Club *club : clubs)
        if (club->get_name() == club_name)
            return club;
    // throw not found exception
}

void FutFan::add_player_to_club(string club_name, string player_name)
{
    Club *p_club = find_club_by_name(club_name);
    Player *p_player = find_player_by_name(player_name);
    p_club->add_player(p_player->get_role(), p_player);
    // throw not found exception
}

vector<vector<string>> FutFan::make_file_lines(string file_address, char delimiter)
{
    ifstream file;
    file.open(file_address);
    vector<vector<string>> lines;
    string line;
    while (getline(file, line))
    {
        vector<string> words = split_line_into_words(line, delimiter);
        lines.push_back(words);
    }
    file.close();
    return lines;
}

void FutFan::add_club(string club_name)
{
    clubs.push_back(new Club(club_name));
}

void FutFan::get_league_data(string file_address)
{
    vector<vector<string>> lines;
    lines = make_file_lines(file_address, COMMA);
    for (int line_num = 0; line_num < (int)lines.size(); ++line_num)
    {
        if (line_num == JUNK_LINE)
            continue;
        string club_name;
        for (int ind = 0; ind <= ROLE_CNT; ++ind)
        {
            if (ind == 0)
            {
                club_name = lines[line_num][ind];
                add_club(club_name);
                continue;
            }
            int pos_num = ind - 1;
            vector<string> pos_players = split_line_into_words(lines[line_num][pos_num], NAME_DELIM);
            for (string player_name : pos_players)
            {
                add_player(player_name, pos_num);
                add_player_to_club(club_name, player_name);
            }
        }
    }
}

void FutFan::make_new_week_stats(int week_num)
{
    for (Player *player : players)
        player->add_week_stats(week_num);
}

void FutFan::update_match_stats(int week_num, vector<string> &data)
{
    for (int j = 0; j < (int)data.size(); ++j)
    {

        if (j == YELLOW_CARD)
        {
            vector<string> yellow_card_player = split_line_into_words(data[j], NAME_DELIM);
            for (string player_name : yellow_card_player)
                find_player_by_name(player_name)->update_yellow_card(week_num);
        }
        if (j == RED_CARD)
        {
            vector<string> red_card_player = split_line_into_words(data[j], NAME_DELIM);
            for (string player_name : red_card_player)
                find_player_by_name(player_name)->update_red_card(week_num);
        }
        if (j == INJURED)
        {
            vector<string> injured_player = split_line_into_words(data[j], NAME_DELIM);
            for (string player_name : injured_player)
                find_player_by_name(player_name)->update_injured(week_num);
        }
    }
}

void FutFan::update_week_stats(int week_num)
{
    // for (Player* player : players)
    // {
    //     player->
    // }
    string file_name = WEEK_STATS_FOLDER + "week_" + to_string(week_num);
    vector<vector<string>> week = make_file_lines(file_name, COMMA);
    for (int i = 0; i < (int)week.size(); ++i)
    {
        if (i == JUNK_LINE)
            continue;
        update_match_stats(week_num, week[i]);
    }
}