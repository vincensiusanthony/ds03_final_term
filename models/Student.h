#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "../models/Book.h"

struct Student {
    std::string nim;
    std::string name;
    std::string password;
    std::vector<int> borrowedBookIds; // In-memory tracking of borrowed book IDs

    Student() = default;
    Student(const std::string& nim, const std::string& name, const std::string& password)
        : nim(nim), name(name), password(password) {}
};

#endif // STUDENT_H