#include "Utils.h"
#include "Library.h"

#include <limits>
#include <iostream>
#include <cctype>
#include <stdexcept>

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

Date read_date_input() {

    while (true){
        std::string input_date = get_string_input("Added date (YYYY-MM-DD): ");

        try{
            return Date::date_from_string(input_date);
        }
        catch (const std::exception &e){
            std::cout << e.what() << "\n";
        }
    }
}

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
    std::cout << "O. Sort Items\n";
    std::cout << "P. Print summary\n";
    std::cout << "F. Filter Items\n";
    std::cout << "Q. Quit\n";
    std::cout << "----------------------------\n";
}

void display_sort_menu() {
    std::cout << "\nSort Options:\n";
    std::cout << "----------------------------\n";
    std::cout << "1. Title (Ascending)\n";
    std::cout << "2. Title (Descending)\n";
    std::cout << "3. Title Case-Insensitive (Ascending)\n";
    std::cout << "4. Title Case-Insensitive (Descending)\n";
    std::cout << "5. ID (Ascending)\n";
    std::cout << "6. ID (Descending)\n";
    std::cout << "7. Date (Ascending)\n";
    std::cout << "8. Date (Descending)\n";
}

void display_filter_menu(){
    std::cout << "\nFilter Options:\n";
    std::cout << "----------------------------\n";
    std::cout << "1. Show Available Items\n";
    std::cout << "2. Show CheckedOut Items\n";
    std::cout << "3. Show Lost Items\n";
    std::cout << "4. Show Books\n";
    std::cout << "5. Show Movies\n";
    std::cout << "6. Show Games\n";  
}

bool library_not_empty(const Library &library){
    if (library.empty()){
        std::cout << "Library is empty.\n";
        return false;
    }
    return true;
}

void print_section_header(const std::string &title){
    std::cout << "\n" << title << "\n";
    std::cout << "----------------------------\n";
}