#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<dirent.h>
#include<sstream>

using namespace std;

const string DONE="OK";
const string BAD_COMMAND = "Bad Request";
const string PERMISSION_DENIED = "Permission Denied";
const string NOT_FOUND = "Not Found";
const string EMPTY_COMMAND = "Empty";

const string POST = "POST";
const string GET = "GET";
const string PUT = "PUT";
const string DELETE = "DELETE";

const string LEAUGE_ADDRESS = "./data/premier_league.csv";
const string WEEK_STATS_FOLDER = "./data/week_stats";