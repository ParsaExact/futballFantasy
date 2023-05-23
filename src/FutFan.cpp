#include "FutFan.hpp"


vector<vector<string>> FutFan::make_file_lines (istringstream instream, string file_address)
{
    ifstream file(file_address);
    vector<vector<string>> lines;
    string line;
    while (getline(instream, line))
    {
        vector <string> words = split_line_into_words(line, COMMA);
        lines.push_back(words);
    }
    return lines;
}