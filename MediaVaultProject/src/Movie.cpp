#include "Movie.h"

#include <utility>
#include <sstream>
#include <string>
#include <iostream>

Movie::Movie(int id, std::string title, const Date &added, std::string director, int duration)
    : Item(id, std::move(title), added), m_director(std::move(director)), m_duration(duration) {}

std::string Movie::info() const {
    
    std::ostringstream oss;

    oss << "[Movie] " << "\nID: " << get_id()
        << "\nTitle: "<< "\"" << get_title() << "\""
        << "\nAdded: " << get_added_date()
        << "\nStatus: " << status_to_string(get_status())
        << "\nDirector: " << m_director
        << "\nDuration: " << m_duration << " minutes";

    return oss.str();
}

Type Movie::get_type() const {
    return Type::Movie;
}

std::string Movie::serialize() const{
    
    std::ostringstream oss;
    
    oss << "Movie,"
        << get_id() << ","
        << get_title() << ","
        << get_added_date().date_to_string() << ","
        << status_to_string(get_status()) << ","
        << m_director << ","
        << m_duration;
    
    return oss.str();
}