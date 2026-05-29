
#include "Book.h"
#include "Movie.h"
#include "Game.h"
#include "Library.h"
#include "Exceptions.h"
#include "Utils.h"

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

int main(){
    
    Library library;
    std::mutex library_mutex; // will later protect access to the shared library
    std::mutex cout_mutex;
    // thread-safe flag to tell background thread: keep running{true}/stop{false}
    std::atomic<bool> autosave_running{true};
    
    try{
        library.load_from_file("data/MediaVault.txt");
    }
    catch (const std::exception &e){
        std::cerr << "Error loading file: " << e.what() << "\n";
    }

    // the thread can use library, library_mutex and autosave_running
    std::thread autosave_thread([&](){
        using namespace std::chrono_literals;

        while(autosave_running){
            // wait about 10 s, but check every 1 s if we should stop
            for (int i{0}; i < 10 && autosave_running; ++i){
                std::this_thread::sleep_for(1s); // because of chrono_literals
            }
            if (!autosave_running){
                break;
            }
            try{
                std::lock_guard<std::mutex> lock (library_mutex);
                library.save_to_file("data/MediaVault.txt");
            }
            catch(const std::exception &e){
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cerr << "\n[Autosave error] " << e.what() << "\n";
            }
        }
    });
    
    while (true){
        display_menu();
        char choice {};

        try{
            choice = get_menu_choice("Enter your choice: ");
            
            switch(choice) {
                case('A'): {
                    char type_choice = get_menu_choice("Add (B)ook, (M)ovie, (G)ame: ");
                    if(type_choice != 'B' && type_choice != 'M' && type_choice != 'G'){
                        std::lock_guard<std::mutex> lock(cout_mutex);
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
                        {
                            std::lock_guard<std::mutex> lock(library_mutex);
                            library.add_item(std::move(book));
                        }
                        {
                            std::lock_guard<std::mutex> lock(cout_mutex);
                            std::cout << "Book added successfully.\n";
                        }
                    }
                    else if (type_choice == 'M'){
                        std::string director = get_string_input("Director: ");
                        int duration = get_int_input("Duration: ");
                        auto movie = std::make_unique<Movie>(id, title, added, director, duration);
                        {
                            std::lock_guard<std::mutex> lock(library_mutex);
                            library.add_item(std::move(movie));
                        }
                        {
                            std::lock_guard<std::mutex> lock(cout_mutex);
                            std::cout << "Movie added successfully.\n";
                        }
                    }
                    else if (type_choice == 'G'){
                        Platform platform = get_platform_input();
                        auto game = std::make_unique<Game>(id, title, added, platform);
                        {
                            std::lock_guard<std::mutex> lock(library_mutex);
                            library.add_item(std::move(game));
                        }
                        {
                            std::lock_guard<std::mutex> lock(cout_mutex);
                            std::cout << "Game added successfully.\n";
                        }
                    }
                    break;
                }
                case('R'): {
                    {
                        std::lock_guard<std::mutex> lock(library_mutex);
                        if (!library_not_empty(library)){
                            break;
                        }
                    }

                    int remove_id = get_int_input("Enter the ID of the item to remove: ");
                    {
                        std::lock_guard<std::mutex> lock(library_mutex);
                        library.remove_item(remove_id);
                    }
                    {
                        std::lock_guard<std::mutex> lock(cout_mutex);
                        std::cout << "Item removed successfully.\n";
                    }    
                    break;
                }
                case('S'): {
                    int search_id = get_int_input("Enter the ID of the item to search: ");
                    {
                        std::lock_guard<std::mutex> lock(library_mutex);
                        if (!library_not_empty(library)){
                            break;
                        }
                        const Item* item = library.find_item(search_id);
                        if (item) {
                            std::lock_guard<std::mutex> lock(cout_mutex);
                            std::cout << "\nItem found:\n" << *item << "\n";
                        }
                        else {
                            std::lock_guard<std::mutex> lock(cout_mutex);
                            std::cout << "Item with ID " << search_id << " not found.\n";
                        }
                    }
                    break;
                }
                case('T'):{
                    std::string keyword = get_string_input("Enter the Title keyword: ");
                    {
                        std::lock_guard<std::mutex> lock(library_mutex);
                        if (!library_not_empty(library)){
                            break;
                        }                       
                        library.search_by_title(keyword);
                    }
                    break;
                }
                case('C'):{
                    int checkedout_id = get_int_input("Enter the ID of item to checkout: ");
                    {
                        std::lock_guard<std::mutex> lock(library_mutex); 
                        if (!library_not_empty(library)){                     
                            break;
                        }                  
                        library.checkout_item(checkedout_id);
                    }
                    {
                        std::lock_guard<std::mutex> lock(cout_mutex);
                        std::cout << "Item checked out successfully.\n";
                    }
                    break;
                }
                case('U'):{
                    int return_id = get_int_input("Enter the ID of item to return: ");
                    {
                        std::lock_guard<std::mutex> lock(library_mutex);
                        if (!library_not_empty(library)){
                            break;
                        }
                        library.return_item(return_id);
                    }
                    {
                        std::lock_guard<std::mutex> lock(cout_mutex);
                        std::cout << "Item returned successfully.\n";
                    }
                    break;
                }
                case('D'):
                    {
                        std::lock_guard<std::mutex> lock(library_mutex);
                        library.list_all_items();
                        break;
                    }
                case('O'):{
                    display_sort_menu();
                    int sort_choice = get_int_input("Choose sorting option: ");
                    bool valid_sort = true;
                    {
                        std::lock_guard<std::mutex> lock(library_mutex);
                        if(!library_not_empty(library)){
                            break;
                        }            
                        switch (sort_choice){
                            case 1: 
                                library.sort_by_title(true);
                                {
                                    std::lock_guard<std::mutex> lock(cout_mutex);
                                    std::cout << "Items sorted by title ascending.\n";
                                }
                                break;
                            case 2: 
                                library.sort_by_title(false);
                                {
                                    std::lock_guard<std::mutex> lock(cout_mutex);
                                    std::cout << "Items sorted by title descending.\n";
                                }
                                break;
                            case 3:
                                library.sort_by_title_case_insensitive(true);
                                {
                                    std::lock_guard<std::mutex> lock(cout_mutex);
                                    std::cout << "Items sorted by title case-insensitive ascending.\n";
                                }
                                break;
                            case 4:
                                library.sort_by_title_case_insensitive(false);
                                {
                                    std::lock_guard<std::mutex> lock(cout_mutex);
                                    std::cout << "Items sorted by title case-insensitive descending.\n";
                                }
                                break;
                            case 5:
                                library.sort_by_id(true);
                                {
                                    std::lock_guard<std::mutex> lock(cout_mutex);
                                    std::cout << "Items sorted by ID ascending.\n";
                                }
                                break;
                            case 6:
                                library.sort_by_id(false);
                                {
                                    std::lock_guard<std::mutex> lock(cout_mutex);
                                    std::cout << "Items sorted by ID descending.\n";
                                }
                                break;
                            case 7:
                                library.sort_by_date(true);
                                {
                                    std::lock_guard<std::mutex> lock(cout_mutex);
                                    std::cout << "Items sorted by date ascending.\n";
                                }
                                break;
                            case 8:
                                library.sort_by_date(false);
                                {
                                    std::lock_guard<std::mutex> lock(cout_mutex);
                                    std::cout << "Items sorted by date descending.\n";
                                }
                                break;
                            default:
                                {
                                    std::lock_guard<std::mutex> lock(cout_mutex);
                                    std::cout << "Invalid sort option.\n";
                                }
                                valid_sort = false;
                                break;
                        }
                    
                        if (valid_sort){
                            print_section_header("Sorted items");
                            library.list_all_items();
                        }
                    }
                    break;
                }
                case ('P'):{
                    std::lock_guard<std::mutex> lock(library_mutex);
                    if (!library_not_empty(library)){
                        break;
                    }
                    library.print_summary();
                    break;
                }
                case ('F'):{
                    display_filter_menu();
                    int filter_choice = get_int_input("Choose filter option: ");
                    bool valid_filter = true;
                    {
                        std::lock_guard<std::mutex> lock(library_mutex);
                        if (!library_not_empty(library)){
                            break;
                        }

                        switch(filter_choice){
                            case 1:
                            case 2:
                            case 3:
                            case 4:
                            case 5:
                            case 6:
                                print_section_header("Filtered results");
                                break;
                            default:
                                {
                                    std::lock_guard<std::mutex> lock(cout_mutex);
                                    std::cout << "Invalid filter option.\n";
                                }
                                valid_filter = false;
                                break;
                        }
                        if(!valid_filter){
                            break;
                        }
                        switch(filter_choice){
                            case 1:
                                library.filter_by_status(Status::Available);
                                break;
                            case 2:
                                library.filter_by_status(Status::CheckedOut);
                                break;
                            case 3:
                                library.filter_by_status(Status::Lost);
                                break;
                            case 4:
                                library.filter_by_type(Type::Book);
                                break;
                            case 5:
                                library.filter_by_type(Type::Movie);
                                break;
                            case 6:
                                library.filter_by_type(Type::Game);
                                break;
                        }
                        break;
                    }
                }
                case('Q'):{
                    autosave_running = false;
                    if(autosave_thread.joinable()){
                        autosave_thread.join();
                    }
                    {
                        std::lock_guard<std::mutex> lock (library_mutex);
                        library.save_to_file("data/MediaVault.txt");
                    }
                    {
                        std::lock_guard<std::mutex> lock(cout_mutex);
                        std::cout << "Data saved. Quitting...\n";
                    }                    
                    return 0;
                }
                default:
                    {
                        std::lock_guard<std::mutex> lock(cout_mutex);
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                    break;
            }
        }

        catch (const NotFoundError& e) {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cerr << e.what() << "\n";
        }
        catch (const InvalidOperationError& e) {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cerr << e.what() << "\n";
        }
        catch (const LibraryError& e){
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cerr << "Library error: " << e.what() << "\n";
        }
        catch (const std::exception& e){
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cerr << "Error: " << e.what() << '\n';
        }
    }

    autosave_running = false;
    if (autosave_thread.joinable()){
        autosave_thread.join();
    }

    return 0;
}   