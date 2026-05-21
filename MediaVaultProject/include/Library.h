#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "Item.h"
#include <vector>
#include <memory>
#include <cstddef>
#include "Exceptions.h"

class Library {
private:
    // Using smart pointers to manage Item objects and ensure proper memory management
    std::vector<std::unique_ptr<Item>> m_items; // Library own a collection of items
public:
    void add_item(std::unique_ptr<Item> item);
    
    void remove_item(int id);
    
    Item* find_item(int id); // Returns a pointer to the item with the given ID, or nullptr if not found
    const Item* find_item(int id) const; // Overloaded for const correctness    
    
    void list_all_items() const;

    bool empty() const;

    std::size_t size() const;
};

#endif