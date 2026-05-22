#include "Book.h"

#include <iostream>
#include <sstream>
#include <string>
#include <utility>  // For std::move

Book::Book(int id, std::string title, const Date &added, std::string author, int pages)
    : Item(id, std::move(title), added), m_author(std::move(author)), m_pages(pages) {}

std::string Book::info() const {
    
    std::ostringstream oss;

    oss << "[Book] " <<"\n" << "ID: " << get_id()
        << "\nTitle: " << "\"" << get_title() << "\""
        << "\nAdded: " << get_added_date()
        << "\nStatus: " << status_to_string(get_status())
        << "\nAuthor: " << m_author
        << "\nPages: " << m_pages;

    return oss.str();
}

Type Book::get_type() const {
    return Type::Book;
}