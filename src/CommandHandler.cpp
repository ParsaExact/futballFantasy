#include "CommandHandler.hpp"

CommandHandler::CommandHandler(FutFan *futfan_)
{
    futfan = futfan_;
    session = new Session();
}

int CommandHandler::find_command_num(vector<string> command_words)
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

string CommandHandler::signup_user(vector<string> command)
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

string CommandHandler::login_user(vector<string> command)
{
    if ((int)command.size() != 7 || command[2] != "?" || command[3] != "team_name" || command[5] != "password")
        return BAD_REQUEST;
    string team_name = command[4];
    string password = command[6];
    if (session->is_admin_logged_in || session->is_user_logged_in)
        return PERMISSION_DENIED;
    try
    {
        session->login_user(team_name, password);
    }
    catch (NotFound &err)
    {
        return err.out();
    }
    catch (PermissionDenied &err)
    {
        return err.out();
    }
    return OK;
}

string CommandHandler::logout_user(vector<string> command)
{
    if ((int)command.size() != 2)
        return BAD_REQUEST;
    if (!session->is_admin_logged_in && !session->is_user_logged_in)
        return PERMISSION_DENIED;
    session->logout_user();
    return OK;
}

string CommandHandler::register_admin(vector<string> command)
{
    if ((int)command.size() != 7 || command[2] != "?" || command[3] != "username" || command[5] != "password")
        return BAD_REQUEST;
    string username = command[4];
    string password = command[6];
    if (session->is_admin_logged_in || session->is_user_logged_in)
        return PERMISSION_DENIED;
    try
    {
        session->register_admin(username, password);
    }
    catch (BadRequest &err)
    {
        return err.out();
    }
    return OK;
}

string CommandHandler::close_transfer_window(vector<string> command)
{
    if ((int)command.size() != 2)
        return BAD_REQUEST;
    try
    {
        session->close_transfer_window();
    }
    catch (PermissionDenied &err)
    {
        return err.out();
    }
    return OK;
}

string CommandHandler::open_transfer_window(vector<string> command)
{
    if ((int)command.size() != 2)
        return BAD_REQUEST;
    try
    {
        session->open_transfer_window();
    }
    catch (PermissionDenied &err)
    {
        return err.out();
    }
    return OK;
}

string CommandHandler::get_league_standing(vector<string> command)
{
    if ((int)command.size() != 2)
        return BAD_REQUEST;
    return futfan->output_standing();
}

string CommandHandler::get_team_of_the_week(vector<string> command)
{
    bool with_week_num = false;
    if ((int)command.size() == 3)
        if (command[2] != "?")
            return BAD_REQUEST;
        else if ((int)command.size() == 5)
        {
            with_week_num = true;
            if (command[2] != "?" || command[3] != "week_num")
                return BAD_REQUEST;
        }
        else
            return BAD_REQUEST;
    if (with_week_num)
        if (stoi(command[4]) > session->current_week_num)
            return BAD_REQUEST;
    if (with_week_num)
        return futfan->team_of_the_week(stoi(command[4]));
    return futfan->team_of_the_week(session->current_week_num);
}

string CommandHandler::get_players(vector<string> command)
{
    try
    {
        string role = "";
        string team_name = convert_underline_to_space(command[4]);
        bool ranked = false, with_position = false;
        int role_num = -1;
        if (command.back() == "ranks")
            ranked = true;
        if (command[2] != "?" || command[3] != "team_name")
            return BAD_REQUEST;
        if ((int)command.size() == 7 && !ranked)
            return BAD_REQUEST;
        if ((int)command.size() == 7 || ((int)command.size() == 6 && !ranked))
            for (int i = 0; i < ROLE_CNT; ++i)
                if (ROLE_ABB_NAME[i] == command[5])
                {
                    role_num = i;
                    role = command[5];
                }
        if ((int)command.size() == 5 || ranked)
            role = "no roles";
        if (role == "")
            return BAD_REQUEST;
        else
            with_position = true;
        Club *club = futfan->find_club_by_name(team_name);
        return futfan->output_players(ranked, role_num, club);
    }
    catch (NotFound &not_found)
    {
        return NOT_FOUND;
    }
    catch (BadRequest &bad)
    {
        return BAD_REQUEST;
    }
}

string CommandHandler::get_match_results(vector<string> command)
{
    bool with_week_num = false;
    if ((int)command.size() == 3)
        if(command[2] != "?")
            return BAD_REQUEST;
    if ((int)command.size() == 5){
        with_week_num = true;
        if(command[2] != "?" || command[3] != "week_num")
            return BAD_REQUEST;
        if(stoi(command[4]) > session->current_week_num)
            return BAD_REQUEST;
    }
    if(with_week_num)
        return futfan->matchs_of_the_week(stoi(command[4]));
    return futfan->matchs_of_the_week(session->current_week_num);
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
        }
        catch (BadRequest &err)
        {
            cout << err.out() << endl;
            continue;
        }

        if (command_num == SIGNUP)
            cout << signup_user(command_words) << endl;

        if (command_num == LOGIN)
            cout << login_user(command_words) << endl;

        if (command_num == LOGOUT)
            cout << logout_user(command_words) << endl;

        if (command_num == REGISTER_ADMIN)
            cout << register_admin(command_words) << endl;

        if (command_num == OPEN_TRANSFER_WINDOW)
            cout << open_transfer_window(command_words) << endl;

        if (command_num == CLOSE_TRANSFER_WINDOW)
            cout << close_transfer_window(command_words) << endl;

        if (command_num == LEAGUE_STANDINGS)
            cout << get_league_standing(command_words);

        if (command_num == TEAM_OF_THE_WEEK)
        {
            cout << get_team_of_the_week(command_words) << endl;
        }
        if (command_num == PLAYERS)
        {
            cout << get_players(command_words) << endl;
        }
        if (command_num == MATCHES_RESULT_LEAGUE)
        {
            cout << get_match_results(command_words) << endl;
        } /*
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
