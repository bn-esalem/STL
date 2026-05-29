# MediaVault

MediaVault is a **C++17 command-line media management application** for managing a collection of **Books**, **Movies**, and **Games**.

This project was built as a practical learning project to apply and strengthen important C++ concepts in a realistic multi-file application.

---

## Project Summary

MediaVault is a feature-rich C++17 CLI application that allows users to manage different types of media items, including Books, Movies, and Games. It supports adding, removing, searching, sorting, filtering, checkout/return workflows, and file persistence through save/load functionality.

The project was developed to practice core C++ programming concepts such as:

- object-oriented programming
- inheritance and polymorphism
- smart pointers
- STL containers and algorithms
- exception handling
- file I/O
- serialization and deserialization
- date parsing and validation
- multithreading with background autosave

---

## Features

MediaVault currently supports the following features:

### Item Management
- Add new items:
  - Book
  - Movie
  - Game
- Remove items by ID
- Display all stored items

### Searching
- Search items by ID
- Search items by title keyword (case-insensitive)

### Sorting
- Sort by title (ascending / descending)
- Sort by title case-insensitive (ascending / descending)
- Sort by ID (ascending / descending)
- Sort by date (ascending / descending)

### Filtering
- Filter by status:
  - Available
  - CheckedOut
  - Lost
- Filter by type:
  - Book
  - Movie
  - Game

### Status Management
- Checkout items
- Return items

### Statistics
- Print summary information:
  - total number of items
  - number of books, movies, and games
  - number of available, checked-out, and lost items

### Persistence
- Save all items to file
- Load items automatically when the program starts

### Validation
- Validated integer and string input
- Date input validation using `YYYY-MM-DD`
- Full calendar validation including leap years

### Multithreading
- Background autosave thread
- Mutex-protected shared data access
- Clean thread shutdown on exit

---

## Concepts Practiced

This project demonstrates practical use of the following C++ concepts:

- multi-file project structure
- classes and objects
- inheritance
- polymorphism
- abstract base classes
- smart pointers (`std::unique_ptr`)
- enums
- operator overloading
- STL containers
- STL algorithms
- lambdas
- custom exceptions
- file I/O
- string parsing
- data validation
- date comparison and validation
- multithreading with:
  - `std::thread`
  - `std::mutex`
  - `std::lock_guard`
  - `std::atomic`

---

## Project Structure

```text
MediaVaultProject/
├── include/
│   ├── Date.h
│   ├── Item.h
│   ├── Book.h
│   ├── Movie.h
│   ├── Game.h
│   ├── Library.h
│   ├── Exceptions.h
│   ├── Utils.h
│
├── src/
│   ├── Date.cpp
│   ├── Item.cpp
│   ├── Book.cpp
│   ├── Movie.cpp
│   ├── Game.cpp
│   ├── Library.cpp
│   ├── Utils.cpp
│   ├── main.cpp
│
├── data/
│   └── MediaVault.txt
│
└── README.md
``

Main Components
Date
Responsible for:

storing day, month, and year
formatting a date to string
parsing a date from string
validating dates
comparing dates for sorting

Item
Abstract base class for all media types.
Shared fields:

ID
title
added date
status

Shared behavior:

info()
serialize()
get_type()

Book
Derived from Item.
Additional fields:

author
pages

Movie
Derived from Item.
Additional fields:

director
duration

Game
Derived from Item.
Additional fields:

platform

Library
Central manager class for all item operations.
Responsibilities include:

adding items
removing items
searching
sorting
filtering
checkout / return
summary/statistics
save / load

Utils
Contains helper functions for:

safe integer input
safe string input
menu input
platform input
date input
menu display helpers

Exceptions
Contains custom exception types:

LibraryError
NotFoundError
InvalidOperationError

Build Instructions
Requirements

C++17 compatible compiler
Linux / Ubuntu (or compatible environment)
g++

Build
Run the following command from the project root:

g++ -std=c++17 -Wall -Wextra -pedantic -pthread -Iinclude src/*.cpp -o MediaVaultProject

Run

./MediaVaultProject

Usage
After running the program, the following menu appears:

Media Vault Menu
----------------------------
A. Add Item (Book / Movie / Game)
R. Remove Item
S. Search Item by ID
T. Search Item by Title
C. Checkout Item
U. Return Item
D. Display All Items
O. Sort Items
P. Print summary
F. Filter Items
Q. Quit
----------------------------

Menu Options

A → Add a new item
Choose the item type (Book, Movie, or Game) and enter the required details.

R → Remove an item by ID

S → Search for an item by ID

T → Search for items by title keyword
Search is case-insensitive.

C → Checkout an item
Only available items can be checked out.

U → Return an item
Only checked-out items can be returned.

D → Display all items

O → Sort items
Sorting options:

Title (Ascending / Descending)
Title Case-Insensitive (Ascending / Descending)
ID (Ascending / Descending)
Date (Ascending / Descending)

P → Print summary
Shows totals and status/type statistics.

F → Filter items
Filtering options:

Available items
CheckedOut items
Lost items
Books
Movies
Games

Q → Quit
Saves the current data before exiting.

Data Persistence
The application stores data in:
data/MediaVault.txt
``
When the program starts, it automatically loads saved items from the same file if it exists.

Example stored records
Book,1,Hello World,2026-05-20,Available,aaa,123
Movie,2,Brave Heart,2026-05-20,CheckedOut,www,120
Game,3,game 1,2026-05-20,Available,PlayStation
``
Input Validation
Date Input
Dates must be entered in the format:
YYYY-MM-DD
Example:
2026-05-20
``
The program validates:

correct format
valid month range
valid day range
correct number of days for each month
leap years

Examples:

2024-02-29 ✅ valid
2025-02-29 ❌ invalid
2026-04-31 ❌ invalid
2026-13-01 ❌ invalid

IDs

item IDs must be unique
duplicate IDs are rejected

Text Input

strings cannot be empty

Status Values
Each item can have one of the following statuses:

Available
CheckedOut
Lost

Status changes happen through:

checkout
return
loading previously saved items

Multithreading / Autosave
MediaVault includes a small multithreading feature:

a background autosave thread periodically saves the library to file
shared access to the library is protected using a mutex
an atomic flag is used to stop the autosave thread cleanly when quitting

This was implemented as a practical exercise in:

background tasks
synchronization
safe shared resource access
thread lifecycle management

Example Session

Enter your choice: A
Add (B)ook, (M)ovie, (G)ame: B
ID: 1
Title: Hello World
Added date (YYYY-MM-DD): 2026-05-20
Author: aaa
Pages: 123
Book added successfully.

Enter your choice: D
[Book]
ID: 1
Title: "Hello World"
Added: 2026-05-20
Status: Available
Author: aaa
Pages: 123
-----------------------

Design Notes
Some important design choices in this project:

Item is an abstract base class
Library stores items using:

std::vector<std::unique_ptr<Item>>

to support polymorphism and clear ownership
custom exceptions are used for clearer error handling
save/load uses a CSV-style text format
input/menu helpers are separated into Utils
autosave runs in the background using a dedicated thread

What I Learned

This project helped me practice how to build and improve a larger C++ application step by step, including:

structuring a multi-file C++ project
applying inheritance and polymorphism in practice
managing ownership using smart pointers
using STL algorithms for searching, sorting, and filtering
validating and parsing user input
implementing persistence with save/load
handling errors with custom exceptions
experimenting with multithreading in a practical, controlled way

## Author

Created as a personal C++ learning project.
