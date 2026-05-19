#include "Date.h"
#include <iostream>
#include <string>
#include <iomanip>

Date::Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {}

int Date::get_day() const {return m_day;}

int Date::get_month() const {return m_month;}

int Date::get_year() const {return m_year;}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    
    os << std::setfill('0') << std::setw(4) 
        << date.get_year() << "-" << std::setw(2) 
        << date.get_month() << "-" << std::setw(2) 
        << date.get_day() << std::setfill(' ');
    
    return os;
}