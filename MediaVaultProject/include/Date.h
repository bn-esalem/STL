#ifndef _DATE_H_
#define _DATE_H_

#include <string>
#include <iostream>

class Date
{
    friend std::ostream& operator<<(std::ostream& os, const Date &date);
private:
    int m_day;
    int m_month;
    int m_year;
public:
    Date(int d, int m, int y);

    int get_day() const;
    int get_month() const;
    int get_year() const;

    std::string to_string() const;
    ~Date () = default;    
};
#endif