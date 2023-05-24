#include "Globalstuff.hpp"
#include "FutFan.hpp"

int main()
{
    FutFan futfan;
    futfan.get_league_data(LEAGUE_ADDRESS);
    // futfan.debug();
    return 0;
}