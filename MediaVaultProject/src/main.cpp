
#include "Book.h"
#include "Movie.h"
#include "Game.h"
#include "Library.h"
#include "Exceptions.h"
#include "Utils.h"

#include <iostream>
#include <memory>
#include <string>


void display_menu() {
    std::cout << "\nMedia Vault Menu:\n";
    std::cout << "----------------------------\n";
    std::cout << "A. Add Item (Book / Movie / Game)\n";
    std::cout << "R. Remove Item\n";
    std::cout << "S. Search Item by ID\n";
    std::cout << "T. Search Item by Title\n";
    std::cout << "C. Checkout Item\n";
    std::cout << "U. Return Item\n";
    std::cout << "D. Display All Items\n";
    std::cout << "Q. Quit\n";
}

int main() {
    
    Library library;

    try{
        library.load_from_file("data/MediaVault.txt");
    }
    catch(const std::exception &e){
        std::cerr << "Error loading file: " << e.what() << "\n";
    }
    
    while (true){
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
                    Date added = read_date_input();
                    
                    if (type_choice == 'B'){
                        std::string author = get_string_input("Author: ");
                        int pages = get_int_input("Pages: ");
                        auto book = std::make_unique<Book>(id, title, added, author, pages);
                        library.add_item(std::move(book));
                        std::cout << "Book added successfully.\n";
                    }
                    else if (type_choice == 'M'){
                        std::string director = get_string_input("Director: ");
                        int duration = get_int_input("Duration: ");
                        auto movie = std::make_unique<Movie>(id, title, added, director, duration);
                        library.add_item(std::move(movie));
                        std::cout << "Movie added successfully.\n";
                    }
                    else if (type_choice == 'G'){
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
                    if (library.empty()){
                        std::cout << "Library is empty.\n";
                        break;
                    }

                    std::string keyword = get_string_input("Enter the Title keyword: ");
                    library.search_by_title(keyword);
                    break;
                }
                case('C'):{
                    if (library.empty()){
                        std::cout << "Library is empty.\n";
                        break;
                    }

                    int checkedout_id = get_int_input("Enter the ID of item to checkout: ");
                    library.checkout_item(checkedout_id);
                    std::cout << "Item checked out successfully.\n";
                    break;
                }
                case('U'):{
                    if (library.empty()){
                        std::cout << "Library is empty.\n";
                        break;
                    }

                    int return_id = get_int_input("Enter the ID of item to return: ");
                    library.return_item(return_id);
                    std::cout << "Item returned successfully.\n";
                    break;
                }

                case('D'):
                    library.list_all_items();
                    break;

                case('Q'):
                    library.save_to_file("data/MediaVault.txt");
                    std::cout << "Data saved. Quitting...\n";
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