#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>

class Date
{
    friend std::ostream& operator<<(std::ostream& os, const Date &date);
private:
    int m_day;
    int m_month;
    int m_year;
public:
    Date(int day, int month, int year);

    int get_day() const;
    int get_month() const;
    int get_year() const;

    std::string date_to_string() const;

    ~Date () = default;    
};
#endif