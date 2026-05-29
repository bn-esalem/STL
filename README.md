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

Build Instructions
Requirements

C++17
g++

Build
g++ -std=c++17 -Wall -Wextra -pedantic -pthread -Iinclude src/*.cpp -o MediaVaultProject

Run
./MediaVaultProject

Usage
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

Data Persistence
Data is stored in:
data/MediaVault.txt

Multithreading / Autosave

Background autosave thread saves data periodically
Mutex protects shared access to the library
Atomic flag ensures clean shutdown

Example Session
Enter your choice: A
Add (B)ook: B
ID: 1
Title: Hello World
Book added successfully.

Author
Created as a personal C++ learning project.