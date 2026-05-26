#ifndef _BOOK_H_
#define _BOOK_H_

#include "Item.h"
#include<iostream>
#include <string>

class Book: public Item
{
private:
    std::string m_author;
    int m_pages;
public:
    Book(int id, std::string title, const Date &added, std::string author, int pages);

    std::string info() const override;
    Type get_type() const override;
    std::string serialize() const override;
};

#endif