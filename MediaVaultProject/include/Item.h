#ifndef _ITEM_H_
#define _ITEM_H_

#include "Date.h"
#include <string>
#include <iostream>

enum class Type { Book, Movie, Game};
enum class Status { Available, CheckedOut, Lost}; 

class Item{  // Abstract base class for all media items
private:
    int m_id;
    std::string m_title;
    Date m_added;
    Status m_status;

public:
    Item(int id, std::string title, const Date &added, Status status = Status::Available);
    
    int get_id() const;
    const std::string& get_title() const;
    // Return a const reference to the added date to avoid unnecessary copying
    const Date& get_added_date() const;
    
    Status get_status() const;
    void set_status(Status status);

    // Pure virtual functions for polymorphism
    virtual std::string info() const = 0; // Pure virtual function for polymorphism
    virtual Type get_type() const = 0; // Pure virtual function to get the type of item 
   
    virtual ~Item() = default;
};

// Overload the << operator for easy printing of Item details
std::ostream& operator<<(std::ostream& os, const Item &item);

// Helper functions to convert enums to strings for display purposes
std::string status_to_string(Status status);

std::string type_to_string(Type type);

#endif