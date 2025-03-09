#include <bits/stdc++.h>
#include <ctime>
#include "../include/user.hpp"
#include "../include/book.hpp"
#include "books.cpp"
#include "save.cpp"
#include "functions.cpp"

using namespace std;



// User Update Profile

void User::updateprofile() {
    string newusername; string newpassword;
    string confirm_password;
    cout << "Enter username: "; cin >> newusername;
    do {
        cout << "Enter password: "; cin >> newpassword; 
        cout << "Confirm password: "; cin >> confirm_password;
        if(newpassword != confirm_password) {
            cout << "Passwords do not match. Please try again.\n";
        }
    }while(newpassword != confirm_password);

    if(newpassword != password) password = newpassword;
    if(newusername != username) username = username;
    

    cout << "\n User profile updated successfully.\n";
    
}


///////////////////////////// Student DB functionlties ////////////////////////

// Find Student
Student* StudentsDB::Find(string userid) {
    // for returning dummy object if student not found
Student* dummy = NULL;
    for(auto& student : list) {
        if(student.userid == userid) {
            Student* temp;
            temp = &student;
            return temp;
        }
    }

    // return None Object
    return dummy;   

}

// student count
int StudentsDB::students_count() {
    return list.size();
}

// show students
void StudentsDB::Show_students(AccountDB &acc) {
    cout << "User Name" << "         " << "Fine Overdue" <<"         " << "Current Books Borrowed"<< "\n";
    for(auto& student: list) {
        Account* studentAccount = acc.Find(student.userid);
        cout << student.username << "         " << studentAccount->fine <<"         " << studentAccount->BorrowedBooks.size()<< "\n";
    }
}

// Add student
void StudentsDB::Add(Student student) {
   list.push_back(student);

//    cout << "User is added with userid " << student.userid  << "\n";
}

// Delete student
void StudentsDB::Delete(string userid, AccountDB &acc_db) {
    for(auto it = list.begin(); it != list.end(); it++) {
        if(it->userid == userid) {
            list.erase(it);
            break;
        }
    }
    
acc_db.Delete(userid);
// save the list again into the file.

    cout << "User is deleted with userid " << userid  << "\n";
}

// Populate student
void StudentsDB::Populate(vector<string> student_lines) {
   
    for(int i = 0; i < student_lines.size(); i += 8){
        Student student;
        student.userid = student_lines[i];
        student.username = student_lines[i+1];
        student.set_password(student_lines[i+2]);
        student.finePerOverdue = stoi(student_lines[i+3]);
        student.manageAccess = stoi(student_lines[i+4]);
        student.maxBooksBorrow = stoi(student_lines[i+5]);
        student.maxTimeperiod = stoi(student_lines[i+6]);
        list.push_back(student);
    }


}
//////////////////////////// Faculty db Functionalities /////////////////////////

Faculty* FacultyDB::Find(string userid) {
    Faculty* dummy = NULL;
        for(auto& faculty : list) {
            if(faculty.userid == userid) {
                Faculty* temp;
                temp = &faculty;
                return temp;
            }
        }
    
        // return None Object
        return dummy;   
    }
int FacultyDB::faculties_count() {
        return list.size();
    }
void FacultyDB::Show_faculties(AccountDB &acc) {
        cout << "User Name" << "         " << "Current Books Borrowed"<< "\n";
        for(auto& student: list) {
            Account* studentAccount = acc.Find(student.userid);
            cout << student.username << "         " << studentAccount->BorrowedBooks.size()<< "\n";
        }
    }
void FacultyDB::Add(Faculty faculty) {
        list.push_back(faculty);
 
       cout << "Faculty is added with userid " << faculty.userid  << "\n";
     }
void FacultyDB::Delete(string userid, AccountDB &acc_db) {
         for(auto it = list.begin(); it != list.end(); it++) {
             if(it->userid == userid) {
                 list.erase(it);
                 break;
             }
         }
         acc_db.Delete(userid);
         cout << "faculty is deleted with userid " << userid  << "\n";
     }
void FacultyDB::Populate(vector<string> faculty_lines) {
    try {
    for(int i = 0; i < faculty_lines.size(); i += 8){
        Faculty faculty;
        faculty.userid = faculty_lines[i];
        faculty.username = faculty_lines[i+1];
        faculty.set_password(faculty_lines[i+2]);
        faculty.finePerOverdue = stoi(faculty_lines[i+3]);
        faculty.manageAccess = stoi(faculty_lines[i+4]);
        faculty.maxBooksBorrow = stoi(faculty_lines[i+5]);
        faculty.maxTimeperiod = stoi(faculty_lines[i+6]);
        list.push_back(faculty);
    }
}
catch (...) {
    return;
}
}
//////////////////////// Account DB /////////////////////////////
Account* AccountDB::Find(string userid) {
    Account *dummy = NULL;
    for(auto& acc: list) {
        if(acc.userid == userid) {
            Account* temp;
            temp = &acc;
            return temp;
        }
    }
    return dummy;
}
void AccountDB::Delete(string userid) {
    for(auto it = list.begin(); it!=list.end(); it++) {
        if(it->userid == userid) {
            list.erase(it);
            break;
        }
    }
}

void AccountDB::Populate(vector<string> account_lines) {
    try {
    for(int i = 0; i < account_lines.size(); i += 6){
        Account acc;
        acc.userid = account_lines[i];
        acc.fine = stoi(account_lines[i+1]);
        acc.BorrowedBooks = create_list(account_lines[i+2]);
        acc.BorrowedHistory = create_list(account_lines[i+3]);
        acc.overDueBooks = create_list(account_lines[i+4]);
        list.push_back(acc);
    }
}
catch (...) {
    return;
}
}

void AccountDB::Add(Account account) {
    list.push_back(account);

 }



 /////////////// Student request and return book functions //////////////////////
 
// borrow book from the current available Library books 
void Student::borrowBook(int ISBN, AccountDB &acc_db, BooksDB &books_db) {
    Account* studentAccount = acc_db.Find(this->userid);
    Books* book = books_db.Find(ISBN);
    if(!book) {
        cout << "Book not found\n";
        return;
    }
    // check book is available or not
        if(book->availableStatus != "available") {
            cout << "Book is " << book->availableStatus << "\n";
            return;
        }

    // If past fine is not payed yet
    if(studentAccount->fine > 0) {
        cout << "Book can't be borrowed until past fine is payed\n";
        return;
    }
    // Create a timestamp for right now
    struct tm date;
    time_t now;
    time(&now);
   // make book reserved and fill the time
    studentAccount->BorrowedBooks.push_back(ISBN);
    book->availableStatus = "reserved";
    book->borrowed_on = now;
}

// return book
void Student::returnBook(int ISBN, AccountDB& acc_db, BooksDB &books_db) {

    // find student account using userid
    Account* studentAccount = acc_db.Find(this->userid);
    Books* book = books_db.Find(ISBN);
    

    
    int diffsec, diffdays;
    for(auto it= studentAccount->BorrowedBooks.begin(); it != studentAccount->BorrowedBooks.end(); it++) {
        if(*it == ISBN) {
            // create timestamp
            struct tm date;
            time_t now;
            time(&now);

            //  calculate fine
            diffsec = now - book->borrowed_on;
            diffdays = diffsec/86400;
            
            studentAccount->fine += (max(0, diffdays-this->maxTimeperiod) * this->finePerOverdue);
            studentAccount->BorrowedBooks.erase(it);
            studentAccount->BorrowedHistory.push_back(ISBN);
            // make book available
            book->availableStatus = "available";
            book->borrowed_on = -1;
            return;
        }
    }

    cout << "This book is not borrowed by you\n";
    


}


//////////////// Faculty borrowbook and returnbook ///////////////////////


// borrow book
void Faculty::borrowBook(int ISBN, AccountDB& acc_db, BooksDB &books_db) {
    Books* book = books_db.Find(ISBN);
    Account* facultyAccount = acc_db.Find(this->userid);
    if(book->availableStatus != "available") {
        cout << "Book is " << book->availableStatus << "\n";
        return;
    }
    
    // Create a timestamp for right now
    struct tm date;
    time_t now;
    time(&now);
    // make book reserved
    facultyAccount->BorrowedBooks.push_back(ISBN);
    book->availableStatus = "reserved";
}


// return book
void Faculty::returnBook(int ISBN, AccountDB& acc_db, BooksDB &books_db) {
    Account* facultyAccount = acc_db.Find(this->userid);
    Books* book = books_db.Find(ISBN);


    for(auto it = facultyAccount->BorrowedBooks.begin(); it != facultyAccount->BorrowedBooks.end(); it++) {
      if(*it == ISBN) {
        facultyAccount->BorrowedBooks.erase(it);
        book->availableStatus = "available";
        book->borrowed_on = -1;
        facultyAccount->BorrowedHistory.push_back(ISBN);
        return;
      }
    }

cout << "This is book is not borrowed by you\n";
}




//////////  Libriran database functions ////////////////




// Add book to Library

void Librarian::AddBook(BooksDB &books_db) {
    string title, author, publisher;
    int ISBN;

    cout << "Enter title of the book: ";
    cin >> title;
    cout << "Enter ISBN: ";
    cin >> ISBN;
    cout << "Enter name of author : ";
    cin >> author;
    cout << "Enter name of the publisher: ";
    cin >> publisher;
    books_db.Add(title, author, publisher, ISBN);
}

// Delete book from Library
void Librarian::DeleteBook(BooksDB &books_db) {
    int ISBN;
    string conformation;
    
    cout << "Enter ISBN of for Deletion: ";
    cin >> ISBN;
    cout << "Are you sure for deleting this book (y/N)";
    cin >> conformation;
    if(conformation == "y" || conformation == "yes") {
        try {
            books_db.Delete(ISBN);
        }catch(...) {
            cout << "Problem in deletion of the book";
        }
    }
    return;
}

// Add Student
void Librarian::AddStudent(StudentsDB &students_db, AccountDB& acc_db, FacultyDB& faculty_db) {

    string username, userid, password, conf_password;
    
    cout << "Enter username: ";
    cin >> username;

    
    cout << "Enter UserId: ";
    cin >> userid;
    Student new_student;
    Account acc;
    Student* student = students_db.Find(userid);
    Faculty* faculty = faculty_db.Find(userid);
    while(student != NULL || faculty != NULL) {
        cout << "User already exist with Userid" << userid << "\n";
        cout << "Enter UserId: ";
        cin >> userid;
        student = students_db.Find(userid);
        Faculty* faculty = faculty_db.Find(userid);
    }
    do {
        
        cout << "Create a Password: ";
        cin >> password;
        cout << "Confirm Password: ";
        cin >> conf_password;
        if(password != conf_password){
            cout<<"Passwords do not match ! Please try again.\n";
        }
    }while(password != conf_password);

    new_student.userid = userid;
    new_student.username = username;
    new_student.set_password(password);

    students_db.list.push_back(new_student);
    acc.userid = userid;
    acc_db.Add(acc);
}

// Add Faculty
void Librarian::AddFaculty(FacultyDB & faculty_db, AccountDB& acc_db, StudentsDB& students_db) {

    string username, userid, password, conf_password;
    
    cout << "Enter username: ";
    cin >> username;

    
    cout << "Enter UserId: ";
    cin >> userid;
    Faculty new_faculty;
    Account acc;
    Faculty* faculty = faculty_db.Find(userid);
    Student* student = students_db.Find(userid);
    while(faculty != NULL || student != NULL) {
        cout << "User already exist with Userid" << userid << "\n";
        cout << "Enter UserId: ";
        cin >> userid;
        faculty = faculty_db.Find(userid);
        student = students_db.Find(userid);
    }
    do {
        
        cout << "Create a Password: ";
        cin >> password;
        cout << "Confirm Password: ";
        cin >> conf_password;
        if(password != conf_password){
            cout<<"Passwords do not match ! Please try again.\n";
        }
    }while(password != conf_password);

    new_faculty.userid = userid;
    new_faculty.username = username;
    new_faculty.set_password(password);
    faculty_db.list.push_back(new_faculty);
    acc.userid = userid;
    acc_db.Add(acc);
}

// Delete User
void Librarian::deleteStudent(StudentsDB &students_db, AccountDB& acc_db) {
    string userid;
    string conformation;
    cout << "Enter the UserID: ";
    cin >> userid;
    cout << "Are you Sure you want to Delete this User[y/N]";
    cin >> conformation;
    if(conformation == "y" || conformation == "yes") {
        students_db.Delete(userid, acc_db);
    }
    return;
}

// Delete User
void Librarian::deleteFaculty(FacultyDB &faculty_db, AccountDB& acc_db) {
    string userid;
    string conformation;
    cout << "Enter the UserID: ";
    cin >> userid;
    cout << "Are you Sure you want to Delete this User[y/N]";
    cin >> conformation;
    if(conformation == "y" || conformation == "yes") {
        faculty_db.Delete(userid, acc_db);
    }
    return;
}


// Add Librarian
void LibrarianDB::Add(Librarian librarian) {    
    list.push_back(librarian);
}

// Delete Librarian
void LibrarianDB::Delete(string userid) {
    for(int i = 0; i < list.size(); i++) {
        if(list[i].userid == userid) {
            list.erase(list.begin() + i);
            return;
        }
    }
   
}

// Populate
void LibrarianDB::Populate(vector<string> librarian_lines) {
    for(int i = 0; i < librarian_lines.size(); i += 8){
        Librarian lib;
        lib.userid = librarian_lines[i];
        lib.username = librarian_lines[i+1];
        lib.set_password(librarian_lines[i+2]);
        lib.finePerOverdue = stoi(librarian_lines[i+3]);
        lib.manageAccess = stoi(librarian_lines[i+4]);
        lib.maxBooksBorrow = stoi(librarian_lines[i+5]);
        lib.maxTimeperiod = stoi(librarian_lines[i+6]);
        list.push_back(lib);
    }
}

// Find
Librarian* LibrarianDB::Find(string userid) {
    Librarian* dummy = NULL;
   for(auto& lib: list) {
      if(lib.userid == userid) {   
          Librarian* temp = &lib;
          return temp;
      }
   }
    return dummy;

}



// Pay Fine
void Librarian::PayFine(string userid, AccountDB &acc_db) {
Account* acc = acc_db.Find(userid);
int pay;
cout << "Enter the Amount User payed: ";
cin >> pay;
acc->fine -= pay;
}