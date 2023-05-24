#ifndef _GLOBALSTUFF_HPP_
#define _GLOBALSTUFF_HPP_

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<dirent.h>
#include<sstream>
#include<map>
#include "Exception.hpp"


using namespace std;


enum ROLE { GK, DF, MD, FW};


const string ROLE_NAME[] = {"GoalKeeper", "Defender", "Midfielder", "Forward"};
const string ROLE_ABB_NAME[] = {"gk", "df", "md", "fw"};

const char COMMA = ',';
const char NAME_DELIM = ';';

const int JUNK_LINE = 0;
const int ROLE_CNT = 4;
const int GK_CNT = 1;
const int DF_CNT = 2;
const int MD_CNT = 1;
const int FW_CNT = 1;
const string LEAGUE_ADDRESS = "data/premier_league.csv";
const string WEEK_STATS_FOLDER = "data/week_stats";

vector <string> split_line_into_words(string line, char delimiter);

int find_int_pos(string position);

#endif