#ifndef _BOOK_H_
#define _BOOK_H_

#include "Item.h"
#include<iostream>
#include <string>

using std::string;

class Book: public Item
{
private:
    string m_author;
    int m_pages;
public:
    Book(int id, string title, const Date& added, string author, int pages);

    string info() const override;
    Type get_type() const override;
    string serialize() const override;
};

#endif