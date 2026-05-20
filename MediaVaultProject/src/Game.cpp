#include "Game.h"
#include <utility>
#include <sstream>
#include <string>
#include <iostream>

Game::Game(int id, std::string title, const Date &added, Platform platform, Status status)
    : Item(id, std::move(title), added, status), m_platform(platform) {}

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

    oss << "[Game] " << "ID: " << get_id()
        << " \"" << get_title() << "\""
        << " | Added: " << get_added_date()
        << " | Status: " << status_to_string(get_status())
        << " | Platform: " << platform_to_string(m_platform);

    return oss.str();
} 

Type Game::get_type() const {
    return Type::Game;
}