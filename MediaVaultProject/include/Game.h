#ifndef _GAME_H_
#define _GAME_H_

#include "Item.h"
#include <string>
#include <iostream>

using std::string;

enum class Platform {
    PC,
    PlayStation,
    Xbox,
    NintendoSwitch,
    Mobile
};

//helper function to convert Platform enum to string for display purposes
string platform_to_string(Platform platform);
Platform platform_from_string(const string& str);

class Game : public Item {
private:
    Platform m_platform;
    
public:
    Game(int id, string title, const Date& added, Platform platform);

    string info() const override;
    Type get_type() const override;
    string serialize() const override;
};

#endif