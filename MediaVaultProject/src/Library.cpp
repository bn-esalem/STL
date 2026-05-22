#include "Library.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <cstddef>

// small helper function
static std::string string_to_lower(std::string str){
    for(char &c: str){
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return str;
}

void Library::add_item(std::unique_ptr<Item> item) {
    if(!item) {
        throw LibraryError("Cannot add a null item to the library.");
    }

    if(find_item(item->get_id()) != nullptr) {
        throw LibraryError("Duplicate item with ID " + std::to_string(item->get_id()) + " already exists.");
    }

    m_items.push_back(std::move(item));
}

void Library::remove_item(int id) {

    const auto old_size = m_items.size();

    auto it = std::remove_if(m_items.begin(), m_items.end(),
              [id](const std::unique_ptr<Item>& item) 
              { return item->get_id() == id; });
    
    m_items.erase(it, m_items.end());
    
    if(m_items.size() == old_size) {
        throw NotFoundError("Item with ID " + std::to_string(id) + " not found.");
    }
}

Item* Library::find_item(int id) {
    auto it = std::find_if(m_items.begin(), m_items.end(),
              [id](const std::unique_ptr<Item>& item) 
              { return item->get_id() == id; });
    
    if (it != m_items.end()){
        return it->get();
    }
    else {
        return nullptr;
    }
}

const Item* Library::find_item(int id) const {
    auto it = std::find_if(m_items.begin(), m_items.end(),
              [id](const std::unique_ptr<Item>& item) 
              { return item->get_id() == id; });
    
    if (it != m_items.end()){
        return it->get();
    }
    else {
        return nullptr;
    }
}

void Library::search_by_title(std::string &keyword){

    if(keyword.empty()){
        std::cout << "Keyword is empty!\n";
        return;
    }
    
    const std::string word = string_to_lower(keyword);
    bool found = false;

    for(const auto &item: m_items){
        const std::string title = string_to_lower(item->get_title());
        if(title.find(word) != std::string::npos){
            std::cout << *item << std::endl;
            found = true;
        }
    }

    if(!found){
        std::cout << "No matches." << std::endl;
    } 
}

void Library::checkout_item(int id){
    Item *item = find_item(id);

    if(!item){
        throw NotFoundError("Item with ID: " + std::to_string(id) + " not found.");
    }

    if(item->get_status() != Status::Available){
        throw InvalidOperationError("Item with ID: " + std::to_string(id) + " is not available for checkout.");
    }

    item->set_status(Status::CheckedOut);

}

void Library::return_item(int id){
    Item *item = find_item(id);

    if(!item){
        throw NotFoundError("Item with ID: " + std::to_string(id) + " not found.");
    }

    if(item->get_status() != Status::CheckedOut){
        throw InvalidOperationError("Item with ID: " + std::to_string(id) + " is not currently checked out.");
    }

    item->set_status(Status::Available);
}

void Library::list_all_items() const {
    if (m_items.empty()) {
        std::cout << "No items in the library.\n";
        return;
    }
    for (const auto& item : m_items) {
        std::cout << *item << "\n"; // Using overloaded operator<< for Item
        std::cout << "-----------------------\n";
    }
}

bool Library::empty() const{
    return m_items.empty();
}

std::size_t Library::size() const{
    return m_items.size();
}