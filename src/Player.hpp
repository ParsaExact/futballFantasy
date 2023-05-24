#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Globalstuff.hpp"

class Player {
public:
    Player (string _name, int _role);
    string get_name();
    int get_role();
    void debug(){
        cout << "Player name: " << name << " and plays in " << ROLE_NAME[role] << endl;
    };
private:
    string name;
    int role;
};

#endif