#include "Game.h"
#include <utility>
#include <sstream>
#include <string>
#include <iostream>

Game::Game(int id, string title, const Date& added, Platform platform)
    : Item(id, std::move(title), added), m_platform(platform) {}

// Helper function to convert Platform enum to string for display purposes
string platform_to_string(Platform platform) {
    switch (platform) {
        case Platform::PC: return "PC";
        case Platform::PlayStation: return "PlayStation";
        case Platform::Xbox: return "Xbox";
        case Platform::NintendoSwitch: return "NintendoSwitch";
        case Platform::Mobile: return "Mobile";
        default: return "Unknown";
    }
}

Platform platform_from_string(const string& str){
    if (str == "PC"){
        return Platform::PC;
    }
    else if (str == "PlayStation") {
        return Platform::PlayStation;
    }
    else if (str == "Xbox") {
        return Platform::Xbox;
    }
    else if (str == "NintendoSwitch") {
        return Platform::NintendoSwitch;
    }
    else if (str == "Mobile") {
        return Platform::Mobile;
    }
    throw std::runtime_error("Unknown platform: " + str);
}

string Game::info() const {   
    std::ostringstream oss;
    oss << "[Game]\n" 
        << "ID: " << get_id()
        << "\nTitle: \"" << get_title() << "\""
        << "\nAdded: " << get_added_date()
        << "\nStatus: " << status_to_string(get_status())
        << "\nPlatform: " << platform_to_string(m_platform);
    return oss.str();
} 

Type Game::get_type() const {
    return Type::Game;
}

string Game::serialize() const{
    std::ostringstream oss;   
    oss << "Game,"
        << get_id() << ","
        << get_title() << ","
        << get_added_date().date_to_string() << ","
        << status_to_string(get_status()) << ","
        << platform_to_string(m_platform);    
    return oss.str();
}