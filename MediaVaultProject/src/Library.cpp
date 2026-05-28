#include "Library.h"
#include "Book.h"
#include "Movie.h"
#include "Game.h"

#include <algorithm>
#include <iostream>
#include <string>  // for to_string()
#include <utility>
#include <fstream>
#include <vector>
#include <sstream>

// small helper function
static std::string string_to_lower(std::string str){
    for (char &c: str){
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return str;
}

static std::vector<std::string> split_cvs_line(const std::string &line){
    
    std::vector<std::string> strings;
    std::stringstream ss(line);
    std::string string;

    while (std::getline(ss, string, ',')){
        strings.push_back(string);
    }
    return strings;
}

void Library::add_item(std::unique_ptr<Item> item) {
    if (!item) {
        throw LibraryError("Cannot add a null item to the library.");
    }

    if (find_item(item->get_id()) != nullptr) {
        throw LibraryError("Duplicate item with ID " + std::to_string(item->get_id()) + " already exists.");
    }

    m_items.push_back(std::move(item)); // unique_ptr can't be copied
}

void Library::remove_item(int id) {

    const auto old_size = m_items.size();

    auto it = std::remove_if (m_items.begin(), m_items.end(),
              [id](const std::unique_ptr<Item>& item) 
              { return item->get_id() == id; });
    
    m_items.erase(it, m_items.end());
    
    if (m_items.size() == old_size) {
        throw NotFoundError("Item with ID " + std::to_string(id) + " not found.");
    }
}

Item* Library::find_item(int id) {
    auto it = std::find_if(m_items.begin(), m_items.end(),
              [id](const std::unique_ptr<Item>& item) 
              { return item->get_id() == id; });
    
    if (it != m_items.end()){
        return it->get(); // extract the row pointer from unique_ptr
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

void Library::search_by_title(const std::string &keyword) const{

    if (keyword.empty()){
        std::cout << "Keyword is empty!\n";
        return;
    }
    
    const std::string lower_keyword = string_to_lower(keyword);
    bool found = false;

    for (const auto &item: m_items){
        const std::string lower_title = string_to_lower(item->get_title());
        if (lower_title.find(lower_keyword) != std::string::npos){
            std::cout << *item << std::endl;
            found = true;
        }
    }

    if (!found){
        std::cout << "No matches." << std::endl;
    } 
}

void Library::checkout_item(int id){
    Item *item = find_item(id);

    if (!item){
        throw NotFoundError("Item with ID: " + std::to_string(id) + " not found.");
    }

    if (item->get_status() != Status::Available){
        throw InvalidOperationError("Item with ID: " + std::to_string(id) + " is not available for checkout.");
    }

    item->set_status(Status::CheckedOut);

}

void Library::return_item(int id){
    Item *item = find_item(id);

    if (!item){
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

void Library::sort_by_title(bool ascending){
    std::sort(m_items.begin(), m_items.end(),
    [ascending](const std::unique_ptr<Item> &a, const std::unique_ptr<Item> &b){
        return ascending ? (a->get_title() < b->get_title()) : (a->get_title() > b->get_title());
    });
}

void Library::sort_by_title_case_insensitive(bool ascending){
    std::sort(m_items.begin(), m_items.end(), [ascending](const std::unique_ptr<Item> &a, const std::unique_ptr<Item> &b){
        std::string title_a = string_to_lower(a->get_title());
        std::string title_b = string_to_lower(b->get_title());

        return ascending ? (title_a < title_b)
                         : (title_a > title_b);
    });
}

void Library::sort_by_id(bool ascending){
    std::sort(m_items.begin(), m_items.end(), [ascending]
    (const std::unique_ptr<Item> &a, const std::unique_ptr<Item> &b){
        return (ascending ? (a->get_id() < b->get_id())
                          : (a->get_id() > b->get_id()));
    });
}

void Library::sort_by_date(bool ascending){
    std::sort(m_items.begin(), m_items.end(), [ascending]
(const std::unique_ptr<Item> &a, const std::unique_ptr<Item> &b){
    return (ascending ? (a->get_added_date() < b->get_added_date()) 
                      : (b->get_added_date() < a->get_added_date()) );
});
}

std::size_t Library::size() const{
    return m_items.size();
}

void Library::save_to_file(const std::string &file_name) const{
    
    std::ofstream out_file(file_name);

    if (!out_file){
        throw LibraryError("Could not open file for writing: " + file_name);
    }

    for(const auto &item: m_items){
        out_file << item->serialize() << "\n";
    }
}

void Library::load_from_file(const std::string &file_name){
    
    std::ifstream in_file(file_name);
    if (!in_file){
        return;
    }

    m_items.clear();

    std::string line;

    while(std::getline(in_file, line)){
        if(line.empty()){
            continue;
        }

        std::vector<std::string> strings = split_cvs_line(line);
        if(strings.empty()){
            continue;
        }

        const std::string &type = strings[0];

        if(type == "Book"){
            if (strings.size() != 7) {
                throw LibraryError("Invalid Book record: " + line);
            }

            int id = std::stoi(strings[1]);
            std::string title = strings[2];
            Date added = Date::date_from_string(strings[3]);
            Status status = status_from_string(strings[4]);
            std::string author = strings[5];
            int pages = std::stoi(strings[6]);

            auto book = std::make_unique<Book>(id, title, added, author, pages);
            book->set_status(status);
            m_items.push_back(std::move(book));
        }
        else if (type == "Movie") {
            if (strings.size() != 7) {
                throw LibraryError("Invalid Movie record: " + line);
            }

            int id = std::stoi(strings[1]);
            std::string title = strings[2];
            Date added = Date::date_from_string(strings[3]);
            Status status = status_from_string(strings[4]);
            std::string director = strings[5];
            int duration = std::stoi(strings[6]);

            auto movie = std::make_unique<Movie>(id, title, added, director, duration);
            movie->set_status(status);
            m_items.push_back(std::move(movie));
        }
        else if (type == "Game") {
            if (strings.size() != 6) {
                throw LibraryError("Invalid Game record: " + line);
            }

            int id = std::stoi(strings[1]);
            std::string title = strings[2];
            Date added = Date::date_from_string(strings[3]);
            Status status = status_from_string(strings[4]);
            Platform platform = platform_from_string(strings[5]);

            auto game = std::make_unique<Game>(id, title, added, platform);
            game->set_status(status);
            m_items.push_back(std::move(game));
        }
        else {
            throw LibraryError("Unknown item type in file: " + type);
        }
    }

}

void Library::print_summary() const{
    if (m_items.empty()){
        std::cout << "Library is empty.\n";
        return;
    }

    size_t books{0};
    size_t movies{0};
    size_t games{0};

    size_t available{0};
    size_t checked_out{0};
    size_t lost{0};

    for (const auto &item: m_items){
        
        switch(item->get_type()){
            case Type::Book:
                ++books;
                break;
            case Type::Movie:
                ++movies;
                break;
            case Type::Game:
                ++games;
                break;
        }

        switch (item->get_status()){
            case Status::Available:
                ++available;
                break;
            case Status::CheckedOut:
                ++checked_out;
                break;
            case Status::Lost:
                ++lost;
                break;   
        }
    }

    std::cout << "\nLibrary Summary\n";
    std::cout << "--------------------\n";
    std::cout << "Total items: " << m_items.size() << "\n";
    std::cout << "Books: " << books << "\n";
    std::cout << "Movies: " << movies << "\n";
    std::cout << "Games: " << games << "\n";
    std::cout << "Available: " << available << "\n";
    std::cout << "CheckedOut: " << checked_out << "\n";
    std::cout << "Lost: " << lost << "\n";
}

void Library::filter_by_status(Status status) const{
    if(m_items.empty()){
        std::cout << "Library is empty.\n";
        return;
    }
    bool found = false;
    for (const auto &item: m_items){
        if(item->get_status() == status){
            std::cout << *item << "\n";
            std::cout << "-------------------------------\n";
            found = true;
        }
    }
    if (!found){
        std::cout << "No items match the selected status.\n";
    }
}

void Library::filter_by_type(Type type) const{
    if (m_items.empty()){
        std::cout << "Library is empty.\n";
        return;
    }
    bool found = false;
    for (const auto &item: m_items){
        if(item->get_type() == type){
            std::cout << *item << "\n";
            std::cout << "-----------------------\n";
            found = true;
        }
    }
    if (!found){
        std::cout << "No items match the selected type.\n";
    }
}


