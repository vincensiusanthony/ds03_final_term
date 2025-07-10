#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include "models/Student.h"
#include "models/Book.h"
#include "models/ActivityLog.h"
#include "structures/HashTable.h"
#include "structures/Queue.h"
#include "structures/Stack.h"
#include "structures/LinkedList.h"
#include "structures/BST.h"
#include "structures/Graph.h"
#include "utils/helper.h"

// Aliases for structures
using StudentTable = HashTable<std::string, Student>;
using BookTable = HashTable<int, Book>;
using ActivityList = LinkedList<ActivityLog>;
using ActivityStack = Stack<ActivityLog>;
using ConsultQueue = Queue<std::string>; // NIM

// Simple global data for demo
StudentTable students;
BookTable books;
BST bookBST;
Graph campusGraph;
ConsultQueue consultQueue;
HashTable<std::string, ActivityList> studentActivities; // NIM to activity logs
HashTable<std::string, ActivityStack> studentActivityStacks; // NIM to activity stacks

// PATCH: Loader dummy data
void loadBooks(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cout << "Gagal membuka " << filename << "\n";
        return;
    }
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string idStr, title, author;
        if (std::getline(iss, idStr, '|') && std::getline(iss, title, '|') && std::getline(iss, author)) {
            int id = std::stoi(idStr);
            Book b(id, title, author);
            books.insert(id, b);
            bookBST.insert(b);
        }
    }
}

void loadStudents(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cout << "Gagal membuka " << filename << "\n";
        return;
    }
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string nim, name, password;
        if (std::getline(iss, nim, '|') && std::getline(iss, name, '|') && std::getline(iss, password)) {
            students.insert(nim, Student(nim, name, password));
        }
    }
}

void loadGraph(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cout << "Gagal membuka " << filename << "\n";
        return;
    }
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string from, to, distStr;
        if (std::getline(iss, from, '|') && std::getline(iss, to, '|') && std::getline(iss, distStr)) {
            int dist = std::stoi(distStr);
            campusGraph.addEdge(from, to, dist);
        }
    }
}

// PATCH: Ubah seedData agar load dari file
void seedData() {
    loadStudents("data/dummy_students.txt");
    loadBooks("data/dummy_books.txt");
    loadGraph("data/dummy_graph.txt");
}

// --- FUNGSI UTAMA DAN MENU ---

Student* login() {
    std::string nim, pass;
    std::cout << "NIM: "; std::cin >> nim;
    std::cout << "Password: "; std::cin >> pass;
    auto opt = students.get(nim);
    if (!opt.has_value() || opt->password != pass) {
        std::cout << "Login gagal.\n";
        return nullptr;
    }
    std::cout << "Selamat datang, " << opt->name << "!\n";
    return students.getMutable(nim);
}

void menu(Student* currentStudent) {
    while (true) {
        std::cout << "\n--- Menu SmartStudent ---\n";
        std::cout << "1. Ambil antrean konsultasi akademik\n";
        std::cout << "2. Pinjam buku\n";
        std::cout << "3. Lihat aktivitas mahasiswa\n";
        std::cout << "4. Navigasi kampus\n";
        std::cout << "5. Lihat daftar buku (terurut judul)\n";
        std::cout << "6. Cari buku berdasarkan ID\n";
        std::cout << "7. Logout\n";
        std::cout << "Pilih menu: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 1) {
            consultQueue.enqueue(currentStudent->nim);
            if (!studentActivities.exists(currentStudent->nim))
                studentActivities.insert(currentStudent->nim, ActivityList());
            if (!studentActivityStacks.exists(currentStudent->nim))
                studentActivityStacks.insert(currentStudent->nim, ActivityStack());

            ActivityLog alog("Ambil antrean konsultasi akademik");
            auto& acts = *studentActivities.getMutable(currentStudent->nim);
            auto& stack = *studentActivityStacks.getMutable(currentStudent->nim);
            acts.push_back(alog);
            stack.push(alog);

            std::cout << "Anda telah mengambil antrean konsultasi. (Antrean: " << currentStudent->nim << ")\n";
        } else if (choice == 2) {
            int id;
            std::cout << "ID buku: ";
            std::cin >> id;
            auto optBook = books.get(id);
            if (optBook.has_value() && !optBook->isBorrowed) {
                Book book = optBook.value();
                book.isBorrowed = true;
                books.insert(id, book);

                currentStudent->borrowedBookIds.push_back(id);

                std::string msg = "Pinjam buku: " + book.title;
                ActivityLog log(msg);

                if (!studentActivities.exists(currentStudent->nim))
                    studentActivities.insert(currentStudent->nim, ActivityList());
                if (!studentActivityStacks.exists(currentStudent->nim))
                    studentActivityStacks.insert(currentStudent->nim, ActivityStack());

                auto& acts = *studentActivities.getMutable(currentStudent->nim);
                auto& stack = *studentActivityStacks.getMutable(currentStudent->nim);
                acts.push_back(log);
                stack.push(log);

                std::cout << "Buku berhasil dipinjam: " << book.title << std::endl;
            } else {
                std::cout << "Buku tidak tersedia.\n";
            }
        } else if (choice == 3) {
            std::cout << "1. Lihat aktivitas kronologis (Linked List)\n";
            std::cout << "2. Lihat aktivitas terbaru (Stack)\n";
            std::cout << "Pilih: ";
            int m;
            std::cin >> m;

            if (!studentActivities.exists(currentStudent->nim))
                studentActivities.insert(currentStudent->nim, ActivityList());
            if (!studentActivityStacks.exists(currentStudent->nim))
                studentActivityStacks.insert(currentStudent->nim, ActivityStack());

            if (m == 1) {
                auto& acts = *studentActivities.getMutable(currentStudent->nim);
                acts.printAll([](const ActivityLog& log) {
                    std::cout << "- ";
                    printTime(log.timestamp);
                    std::cout << " : " << log.activity << std::endl;
                });
            } else if (m == 2) {
                auto& s = *studentActivityStacks.getMutable(currentStudent->nim);
                Stack<ActivityLog> temp = s;
                while (!temp.isEmpty()) {
                    auto log = temp.pop();
                    std::cout << "- ";
                    printTime(log.timestamp);
                    std::cout << " : " << log.activity << std::endl;
                }
            }
        } else if (choice == 4) {
            campusGraph.printLocations();
            std::string from, to;
            std::cout << "Lokasi awal: "; std::getline(std::cin, from);
            std::cout << "Lokasi tujuan: "; std::getline(std::cin, to);
            campusGraph.printShortestPath(from, to);
        } else if (choice == 5) {
            std::cout << "Daftar buku (urut judul):\n";
            bookBST.inOrder([](const Book& book) {
                std::cout << "- [" << book.id << "] " << book.title << " oleh " << book.author;
                if (book.isBorrowed) std::cout << " (Dipinjam)";
                std::cout << std::endl;
            });
        } else if (choice == 6) {
            int id;
            std::cout << "ID buku: ";
            std::cin >> id;
            auto opt = books.get(id);
            if (opt.has_value()) {
                std::cout << "Judul: " << opt->title << "\nPenulis: " << opt->author;
                std::cout << (opt->isBorrowed ? " [Dipinjam]" : " [Tersedia]") << std::endl;
            } else {
                std::cout << "Buku tidak ditemukan.\n";
            }
        } else if (choice == 7) {
            std::cout << "Logout...\n";
            break;
        } else {
            std::cout << "Menu tidak valid.\n";
        }
    }
}

int main() {
    seedData();
    std::cout << "==== SmartStudent - Kampus Cakrawala ====\n";
    while (true) {
        std::cout << "\n1. Login Mahasiswa\n2. Keluar\nPilih: ";
        int m; std::cin >> m;
        if (m == 1) {
            Student* s = login();
            if (s) menu(s);
        } else if (m == 2) {
            std::cout << "Sampai jumpa!\n";
            break;
        }
    }
    return 0;
}