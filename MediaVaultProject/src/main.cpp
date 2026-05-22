
#include "Book.h"
#include "Movie.h"
#include "Game.h"
#include "Library.h"
#include "Exceptions.h"

#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include <cctype>

void display_menu() {
    std::cout << "Media Vault Menu:\n";
    std::cout << "A. Add Item (Book / Movie / Game)\n";
    std::cout << "R. Remove Item\n";
    std::cout << "S. Search Item by ID\n";
    std::cout << "T. Search Item by Title\n";
    std::cout << "C. Checkout Item\n";
    std::cout << "U. Return Item\n";
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

Platform get_platform_input() {

    while(true){
        std::cout << "Choose platform:\n"
                  << "1. PC\n"
                  << "2. PlayStation\n"
                  << "3. Xbox\n"
                  << "4. Nintendo Switch\n"
                  << "5. Mobile\n";
    
        int platform_choice = get_int_input("Platform: ");
        switch (platform_choice) {
            case 1: return Platform::PC;
            case 2: return Platform::PlayStation;
            case 3: return Platform::Xbox;
            case 4: return Platform::NintendoSwitch;
            case 5: return Platform::Mobile;
            default:
                std::cout << "Invalid choice. Try again.\n";
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
                    char type_choice = get_menu_choice("Add (B)ook, (M)ovie, (G)ame: ");
                    if(type_choice != 'B' && type_choice != 'M' && type_choice != 'G'){
                        std::cout << "Invalid type choice. Please enter B, M, or G." << std::endl;
                        break;
                    }

                    int id = get_int_input("ID: ");
                    std::string title = get_string_input("Title: ");
                    Date added = read_date_for_now();
                    
                    if(type_choice == 'B'){
                        std::string author = get_string_input("Author: ");
                        int pages = get_int_input("Pages: ");
                        auto book = std::make_unique<Book>(id, title, added, author, pages);
                        library.add_item(std::move(book));
                        std::cout << "Item added successfully.\n";
                    }
                    else if(type_choice == 'M'){
                        std::string director = get_string_input("Director: ");
                        int duration = get_int_input("Duration: ");
                        auto movie = std::make_unique<Movie>(id, title, added, director, duration);
                        library.add_item(std::move(movie));
                        std::cout << "Movie added successfully.\n";
                    }
                    else if(type_choice == 'G'){
                        Platform platform = get_platform_input();
                        auto game = std::make_unique<Game>(id, title, added, platform);
                        library.add_item(std::move(game));
                        std::cout << "Game added successfully.\n";
                    }
                    break;
                }

                case('R'): {
                    if (library.empty()) {
                        std::cout << "Library is empty.\n";
                        break;
                    }

                    int remove_id = get_int_input("Enter the ID of the item to remove: ");
                    library.remove_item(remove_id);
                    std::cout << "Item removed successfully.\n";    
                    break;
                }

                case('S'): {
                    if (library.empty()) {
                        std::cout << "Library is empty.\n";
                        break;
                    }

                    int search_id = get_int_input("Enter the ID of the item to search: ");
                    const Item* item = library.find_item(search_id);
                    if (item) {
                        std::cout << "\nItem found:\n" << *item << "\n";
                    } else {
                        std::cout << "Item with ID " << search_id << " not found.\n";
                    }
                    break;
                }
                case('T'):{
                    if(library.empty()){
                        std::cout << "Library is empty.\n";
                        break;
                    }

                    std::string keyword = get_string_input("Enter the Title keyword: ");
                    library.search_by_title(keyword);
                    break;
                }
                case('C'):{
                    if(library.empty()){
                        std::cout << "Library is empty.\n";
                        break;
                    }

                    int checkedout_id = get_int_input("Enter the ID of item to checkout: ");
                    library.checkout_item(checkedout_id);
                    std::cout << "Item checked out successfully.\n";
                    break;
                }
                case('U'):{
                    if(library.empty()){
                        std::cout << "Library is empty.";
                        break;
                    }

                    int return_id = get_int_input("Enter the ID of item to return: ");
                    library.return_item(return_id);
                    std::cout << "Item returned successfuly.\n";
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
        catch (const InvalidOperationError& e) {
            std::cerr << e.what() << "\n";
        }
        catch (const LibraryError& e) {
            std::cerr << "Library error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    
    return 0;
}   