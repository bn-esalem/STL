#ifndef _UTILS_H_
#define _UTILS_H_

#include "Game.h"
#include "Date.h"

#include <string>


char get_menu_choice(const std::string& prompt);
int get_int_input(const std::string& prompt);
std::string get_string_input(const std::string& prompt);
Platform get_platform_input();
Date read_date_input();

#endif
