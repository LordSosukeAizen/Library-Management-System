#ifndef LIBRARY_SYSTEM_HPP
#define LIBRARY_SYSTEM_HPP

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class AccountDB;
class StudentsDB;
class FacultyDB;
class Account;
class Student;
class Faculty;
class Librarian;
class BooksDB; // Assuming BooksDB is defined elsewhere.

class Account {
public:
    string userid;
    vector<int> BorrowedBooks;
    vector<int> BorrowedHistory;
    int fine;
    vector<int> overDueBooks;

    Account() : fine(0) {}
};

class User {
protected:
    string password;

public:
    string username;
    string userid;
    int maxBooksBorrow;
    int finePerOverdue;
    bool manageAccess;
    int maxTimeperiod;



    string get_password() { return password; }
    void set_password(string pass) {
        password = pass;
    }
    void updateprofile() ;
};

class Student : public User {
public:
    Student() {
        username = "***";
        userid = "***";
        password = "***";
        maxBooksBorrow = 3;
        maxTimeperiod = 15;
        finePerOverdue = 10;
        manageAccess = false;
    }

    void borrowBook(int ISBN, AccountDB &acc_db, BooksDB &books_db) ;
    void returnBook(int ISBN, AccountDB &acc_db, BooksDB &books_db) ;
};

class Faculty : public User {
public:
    Faculty() {
        username = "***";
        userid = "***";
        password = "***";
        maxBooksBorrow = 5;
        maxTimeperiod = 30;
        finePerOverdue = 0;
        manageAccess = false;
    }
 
    void borrowBook(int ISBN, AccountDB &acc_db, BooksDB &books_db) ;
    void returnBook(int ISBN, AccountDB &acc_db, BooksDB &books_db) ;
};

class Librarian : public User {
public:
    Librarian(string username = "***", string password = "***", int maxBooksBorrow = 0, int maxTimeperiod = 0, int finePerOverdue = 0, bool manageAccess = true){};
    

    void deleteStudent(StudentsDB &student_db, AccountDB &acc_db);
    void deleteFaculty(FacultyDB &faculty_db, AccountDB &acc_db);
    void AddFaculty(FacultyDB &faculty_db, AccountDB& acc_db,StudentsDB& students_db);
    void AddStudent(StudentsDB &student_db, AccountDB& acc_db, FacultyDB &faculty_db);
    void AddBook(BooksDB &books_db);
    void DeleteBook(BooksDB &book_db);
    void PayFine(string userid, AccountDB &acc_db);
};

class AccountDB {
public:
    vector<Account> list;

    Account* Find(string userid);
    void Delete(string userid);
    void Populate(vector<string> account_lines);
    void Add(Account account);
};

class StudentsDB {
public:
    vector<Student> list;

    Student* Find(string userid);
    void Add(Student student);
    void Delete(string userid, AccountDB &acc_db);
    int students_count();
    void Show_students(AccountDB &acc_db);
    void Populate(vector<string> student_lines);
};

class FacultyDB {
public:
    vector<Faculty> list;

    Faculty* Find(string userid);
    void Add(Faculty faculty);
    void Delete(string userid, AccountDB &acc_db);
    int faculties_count();
    void Show_faculties(AccountDB &acc_db);
    void Populate(vector<string> faculty_lines);
};


class LibrarianDB {
    public:
        vector<Librarian> list;
        void Add(Librarian librarian);
        void Delete(string userid);
        void Populate(vector<string> librarian_lines);
        Librarian* Find(string userid);
        
    };
    
#endif // LIBRARY_SYSTEM_HPP
