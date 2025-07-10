#ifndef BOOK_H
#define BOOK_H

#include <string>

struct Book {
    int id;
    std::string title;
    std::string author;
    bool isBorrowed;

    Book() : id(0), title(""), author(""), isBorrowed(false) {}
    Book(int id, const std::string& title, const std::string& author)
        : id(id), title(title), author(author), isBorrowed(false) {}
};

#endif // BOOK_H