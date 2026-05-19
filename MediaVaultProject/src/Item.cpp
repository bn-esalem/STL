#include "Item.h"
#include <iostream>
#include <string>
#include <utility>

Item::Item(int id, std::string title, const Date &added, Status status)
    : m_id(id), m_title(std::move(title)), m_added(added), m_status(status) {}

int Item::get_id() const {return m_id;}

const std::string& Item::get_title() const {return m_title;}

const Date& Item::get_added_date() const {return m_added;}

Status Item::get_status() const {return m_status;}

void Item::set_status(Status status) {this-> m_status = status;}

std::ostream& operator<<(std::ostream& os, const Item &item) {
    os << item.info(); // Assuming info() returns a string representation of the item
    return os;
}

std::string status_to_string(Status status) {
    switch (status) {
        case Status::Available:
            return "Available";
        case Status::CheckedOut:
            return "CheckedOut";
        case Status::Lost:
            return "Lost";
        default:
            return "Unknown Status";
    }
}

std::string type_to_string(Type type) {
    switch (type) {
        case Type::Book:
            return "Book";
        case Type::Movie:
            return "Movie";
        case Type::Game:
            return "Game";
        default:
            return "Unknown Type";
    }
}
