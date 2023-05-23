#include "Globalstuff.hpp"

vector <string> split_line_into_words(string line, char delimiter)
{
    istringstream str_line(line);
    string word;
    vector <string> words;
    while (getline(str_line, word, delimiter)){
        words.push_back(word);
    }
    return words;
}