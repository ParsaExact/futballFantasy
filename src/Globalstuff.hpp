#ifndef _GLOBALSTUFF_HPP_
#define _GLOBALSTUFF_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <dirent.h>
#include <sstream>
#include <map>
#include <algorithm>
#include "Exception.hpp"


using namespace std;


enum ROLE { GK, DF, MD, FW};
enum WEEK_INFO { MATCH, RESULT, INJURED, YELLOW_CARD, RED_CARD, SCORES};


const string ROLE_NAME[] = {"GoalKeeper", "Defender", "Midfielder", "Forward"};
const string ROLE_ABB_NAME[] = {"gk", "df", "md", "fw"};

const char COMMA = ',';
const char SPACE = ' ';
const char NAME_DELIM = ';';
const char SCORE_DELIM = ':';

const int RED_CARD_SUS_DAYS = 1;
const int YELLOW_CARD_SUS_DAYS = 1;
const int INJURY_SUS_DAYS = 3;
const int JUNK_LINE = 0;
const int ROLE_CNT = 4;
const int GK_CNT = 1;
const int DF_CNT = 2;
const int MD_CNT = 1;
const int FW_CNT = 1;
const int DRAW_POINT = 1;
const int WIN_POINT = 3;
const int LOSS_POINT = 0;
const string LEAGUE_ADDRESS = "data/premier_league.csv";
const string WEEK_STATS_FOLDER = "data/weeks_stats/";
const string ADMIN_USER_NAME = "admin";
const string ADMIN_PASSWORD = "123456";

vector <string> split_line_into_words(string line, char delimiter);

int find_int_role(string position);

string convert_underline_to_space(string team);
#endif