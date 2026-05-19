#include "Item.h"
#include <iostream>
#include <string>

Item::Item(int id, const std::string &title, const Date &release_date, ItemType type, ItemStatus status)
    : id(id), title(title), release_date(release_date), type(type), status(status) {}

int Item::get_id() const {
    return id;
}

const std::string& Item::get_title() const {
    return title;
}

const Date& Item::get_release_date() const {
    return release_date;
}

Item::ItemType Item::get_type() const {
    return type;
}

Item::ItemStatus Item::get_status() const {
    return status;
}

void Item::set_status(ItemStatus status) {
    this->status = status;
}

std::string Item::to_string() const {
    return "Item: " + title;
}
