#ifndef _MOVIE_H_
#define _MOVIE_H_

#include "Item.h"
#include <string>
#include <iostream>


class Movie : public Item {
private:
    std::string m_director;
    int m_duration; // Duration in minutes
public:
    Movie(int id, std::string title, const Date &added, std::string director, int duration, Status);
    
    std::string info() const override;
    Type get_type() const override;
};

#endif