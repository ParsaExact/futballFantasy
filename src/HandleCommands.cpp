#include "HandleCommands.hpp"
#include "Globalstuff.hpp"
#include "FutFan.hpp"
#include "Exception.hpp"
void HandleCommands::get_commands()
{
    FutFan futfan;
    futfan.get_league_data(LEAGUE_ADDRESS);
    futfan.update_week_stats(1);
    string line;
    int cur_week = 1;
    bool admin_signed_in = false, transfer_window = false;
    Team *cur_team = NULL;
    while (getline(cin, line))
    {
        vector<string> command_words = split_line_into_words(line, SPACE);
        string command = command_words[1];
        if (command == "team_of_the_week")
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
        if (command == "players") //not completed
        {
            try
            {
                string role = "";
                string team_name = convert_underline_to_space(command_words[4]);
                Club *club = futfan.find_club_by_name(team_name);
                bool ranked = false, with_position = false;
                if (command_words.back() == "rank")
                    ranked = true;
                if (command_words.size() == 7 || (command_words.size() == 6 && !ranked))
                    for (int i = 0; i < ROLE_CNT; ++i)
                        if (ROLE_ABB_NAME[i] == command_words[5])
                            role = command_words[5];
                if (role == "")
                    throw BadRequest();
                with_position = true;
                vector<Player *> club_players = club->players[ROLE_CNT];
                // if(ranked)
                //     for(int i = 0 ; i<club_players.size() ; ++i)
                //     {
                //         for(int j = i+1 ; j < club_players.size() ; ++j)
                //             if(club_players[i].)
                //     }
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
    }
}