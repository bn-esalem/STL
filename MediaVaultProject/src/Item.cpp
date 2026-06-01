#include "Item.h"
#include <iostream>
#include <string>
#include <utility>  // for move
#include <stdexcept>

/*Use std::move when:
you own the object now
you won’t use it again
moving is cheaper than copying*/

Item::Item(int id, string title, const Date &added, Status status)
    : m_id(id), m_title(std::move(title)),
     m_added(added), m_status(status) {}

int Item::get_id() const {return m_id;}

const string& Item::get_title() const {return m_title;}

const Date& Item::get_added_date() const {return m_added;}

Status Item::get_status() const {return m_status;}

void Item::set_status(Status status) {m_status = status;}

std::ostream& operator<<(std::ostream& os, const Item &item) {
    // Assuming info() returns a string representation of the item
    os << item.info();
    return os;
}

string status_to_string(Status status) {
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

Status status_from_string(const std::string& str){

    if(str == "Available"){
        return Status::Available;
    }
    else if(str == "CheckedOut"){
        return Status::CheckedOut;
    }
    else if(str == "Lost"){
        return Status::Lost;
    }

    throw std::runtime_error("Unknown status: "+str);
}

string type_to_string(Type type) {
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

Type type_from_string(const string& str){
    if (str == "Book"){
        return Type::Book;
    }
    else if (str == "Movie"){
        return Type::Movie;
    }
    else if (str == "Game"){
        return Type::Game;
    }

    throw std::runtime_error("Unknown type: " + str);
}
