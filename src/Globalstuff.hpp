#ifndef _GLOBALSTUFF_HPP_
#define _GLOBALSTUFF_HPP_

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<dirent.h>
#include<sstream>

using namespace std;


const char COMMA = ',';

const string LEAGUE_ADDRESS = "../data/premier_league.csv";
const string WEEK_STATS_FOLDER = "../data/week_stats";

vector <string> split_line_into_words(string line, char delimiter);

#endif