#include "Movie.h"

#include <utility>
#include <sstream>
#include <string>
#include <iostream>

Movie::Movie(int id, std::string title, const Date &added, std::string director, int duration, Status status)
    : Item(id, std::move(title), added, status), m_director(std::move(director)), m_duration(duration) {}

std::string Movie::info() const {
    
    std::ostringstream oss;

    oss << "[Movie] " << "ID: " << get_id()
        << " \"" << get_title() << "\""
        << " | Added: " << get_added_date()
        << " | Status: " << status_to_string(get_status())
        << " | Director: " << m_director
        << " | Duration: " << m_duration << " minutes";

    return oss.str();
}

Type Movie::get_type() const {
    return Type::Movie;
}