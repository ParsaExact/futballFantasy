#include "CommandHandler.hpp"

CommandHandler::CommandHandler(FutFan* futfan_)
{
    futfan = futfan_;
    session = new Session();
}

int CommandHandler::find_command_num(vector <string> command_words)
{
    if ((int)command_words.size() < 2)
        throw BadRequest();
    int cnt = 0;
    for (CommandType cmd : COMMAND_TYPE)
    {
        if (cmd.command_class == command_words[0] && cmd.command_type == command_words[1])
            return cnt;
        cnt++;
    }
    throw BadRequest();
}

void CommandHandler::print_players(vector<Player*> club_players)
{
    cout << "list of players:" <<endl;
    for(int i = 0 ; i < club_players.size() ; ++i)
        cout << i << ". name: " << club_players[i]->get_name() << " | role: " << club_players[i]->get_role() << " | score: " << club_players[i]->calculate_avarage_score() << endl;
}

string CommandHandler::signup_user(vector <string> command)
{
    if ((int)command.size() != 7 || command[2] != "?" || command[3] != "team_name" || command[5] != "password")
        return BAD_REQUEST;
    string team_name = command[4];
    string password = command[6];
    if (session->is_admin_logged_in || session->is_user_logged_in)
        return PERMISSION_DENIED;
    if (!session->is_username_available(team_name))
        return BAD_REQUEST;
    session->add_user(team_name, password, futfan->add_team(team_name));
    return OK;
}

void CommandHandler::handle_commands()
{
    string line;
    while (getline(cin, line))
    {
        vector<string> command_words = split_line_into_words(line, SPACE);
        int command_num;
        try
        {
            command_num = find_command_num(command_words);
        } catch(BadRequest& err) {
            cout << err.out() << endl;
            continue;
        }

        if (command_num == SIGNUP)
        {
            cout << signup_user(command_words) << endl;
        }

        /*if (command == "team_of_the_week")
        {
            if (command_words.size() == 5)
            {
                try
                {
                    if (stoi(command_words[4]) > cur_week)
                        throw BadRequest();
                    futfan.team_of_the_week(stoi(command_words[4]));
                }
                catch (BadRequest &bad)
                {
                    cout << bad.out();
                }
            }
            futfan.team_of_the_week(cur_week);
        }
        if (command == "league_standings")
            cout << futfan.output_standing();
        if (command == "players") // not completed
        {
            try
            {
                string role = "";
                string team_name = convert_underline_to_space(command_words[4]);
                Club *club = futfan.find_club_by_name(team_name);
                bool ranked = false, with_position = false;
                if (command_words.back() == "rank"){
                    ranked = true;
                }
                if (command_words.size() == 7 || (command_words.size() == 6 && !ranked))
                    for (int i = 0; i < ROLE_CNT; ++i)
                        if (ROLE_ABB_NAME[i] == command_words[5])
                            role = command_words[5];
                if(command_words.size() == 5 || ranked)
                    role = "no roles";
                if (role == "")
                    throw BadRequest();
                else
                {
                    with_position = true;
                }
                vector<Player *> club_players = club->players[ROLE_CNT];
                if (ranked)
                    for (int i = 0; i < club_players.size(); ++i)
                    {
                        for (int j = i + 1; j < club_players.size(); ++j)
                        {
                            if (club_players[i]->calculate_avarage_score() > club_players[i]->calculate_avarage_score())
                                swap(club_players[i], club_players[j]);
                            else if (club_players[i]->calculate_avarage_score() == club_players[i]->calculate_avarage_score() && club_players[i]->get_name() > club_players[j]->get_name())
                                swap(club_players[i], club_players[j]);
                        }
                    }
                if (with_position)
                    for (int i = 0; i < club_players.size(); ++i)
                        if (ROLE_ABB_NAME[club_players[i]->get_role()] != command_words[5])
                        {
                            club_players.erase(club_players.begin() + i);
                            i--;
                        }
                print_players(club_players);
            }
            catch (NotFound &not_found)
            {
                cout << not_found.out() << endl;
            }
            catch (BadRequest &bad)
            {
                cout << bad.out() << endl;
            }
        }
        if (command == "matches_result_league")
        {
            if (command_words.size() == 5)
            {
                try
                {
                    if (stoi(command_words[4]) > cur_week)
                    {
                        throw BadRequest();
                        continue;
                    }
                }
                catch (BadRequest &bad)
                {
                    cout << bad.out() << endl;
                }
                futfan.matchs_of_the_week(stoi(command_words[4]));
                continue;
            }
            futfan.matchs_of_the_week(cur_week);
            // handle not found somehow
        }
        if (command == "register_admin")
        {
            try
            {
                if (command_words[4] != ADMIN_USER_NAME || command_words[6] != ADMIN_PASSWORD)
                {
                    throw BadRequest();
                }
                cout << "OK" << endl;
                admin_signed_in = true;
            }
            catch (BadRequest &bad)
            {
                cout << bad.out() << endl;
            }
        }
        if (command == "logout")
        {
            try
            {
                if (!admin_signed_in)
                    throw PermissionDenied();
                admin_signed_in = false;
                cout << "OK" << endl;
            }
            catch (PermissionDenied &permission)
            {
                cout << permission.out() << endl;
            }
        }
        if (command == "signup")
        {
            try
            {
                if (futfan.check_team(command_words[4]))
                    throw BadRequest();
                futfan.update_team(command_words[4], command_words[6]);
                cout << "OK" << endl;
            }
            catch (BadRequest &bad)
            {
                cout << bad.out() << endl;
            }
        }
        if (command == "login")
        {
            try
            {
                Team *team = futfan.find_team_by_name(command_words[4]);
                if (team->get_team_password() != command_words[6])
                    throw PermissionDenied();
                cur_team = team;
            }
            catch (NotFound &not_found)
            {
                cout << not_found.out() << endl;
            }
            catch (PermissionDenied &permission_denied)
            {
                cout << permission_denied.out() << endl;
            }
        }
        if (command == "pass_week")
        {
            try
            {
                if (!admin_signed_in)
                    throw PermissionDenied();
                cur_week++;
                cout << "OK" << endl;
            }
            catch (PermissionDenied &permission)
            {
                cout << permission.out() << endl;
            }
        }
        if (command == "close_transfer_window")
        {
            try
            {
                if (!admin_signed_in)
                    throw PermissionDenied();
                transfer_window = false;
                cout << "OK" << endl;
            }
            catch (PermissionDenied &permission)
            {
                cout << permission.out() << endl;
            }
        }
        if (command == "open_transfer_window")
        {
            try
            {
                if (!admin_signed_in)
                    throw PermissionDenied();
                transfer_window = true;
                cout << "OK" << endl;
            }
            catch (PermissionDenied &permission)
            {
                cout << permission.out() << endl;
            }
        }
        // if (command == "sell_player")
        // {
        //     cur_team
        // }
        */
    }
}
