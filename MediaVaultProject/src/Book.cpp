#include "Book.h"

#include <iostream>
#include <sstream>
#include <string>
#include <utility>  // For std::move

Book::Book(int id, std::string title, const Date &added, std::string author, int pages)
    : Item(id, std::move(title), added), m_author(std::move(author)), m_pages(pages) {}

std::string Book::info() const {
    
    std::ostringstream oss;

    oss << "[Book] " << "ID: " << get_id()
        << " \"" << get_title() << "\""
        << " | Added: " << get_added_date()
        << " | Status: " << status_to_string(get_status())
        << " | Author: " << m_author
        << " | Pages: " << m_pages;

    return oss.str();
}

Type Book::get_type() const {
    return Type::Book;
}