#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "Item.h"
#include <vector>
#include <memory>
#include <cstddef>  // for std::size_t
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
    
    void search_by_title(const std::string &keyword) const;

    void checkout_item(int id);
    void return_item(int id);

    void list_all_items() const;

    bool empty() const;

    void sort_by_title(bool ascending = true);
    void sort_by_title_case_insensitive(bool ascending = true);
    void sort_by_id(bool ascending = true);
    void sort_by_date(bool ascending = true);

    std::size_t size() const;

    void save_to_file(const std::string &file_name) const; // before quitting
    void load_from_file(const std::string &file_name); // at program start

    void print_summary() const;

    void filter_by_status(Status status) const;
    void filter_by_type(Type type) const;
};

#endif