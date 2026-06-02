#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>

using std::string;

class Date
{
    friend std::ostream& operator<<(std::ostream& os, const Date &date);
private:
    int m_day;
    int m_month;
    int m_year;
    
    static bool is_leap_year(int year);
    static int days_in_month(int month, int year);
public:
    Date(int day, int month, int year);

    int get_day() const;
    int get_month() const;
    int get_year() const;

    string date_to_string() const;
    static Date date_from_string(const string& str);

    bool operator==(const Date &rhs) const;
    bool operator<(const Date &rhs) const; // used for sorting by date (ascending or descending)

    ~Date () = default;    
};
#endif