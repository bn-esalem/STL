#ifndef _UTILS_H_
#define _UTILS_H_

#include "Game.h"
#include "Date.h"


#include <string>

using std::string;
class Library;

void display_menu();
char get_menu_choice(const string& prompt);

int get_int_input(const string& prompt);
string get_string_input(const string& prompt);
Date read_date_input();
Platform get_platform_input();

void display_search_menu();
void display_sort_menu();
void display_filter_menu();

bool library_not_empty(const Library& library);

void print_section_header(const string& title);

#endif
