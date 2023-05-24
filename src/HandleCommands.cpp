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
    while (getline(cin, line))
    {
        vector<string> command_words = split_line_into_words(line, SPACE);
        string command = command_words[1];
        if (command == "team_of_the_week")
        {
            if (command_words.size() == 5)
            {
                if (stoi(command_words[4]) > cur_week)
                {
                    cout << BadRequest().out() << endl;
                    continue;
                }
                futfan.team_of_the_week(stoi(command_words[4]));
            }
            futfan.team_of_the_week(cur_week);
        }
        if (command == "league_standings")
            cout << futfan.output_standing();
    //     if (command == "players")
    //     {
    //         string role = "";
    //         string team_name =  convert_underline_to_space(command_words[4]);
    //         Club* club = futfan.find_club_by_name(team_name); //check not found
    //         bool ranked = false , with_position = false;
    //         if(command_words.back() == "rank")
    //             ranked = true;
    //         if(command_words.size() == 7 || (command_words.size() == 6 && !ranked))
    //             for(int i = 0 ; i < ROLE_CNT ; ++i)
    //                 if(ROLE_ABB_NAME[i] == command_words[5])
    //                     role = command_words[5];
    //         if(role != "")
    //             with_position = true;
    //             //bad request
    //         vector<Player*> club_players = club->players[ROLE_CNT];
    //         if(ranked)
    //             for(int i = 0 ; i<club_players.size() ; ++i)
    //             {
    //                 for(int j = i+1 ; j < club_players.size() ; ++j)
    //                     if(club_players[i].)
    //             }
    //     }
            if(command == "matches_result_league")
            {
                if(command_words.size() == 5){
                    if(stoi(command_words[4]) > cur_week)
                    {
                        //bad request
                        continue;
                    }
                    futfan.matchs_of_the_week(stoi(command_words[4]));
                    continue;
                }
                futfan.matchs_of_the_week(cur_week);
                //handle not found somehow
            }
    }
}