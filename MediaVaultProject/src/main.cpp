
#include "Book.h"
#include "Library.h"
#include "Exceptions.h"

#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include <cctype>

void display_menu() {
    std::cout << "Media Vault Menu:\n";
    std::cout << "A. Add Item\n";
    std::cout << "R. Remove Item\n";
    std::cout << "S. Search Item\n";
    std::cout << "D. Display All Items\n";
    std::cout << "Q. Quit\n";
}

char get_menu_choice(const std::string& prompt) {
    while (true) {
        std::string line;
        std::cout << prompt;

        if (!std::getline(std::cin >> std::ws, line)) {
            throw std::runtime_error("Input stream closed (EOF).");
        }
        if (!line.empty()) {
            unsigned char c = static_cast<unsigned char>(line[0]);
            return static_cast<char>(std::toupper(c)); // Convert to uppercase for case-insensitive comparison
        }
        
        std::cout << "Input cannot be empty. Please try again.\n";
            
    }
}

 // Helper function to get validated integer input from the user
int get_int_input(const std::string& prompt) {
    
    int value{};
    while (true){
        
        std::cout << prompt;
        if (std::cin >> value) {
            return value; // Valid integer input
        } else {
            std::cout << "Invalid input. Please enter a valid integer.\n";
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
}

std::string get_string_input(const std::string& prompt) {
    
    std::string value;
    while (true)
    {
        std::cout << prompt;
        //std::getline(std::cin >> std::ws, value); // Read a line of input
        
        if(!std::getline(std::cin >> std::ws, value)) {
            throw std::runtime_error("Input stream closed (EOF).");
        }
        else if(!value.empty()) {
            return value;
        }else{
            std::cout << "Input cannot be empty. Please try again.\n";
        }
    }
}



Date read_date_for_now() {
    return Date(20, 5, 2026);
}


int main() {
    
    Library library;
    
    while(true){
        display_menu();
        char choice {};

        try{
            choice = get_menu_choice("Enter your choice: ");
            
            switch(choice) {
                case('A'): {
                    int id = get_int_input("ID: ");
                    std::string title = get_string_input("Title: ");
                    std::string author = get_string_input("Author: ");
                    int pages = get_int_input("Pages: ");
                    Date added = read_date_for_now();
                    auto book = std::make_unique<Book>(id, title, added, author, pages);
                    library.add_item(std::move(book));

                    std::cout << "Item added successfully.\n";
                    break;
                }

                case('R'): {
                    int remove_id = get_int_input("Enter the ID of the item to remove: ");
                    library.remove_item(remove_id);
                    std::cout << "Item removed successfully.\n";    
                    break;
                }

                case('S'): {
                    int search_id = get_int_input("Enter the ID of the item to search: ");
                    const Item* item = library.find_item(search_id);
                    if (item) {
                        std::cout << "Item found: " << *item<< "\n";
                    } else {
                        std::cout << "Item with ID " << search_id << " not found.\n";
                    }
                    break;
                }
                case('D'):
                    library.list_all_items();
                    break;

                case('Q'):
                    std::cout << "Quitting...\n";
                    return 0;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }

        catch (const NotFoundError& e) {
            std::cerr << e.what() << "\n";
        }
        catch (const LibraryError& e) {
            std::cerr << "Library error: " << e.what() << "\n";
        }
        catch(const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    
    return 0;
}   