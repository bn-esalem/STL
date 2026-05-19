#include "Library.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

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

void Library::list_all_items() const {
    if (m_items.empty()) {
        std::cout << "No items in the library.\n";
        return;
    }
    for (const auto& item : m_items) {
        std::cout << *item << "\n"; // Using overloaded operator<< for Item
    }
}