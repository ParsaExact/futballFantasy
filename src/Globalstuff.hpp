#ifndef _GLOBALSTUFF_HPP_
#define _GLOBALSTUFF_HPP_

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<dirent.h>
#include<sstream>
#include<map>

using namespace std;


enum POS { GK, DF, MD, FW};


const string POS_NAME[] = {"GoalKeeper", "Defender", "Midfielder", "Forward"};
const string POS_ABB_NAME[] = {"gk", "df", "md", "fw"};

const char COMMA = ',';

const int POS_CNT = 4;
const int GK_CNT = 1;
const int DF_CNT = 2;
const int MD_CNT = 1;
const int FW_CNT = 1;
const string LEAGUE_ADDRESS = "../data/premier_league.csv";
const string WEEK_STATS_FOLDER = "../data/week_stats";

vector <string> split_line_into_words(string line, char delimiter);

int find_int_pos(string position);

#endif