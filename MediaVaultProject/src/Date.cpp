#include "Date.h"
#include <iostream>
#include <string>

Date::Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {}

int Date::get_day() const {
    return m_day;
}

int Date::get_month() const {
    return m_month;
}

int Date::get_year() const {
    return m_year;
}
std::string Date::to_string() const {
    return std::to_string(m_day) + "/" + std::to_string(m_month) + "/" + std::to_string(m_year);
}
std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << date.to_string();
    return os;
}