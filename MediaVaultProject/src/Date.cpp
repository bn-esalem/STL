#include "Date.h"
#include <iostream>
#include <string>
#include <iomanip>

Date::Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {}

int Date::get_day() const {return m_day;}

int Date::get_month() const {return m_month;}

int Date::get_year() const {return m_year;}

std::string Date::date_to_string() const{
    
    std::ostringstream oss;
    
    oss << std::setfill('0') << std::setw(4) 
        << get_year() << "-" << std::setw(2) 
        << get_month() << "-" << std::setw(2) 
        << get_day();
    
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    
    return os << date.date_to_string();
}