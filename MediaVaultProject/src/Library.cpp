#include "Library.h"
#include "Book.h"
#include "Movie.h"
#include "Game.h"

#include <algorithm>
#include <iostream>
#include <string>  // for to_string(...) & std::stoi(...)
#include <utility>
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>

// small helper function
//Pass by value when you want to modify a local copy and return it.
static string string_to_lower(string str){
    for (char &c: str){
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return str;
}

bool Library::empty() const{
    return m_items.empty();
}

std::size_t Library::size() const{
    return m_items.size();
}

/*find_item() returns Item* because a pointer can represent 
two possibilities:
a valid found object
no object found → nullptr

But a reference (Item&) must always refer to a real object 
and cannot be “empty”*/

// not constant to modify (checkout and return)
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

// constant for displaying
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

void Library::search_by_title(const string& keyword) const{

    if (keyword.empty()){
        std::cout << "Keyword is empty!\n";
        return;
    }   
    const string lower_keyword = string_to_lower(keyword);
    bool found = false;

    for (const auto& item: m_items){
        const string lower_title = string_to_lower(item->get_title());
        if (lower_title.find(lower_keyword) != string::npos){
            std::cout << *item << std::endl;
            found = true;
        }
    }
    if (!found){
        std::cout << "No matches. \n";
    } 
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
    
/*[ keep ] [ remove ] [ keep ] [ keep ]
[ keep ] [ keep ] [ keep ] [ ??? ]
                     ^
                     it
erase(it, end) removes the ??? part. */

    m_items.erase(it, m_items.end());
    
    if (m_items.size() == old_size) {
        throw NotFoundError("Item with ID " + std::to_string(id) + " not found.");
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

void Library::sort_by_title(bool ascending){
    std::sort(m_items.begin(), m_items.end(),
    [ascending](const std::unique_ptr<Item>& a, 
                const std::unique_ptr<Item>& b){
    return ascending ? (a->get_title() < b->get_title()) // ascending 1->2->3
                     : (a->get_title() > b->get_title());
    });
}

void Library::sort_by_title_case_insensitive(bool ascending){
    std::sort(m_items.begin(), m_items.end(), 
    [ascending](const std::unique_ptr<Item>& a, 
                const std::unique_ptr<Item>& b){
        std::string title_a = string_to_lower(a->get_title());
        std::string title_b = string_to_lower(b->get_title());
        return ascending ? (title_a < title_b)
                         : (title_a > title_b);
    });
}

void Library::sort_by_id(bool ascending){
    std::sort(m_items.begin(), m_items.end(), 
    [ascending](const std::unique_ptr<Item>& a, 
                const std::unique_ptr<Item>& b){
    return (ascending ? (a->get_id() < b->get_id())
                      : (a->get_id() > b->get_id()));
    });
}

void Library::sort_by_date(bool ascending){
    std::sort(m_items.begin(), m_items.end(), 
    [ascending](const std::unique_ptr<Item>& a,
                const std::unique_ptr<Item>& b){
    return (ascending ? (a->get_added_date() < b->get_added_date()) 
                      : (b->get_added_date() < a->get_added_date()) );
    });
}

void Library::filter_by_status(Status status) const{
    if(m_items.empty()){
        std::cout << "Library is empty.\n";
        return;
    }
    bool found = false;
    for (const auto& item: m_items){
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
    for (const auto& item: m_items){
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

void Library::save_to_file(const std::string& file_name) const{
    
    std::ofstream out_file(file_name);

    if (!out_file){
        throw LibraryError("Could not open file for writing: " + file_name);
    }

    for(const auto& item: m_items){
        out_file << item->serialize() << "\n";
    }
}

// for loading data from file to turns one line into vector of strings
static std::vector<string> split_csv_line(const string& line){
    
    std::vector<string> fields;
    std::stringstream ss(line);
    string field;

    while (std::getline(ss, field, ',')){
        fields.push_back(field);
    }
    return fields;
}

void Library::load_from_file(const string& file_name){
    
    std::ifstream in_file(file_name); // to read data from a file
    if (!in_file){return;}
    
    m_items.clear();

    string line;
    int line_number{0};
    while(std::getline(in_file, line)){
        ++line_number;
        
        if(line.empty()){continue;}

        std::vector<std::string> fields = split_csv_line(line);
        if(fields.empty()){continue;}

        Type type;
        try{
            type = type_from_string(fields[0]);
        }
        catch (const std::exception&) {
            throw LibraryError("Unknown item type at line " +
                std::to_string(line_number) + ": " + fields[0]);

        }
        switch(type){
            case Type::Book:{
                if (fields.size() != 7) {
                    // missing field, extra field, wrong #of commas
                    throw LibraryError("Invalid Book record at line " +
                            std::to_string(line_number) + ": " + line);
                }
                try{
                    int id = std::stoi(fields[1]);
                    string title = fields[2];
                    Date added_date = Date::date_from_string(fields[3]);
                    Status status = status_from_string(fields[4]);
                    string author = fields[5];
                    int pages = std::stoi(fields[6]);

                    auto book = std::make_unique<Book>(id, title, added_date, author, pages);
                    book->set_status(status);
                    m_items.push_back(std::move(book));
                }
                catch(const std::exception& e){
                    throw LibraryError("Invalid Book record at line " +
                        std::to_string(line_number) + ": " + line 
                        + " | Reason: " + e.what());
                }
                break;
            }
            case Type::Movie: {
                if (fields.size() != 7) {
                    throw LibraryError("Invalid Movie record at line " + 
                        std::to_string(line_number) + ": " + line);
                }
                try{
                    int id = std::stoi(fields[1]);
                    string title = fields[2];
                    Date added_date = Date::date_from_string(fields[3]);
                    Status status = status_from_string(fields[4]);
                    string director = fields[5];
                    int duration = std::stoi(fields[6]);

                    auto movie = std::make_unique<Movie>(id, title, added_date, director, duration);
                    movie->set_status(status);
                    m_items.push_back(std::move(movie));
                }
                catch(const std::exception& e){
                    throw LibraryError("Invalid Movie record at line " +
                        std::to_string(line_number) + ": " + line 
                        + " | Reason: " + e.what());
                }
                break;
            }
            case Type::Game: {
                if (fields.size() != 6) {
                    throw LibraryError("Invalid Game record at line " + 
                        std::to_string(line_number) + ": " + line);
                }
                try{
                    int id = std::stoi(fields[1]);
                    string title = fields[2];
                    Date added_date = Date::date_from_string(fields[3]);
                    Status status = status_from_string(fields[4]);
                    Platform platform = platform_from_string(fields[5]);

                    auto game = std::make_unique<Game>(id, title, added_date, platform);
                    game->set_status(status);
                    m_items.push_back(std::move(game));
                }
                catch(const std::exception& e){
                    throw LibraryError("Invalid Game record at line " +
                        std::to_string(line_number) + ": " + line 
                        + " | Reason: " + e.what());
                }
                break;
            }
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

    for (const auto& item: m_items){        
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



