#include "Date.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

Date::Date(int day, int month, int year) 
    : m_day(day), m_month(month), m_year(year) {}

int Date::get_day() const {return m_day;}

int Date::get_month() const {return m_month;}

int Date::get_year() const {return m_year;}

static bool is_leap_year(int year){
    return ((year % 4 == 0 && year % 100 != 0) ||
            (year % 400 == 0));
}

static int days_in_month(int month, int year){
    switch (month){
        case 1: return 31;
        case 2: return is_leap_year(year) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
    
        default: return 0;
    }
}

std::string Date::date_to_string() const{
    
    std::ostringstream oss;
    
    oss << std::setfill('0') << std::setw(4) 
        << get_year() << "-" << std::setw(2) 
        << get_month() << "-" << std::setw(2) 
        << get_day();
    
    return oss.str();
}

Date Date::date_from_string(const std::string &str){

    std::istringstream iss(str);
    int year{}, month{}, day{};
    char dash1{}, dash2{};

    if (! (iss >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-'){
        throw std::runtime_error("Invalid date format. Use YYYY-MM-DD.");
    }
    if (month < 1 || month > 12){
        throw std::runtime_error("Invalid month. Please enter a value between 1 and 12.");
    }

    int max_day = days_in_month(month, year);
    if (day < 1 || day > 31){
        throw std::runtime_error("Invalid day for the given month/year. Maximum day is " + std::to_string(max_day) + ".");
    }

    return Date(day, month, year);
}


std::ostream& operator<<(std::ostream& os, const Date& date){
    
    return os << date.date_to_string();
}

bool Date::operator==(const Date& rhs) const {
    return get_year() == rhs.get_year() &&
           get_month() == rhs.get_month() &&
           get_day() == rhs.get_day();
}

bool Date::operator<(const Date &rhs) const{
    if (m_year != rhs.m_year){
        return m_year < rhs.m_year;
    }
    if (m_month != rhs.m_month){
        return m_month < rhs.m_month;
    }
    return m_day < rhs.m_day;
}

