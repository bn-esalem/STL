#ifndef _MOVIE_H_
#define _MOVIE_H_

#include "Item.h"
#include <string>
#include <iostream>

using std::string;

class Movie : public Item {
private:
    string m_director;
    int m_duration; // Duration in minutes
public:
    Movie(int id, string title, const Date& added, string director, int duration);
    
    string info() const override;
    Type get_type() const override;
    string serialize() const override;
};

#endif