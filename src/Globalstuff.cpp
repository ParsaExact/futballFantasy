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

int find_int_pos(string position)
{
    for (int i = 0; i < POS_CNT; ++i)
        if (POS_NAME[i] == position || POS_ABB_NAME[i] == position)
            return i;
    // throw not found position error
}