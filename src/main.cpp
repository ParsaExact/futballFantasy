#include "Globalstuff.hpp"
#include "FutFan.hpp"

int main()
{
    FutFan futfan;
    futfan.get_league_data(LEAGUE_ADDRESS);
    futfan.update_week_stats(1);
    // futfan.debug();
    return 0;
}