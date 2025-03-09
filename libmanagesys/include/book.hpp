#ifndef BOOK_HPP
#define BOOK_HPP
#include <bits/stdc++.h>

using namespace std;

// title, author, publisher, year, and ISBN
class Books
{

public:
    int ISBN;
    string availableStatus;
    string title;
    string author;
    string publisher;
    int borrowed_on;
};

class BooksDB
{
public:
    vector<Books> list; // List of books  objects in the database

    Books *Find(int ISBN);
    void Add(string title, string author, string publisher, int ISBN);
    void Delete(int ISBN);
    int available_books_count();
    void Show_Available_books();
    void Show_All_Books();
    void makeAvailable(vector<string> books);
    void Populate(vector<string> book_lines);
};
#endif
