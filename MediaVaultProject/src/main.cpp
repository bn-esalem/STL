
#include "Book.h"
#include <iostream>

int main() {
    Date d(19, 5, 2026);
    Book b(101, "Clean Code", d, "Robert Martin", 464);

   // std::cout << b << "\n";         // uses Item operator<<
    std::cout << b.info() << "\n";

  
    return 0;
}   