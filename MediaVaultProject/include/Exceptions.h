#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <stdexcept>
#include <string>

class LibraryError : public std::runtime_error {
public:
    explicit LibraryError(const std::string& msg)
        : std::runtime_error(msg) {}
};

class NotFoundError : public LibraryError {
public:
    explicit NotFoundError(const std::string& msg)
        : LibraryError("Not found: " + msg) {}
};

class InvalidOperationError : public LibraryError{
public:
    explicit InvalidOperationError(const std::string &msg)
        : LibraryError("Invalid operation: " + msg) {}
};

#endif