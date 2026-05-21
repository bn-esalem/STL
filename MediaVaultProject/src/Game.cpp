#include "Game.h"
#include <utility>
#include <sstream>
#include <string>
#include <iostream>

Game::Game(int id, std::string title, const Date &added, Platform platform)
    : Item(id, std::move(title), added), m_platform(platform) {}

// Helper function to convert Platform enum to string for display purposes
std::string platform_to_string(Platform platform) {
    switch (platform) {
        case Platform::PC: return "PC";
        case Platform::PlayStation: return "PlayStation";
        case Platform::Xbox: return "Xbox";
        case Platform::NintendoSwitch: return "NintendoSwitch";
        case Platform::Mobile: return "Mobile";
        default: return "Unknown";
    }
}

std::string Game::info() const {
    
    std::ostringstream oss;

    oss << "[Game] " << "\nID: " << get_id()
        << "\nTitle: "<< " \"" << get_title() << "\""
        << "\nAdded: " << get_added_date()
        << "\nStatus: " << status_to_string(get_status())
        << "\nPlatform: " << platform_to_string(m_platform);

    return oss.str();
} 

Type Game::get_type() const {
    return Type::Game;
}