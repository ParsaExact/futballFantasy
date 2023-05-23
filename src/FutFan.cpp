#include "FutFan.hpp"


void FutFan::add_player(string player_name)
{
    players.push_back(new Player(player_name));
}

Player* FutFan::find_player_by_name(string player_name)
{
    for (Player* player : players)
        if (player->get_name() == player_name)
            return player;
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
        vector <string> words = split_line_into_words(line, delimiter);
        lines.push_back(words);
    }
    file.close();
    return lines;
}

void FutFan::get_league_data(string file_address)
{
    vector<vector<string>> lines;
    lines = make_file_lines(file_address, COMMA);
    cout << lines.size() << endl;
    for (int line_num = 0; line_num < (int)lines.size(); ++line_num)
    {
        if (line_num == JUNK_LINE)
            continue;
        if (line_num > 1)
            continue;
        for (int pos_num = 0; pos_num < POS_CNT; ++pos_num)
        {
            vector <string> pos_players = split_line_into_words(lines[line_num][pos_num], NAME_DELIM);
            // to be continued
        }
    }

}