#include "Globalstuff.hpp"
#include "FutFan.hpp"


int main()
{
    FutFan futFan;
    string line = "hello, bye, Im good ";
    for (string i : split_line_into_words(line, COMMA))
        cout << i << endl;
    return 0;
}