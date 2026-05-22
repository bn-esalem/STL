#ifndef _GAME_H_
#define _GAME_H_

#include "Item.h"
#include <string>
#include <iostream>

enum class Platform {
    PC,
    PlayStation,
    Xbox,
    NintendoSwitch,
    Mobile
};

//helper function to convert Platform enum to string for display purposes
std::string platform_to_string(Platform platform);

class Game : public Item {
private:
    Platform m_platform;
    
public:
    Game(int id, std::string title, const Date &added, Platform platform);

    std::string info() const override;
    Type get_type() const override;
    std::string serialize() const override;
};
#endif