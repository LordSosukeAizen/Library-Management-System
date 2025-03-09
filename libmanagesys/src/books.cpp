#include <bits/stdc++.h>
#include "../include/book.hpp"
using namespace std;




/////// BOOKS DB //////////

Books* BooksDB::Find(int ISBN) {
Books* dummy = NULL;
   for(auto &book: list) {
        if(book.ISBN == ISBN) {
            Books* temp = &book;
            return temp;
        }
   }
   // if not found return None Object
    return dummy;

}


void BooksDB::Add(string title, string author, string publisher, int ISBN) {
    Books book;
    book.title = title;
    book.author = author;
    book.publisher = publisher;
    book.ISBN = ISBN;
    book.availableStatus = "available";

    list.push_back(book);
}

void BooksDB::Delete(int ISBN) {
   
for(auto it=list.begin(); it!=list.end(); it++) {
    if(it->ISBN == ISBN) list.erase(it);   
}


}


int BooksDB::available_books_count() {
    int cnt = 0;
    for(Books book : list) {
        if(book.availableStatus == "available") cnt++;
    }
    return cnt;
};


void BooksDB::Show_All_Books() {
    cout << "ISBN"<< "      " <<"title" << "      " << "author" << "      " << "publisher" << "      " << "Status" << "\n"; 
    cout << "----------------------------------------\n";
    int cnt = 1;
    for(Books book: list) {
        cout << cnt<< ".    "<<book.ISBN << "      " <<book.title << "      " << book.author << "      " << book.publisher << "      " << book.availableStatus << "\n"; 
        cnt++;
    }
}

void BooksDB::Show_Available_books() {
cout << "title" << "      " << "author" << "      " << "publisher" << "      " << "ISBN" << "\n";
cout << "------------------------------------------------------------------------------------"<<"\n";
for(Books book : list) {
    if(book.availableStatus != "available") continue;
    cout << book.title << "      " << book.author << "      " << book.publisher << "      " << book.ISBN << "\n"; 
}
}


void BooksDB::Populate(vector<string> book_lines) {
    for(int i = 0; i < book_lines.size(); i += 7){
        Books book;
        try {
        book.ISBN = stoi(book_lines[i]);
        }
        catch (...) {
            cout << "Invalid type conversion at line " << i << "\n";
            cout << book_lines[i] << "\n";
            continue;
        }
        book.title = book_lines[i+1];
        book.author = book_lines[i+2];
        book.publisher = book_lines[i+3];
        book.availableStatus = book_lines[i+4];
        book.borrowed_on = stoi(book_lines[i+5]);
        list.push_back(book);
    }

}


