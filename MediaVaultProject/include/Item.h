#ifndef _ITEM_H_
#define _ITEM_H_

#include "Date.h"
#include <string>


    enum class Type { Book, Movie, Game};
    enum class Status { Available, CheckedOut, Lost}; 
class Item{
protected:
    int m_id;
    std::string m_title;
    Date added;
    Status m_status;

public:
    Item(int id, const std::string &title, const Date &added, Status status);
    
    int get_id() const;
    const std::string& get_title() const;
    const Date& get_release_date() const;
    Type get_type() const;
    Status get_status() const;
    
    void set_status(ItemStatus status);
    std::string to_string() const;

    virtual std::string get_details() const = 0; // Pure virtual function for polymorphism

    ~Item() = default;
};

#endif