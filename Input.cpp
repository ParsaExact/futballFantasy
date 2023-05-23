#include "Globalstuff.hpp"

vector<string> split_words(string line, char del)
{
    vector<string> words_in_line;
    istringstream words(line);
    string word;
    while (getline(words, word, del)){
        words_in_line.push_back(word);
    }
    return words_in_line;
}

vector<string> read_from_file(string filename)
{
    vector<string> lines;
    string line;
    ifstream myfile(filename);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            lines.push_back(line);
        }
        myfile.close();
    }
    return lines;
}

vector<string> get_week_stats(string filename, int index)
{
    vector<string> week = read_from_file(filename + to_string(index));
    return week;
}