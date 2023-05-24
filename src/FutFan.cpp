#include "FutFan.hpp"

bool cmp(Club *i, Club *j)
{
    if (i->get_points() < j->get_points())
        return false;
    if (i->get_points() == j->get_points() &&
        (i->get_goals_scored() - i->get_goals_conceded()) < (j->get_goals_scored() - j->get_goals_conceded()))
        return false;
    if (i->get_points() == j->get_points() &&
        (i->get_goals_scored() - i->get_goals_conceded()) == (j->get_goals_scored() - j->get_goals_conceded()) &&
        i->get_goals_scored() < i->get_goals_conceded())
        return false;
    return true;
}

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
            vector<string> pos_players = split_line_into_words(lines[line_num][ind], NAME_DELIM);
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
    string home_team, away_team;
    int home_team_score, away_team_score;
    for (int j = 0; j < (int)data.size(); ++j)
    {
        if (j == MATCH)
        {
            vector<string> match_teams = split_line_into_words(data[j], SCORE_DELIM);
            home_team = match_teams[0];
            away_team = match_teams[1];
        }
        if (j == RESULT)
        {
            vector<string> match_scores = split_line_into_words(data[j], SCORE_DELIM);
            home_team_score = stoi(match_scores[0]);
            away_team_score = stoi(match_scores[1]);
        }
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
            {
                Player *player = find_player_by_name(player_name);
                find_player_by_name(player_name)->update_red_card(week_num);
            }
        }
        if (j == INJURED)
        {
            vector<string> injured_player = split_line_into_words(data[j], NAME_DELIM);
            for (string player_name : injured_player)
                find_player_by_name(player_name)->update_injured(week_num);
        }
        if (j >= SCORES)
        {
            vector<string> player_plus_score = split_line_into_words(data[j], SCORE_DELIM);
            find_player_by_name(player_plus_score[0])->update_score(week_num, stof(player_plus_score[1]));
        }
    }
    all_matches[week_num - 1].push_back(Match(home_team, away_team, home_team_score, away_team_score));
    if (home_team_score < away_team_score)
        swap(home_team_score, away_team_score), swap(home_team, away_team);
    Club *home_club = find_club_by_name(home_team);
    Club *away_club = find_club_by_name(away_team);
    if (home_team_score == away_team_score)
    {
        home_club->update_standing(home_team_score, away_team_score, DRAW_POINT);
        away_club->update_standing(away_team_score, home_team_score, DRAW_POINT);
    }
    else
    {
        home_club->update_standing(home_team_score, away_team_score, WIN_POINT);
        away_club->update_standing(away_team_score, home_team_score, LOSS_POINT);
    }
}

void FutFan::update_week_stats(int week_num)
{
    vector<Match> empty_vec;
    all_matches.push_back(empty_vec);
    for (Player *player : players)
    {
        player->add_week_stats(week_num);
    }
    string file_name = WEEK_STATS_FOLDER + "week_" + to_string(week_num) + ".csv";
    vector<vector<string>> week = make_file_lines(file_name, COMMA);
    for (int i = 0; i < (int)week.size(); ++i)
    {
        if (i == JUNK_LINE)
            continue;
        update_match_stats(week_num, week[i]);
    }
    for (Player *player : players)
    {
        player->update_availability(week_num);
    }
}

string FutFan::output_standing()
{
    ostringstream out;
    sort(clubs.begin(), clubs.end(), cmp);
    out << "league standing:" << endl;
    for (int i = 0; i < (int)clubs.size(); ++i)
    {
        Club *club = clubs[i];
        out << i + 1 << ". " << club->get_name() << ": ";
        out << "score: " << club->get_points() << " | ";
        out << "GF: " << club->get_goals_scored() << " | ";
        out << "GA: " << club->get_goals_conceded() << endl;
    }
    return out.str();
}

void FutFan::team_of_the_week(int week_num)
{
    vector<string> team_of_week = {"", "", "", "", ""};
    float goalkeeper_max = 0, defender_max1 = 0, defender_max2 = 0;
    float midfielder_max = 0, forward_max = 0;
    for (Player *player : players)
    {
        if (player->find_player_score(week_num) >= goalkeeper_max && player->get_role() == GK)
        {
            goalkeeper_max = player->find_player_score(week_num);
            team_of_week[0] = player->get_name();
        }
        if (player->find_player_score(week_num) >= defender_max1 && player->get_role() == DF)
        {
            defender_max1 = player->find_player_score(week_num);
            team_of_week[1] = player->get_name();
        }
        else if (player->find_player_score(week_num) >= defender_max2 && player->get_role() == DF)
        {
            defender_max2 = player->find_player_score(week_num);
            team_of_week[2] = player->get_name();
        }
        if (player->find_player_score(week_num) >= midfielder_max && player->get_role() == MD)
        {
            midfielder_max = player->find_player_score(week_num);
            team_of_week[3] = player->get_name();
        }
        if (player->find_player_score(week_num) >= forward_max && player->get_role() == FW)
        {
            forward_max = player->find_player_score(week_num);
            team_of_week[4] = player->get_name();
        }
    }
    cout << "team of the week:" << endl
         << ROLE_NAME[0] << ": " << team_of_week[0] << " | score: " << goalkeeper_max << endl
         << ROLE_NAME[1] << "1: " << team_of_week[1] << " | score: " << defender_max1 << endl
         << ROLE_NAME[1] << "2: " << team_of_week[2] << " | score: " << defender_max2 << endl
         << ROLE_NAME[2] << ": " << team_of_week[3] << " | score: " << midfielder_max << endl
         << ROLE_NAME[3] << ": " << team_of_week[4] << " | score: " << forward_max << endl;
}

void FutFan::matchs_of_the_week(int week_num)
{
    for (Match match : all_matches[week_num - 1])
    {
        cout << match.home << SPACE << match.home_goals << " | " << match.away << SPACE << match.away_goals << endl;
    }
}