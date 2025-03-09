#include <bits/stdc++.h>

#include "user.cpp"


using namespace std;
/*

TODOS:


*/

int main(){



AccountDB account_db;
StudentsDB students_db;
FacultyDB faculty_db;
BooksDB books_db;
LibrarianDB librarian_db;

cout<<"Fetching data from the database...\n";
    
// Read data from the text files
vector<string> book_lines;
vector<string> students_lines;
vector<string> accounts_lines;
vector<string> faculty_lines;
vector<string> librarian_lines;
try {
 book_lines = Read_From_File("../db/Books.txt");
 students_lines = Read_From_File("../db/students.txt");
 accounts_lines = Read_From_File("../db/accounts.txt");
 faculty_lines = Read_From_File("../db/faculty.txt");
 librarian_lines = Read_From_File("../db/librarians.txt");
}catch (...) {
  cout << "Error reading from file\n";
  return 1;
}



// Populate the Database objects from the text files
books_db.Populate(book_lines);
cout << "Books fetched successfully!\n";
students_db.Populate(students_lines);
cout << "Students fetched successfully!\n";
faculty_db.Populate(faculty_lines);
cout << "Faculty fetched successfully!\n";
account_db.Populate(accounts_lines);
cout << "Accounts fetched successfully!\n";
librarian_db.Populate(librarian_lines);
cout << "Librarians fetched successfully!\n";

// Welcome message. Program starts.
cout<<"Welcome to Library Management System !\n";
cout<<"\nPress Enter to continue...";
cin.get();

int logged_in_user = -1;



bool end_prog = false; // program ends when end_prog becomes true.
while(!end_prog){

  Student* login_student;
  Faculty* login_faculty;
  Librarian* login_librarian;

    bool logged_in = false; // user is logged out when logged_in is false, and logged in when it is true.
    cout<<endl;

    // Ask the user whether he/she wants to register or login
   
    int choice;
    do {
      cout<<"1. Register\n2. Login\n3. Exit\n";
      cout << "Enter your choice: ";
      cin>>choice;
      if(choice < 1 || choice > 3) {
          cout<<"Invalid choice\n";
      }
      }while(choice < 1 || choice > 3);
    cin.ignore();

    switch(choice){


        // Register
        case 1:
            cout<<"You have chosen to register\n";
            int choice2;
            do {
            cout<<"1. Register as Librarian\n2. Register as Student\n3. Register as Faculty\n";
            cin>>choice2;
            if(choice2 < 1 || choice2 > 3) {
                cout<<"Invalid choice\n";
            }
            }while(choice2 < 1 || choice2 > 3);
            cin.ignore();
            
            switch(choice2){
              // Register as Librarian
                case 1: {
                      
                      string userid;
                        string username; string password; string conf_password;
                        cout << "Enter username: "; cin >> username;
                        cout << "Enter userid: "; cin >> userid;
                        while(librarian_db.Find(userid) != NULL) {
                            cout << "User already exist with Userid: " << userid << "\n";
                            cout << "Enter userid: ";
                            cin >> userid;
                        }

                        do {
                        cout << "Enter password: "; cin >> password;
                        cout << "Confirm password: "; cin >> conf_password;
                        if(password != conf_password){
                            cout<<"Passwords do not match ! Please try again.\n";
                        }
                        }while(password != conf_password);
                        Librarian new_librarian;
                        new_librarian.userid = userid;
                        new_librarian.username = username;
                        new_librarian.set_password(password);
                        librarian_db.Add(new_librarian);
                      

                        break;
                    }

                // Register as Student
                case 2: {
                        string username; string userid; string password; string conf_password;
                        cout << "Enter username: "; cin >> username;
                        cout << "Enter userid: "; cin >> userid;
                        while(students_db.Find(userid) != NULL || faculty_db.Find(userid) != NULL) {
                            cout << "User already exist with Userid: " << userid << "\n";
                            cout << "Enter userid: ";
                            cin >> userid;
                        }
                        do {
                        cout << "Enter password: "; cin >> password;
                        cout << "Confirm password: "; cin >> conf_password;
                        if(password != conf_password){
                            cout<<"Passwords do not match ! Please try again.\n";
                        }
                        }while(password != conf_password);
                        Student student;
                        Account student_account;
                        student.userid = userid;
                        student.username = username;
                        student.set_password(password);
                        students_db.Add(student);
                        student_account.userid = userid;
                        account_db.Add(student_account);

                        break;
                      }

                // Register as Faculty
                case 3: {
                        string username; string userid; string password; string conf_password;
                        cout << "Enter username: "; cin >> username;
                        cout << "Enter userid: "; cin >> userid;
                        while(faculty_db.Find(userid) != NULL || students_db.Find(userid) != NULL) {
                            cout << "User already exist with Userid: " << userid << "\n";
                            cout << "Enter userid: ";
                            cin >> userid;
                        }
                        do {
                        cout << "Enter password: "; cin >> password;
                        cout << "Confirm password: "; cin >> conf_password;
                        if(password != conf_password){
                            cout<<"Passwords do not match ! Please try again.\n";
                        }
                        }while(password != conf_password);
                        Faculty faculty;
                        Account faculty_account;
                        faculty.userid = userid;
                        faculty.username = username;
                        faculty.set_password(password);
                        faculty_db.Add(faculty);
                        faculty_account.userid = userid;
                        account_db.Add(faculty_account);
                        break;
                      }
            }
            break;


        // Login
        case 2: {
            cout<<"You have chosen to login\n";
            logged_in = false;
            int choice2;
            cout << "1.Login as Librarian\n2.Login as Student\n3.Login as Faculty\n";
            cin >> choice2;
            cin.ignore();
            switch(choice2){
                case 1: {
                    string userid; string password;
                    do {
                    cout << "Enter userid: "; cin >> userid;
                    cout << "Enter password: "; cin >> password;
                    Librarian librarian = librarian_db.list[0]; 
                    if(librarian.userid == userid && librarian.get_password() == password) {
                        logged_in = true;
                        logged_in_user = 1;
                        login_librarian = &librarian;
                    }
                    else {
                        cout << "Invalid credentials Try again\n";
                        cin.get();
                    }
                  }while(!logged_in);
                    break;
                  }

                case 2: {
                  string username; string password;
                    do {
                    cout << "Enter username: "; cin >> username;
                    cout << "Enter password: "; cin >> password;
                    
                    Student* student = students_db.Find(username);
                    if(student != NULL && student->get_password() == password) {
                        logged_in = true;
                        logged_in_user = 2;
                        login_student = student;
                    }
                    else {
                        cout << "Invalid credentials Try again\n";
                        cin.get();
                    }
                  }while(!logged_in);
                    break;
                  }

                  case 3: {
                  string username; string password;
                    do {
                    cout << "Enter username: "; cin >> username;
                    cout << "Enter password: "; cin >> password;
                    
                    Faculty* faculty = faculty_db.Find(username);
                    if(faculty != NULL && faculty->get_password() == password) {
                        logged_in = true;
                        logged_in_user = 3;
                        login_faculty = faculty;
                    }
                    else {
                        cout << "Invalid credentials Try again\n";
                        cin.get();
                    }
                  }while(!logged_in);
                    break;
                  }
                }      
            break;
              }


        // EXIT
        case 3:
            end_prog = true;
            break;
        }
// If user is logged in
    while(logged_in) {
      // Based on type of user logged in
        switch(logged_in_user) {
        
          // Librarian
          case 1: {
          do {
            cout << "Librarian\n";
             cout << "Hello "<< login_librarian->username << "\n";
             while(logged_in) {
              cout << "1.Profile\n2.Manage Users\n3.Manage Books\n4.Logout\n";
              cout << "Enter your choice: ";
              int acc; cin >> acc;
              switch(acc) {
              // update profile
                case 1: {
                  login_librarian->updateprofile();
                  break;
                }
              // Manage Users
                case 2: {
                  int mng;
                  cout << "1.Add Student\n2.Delete Users\n3.Add Faculty\n4.Delete Faculty\n5.Pay Fees\n";
                  cout << "Enter your choice: "; cin >> mng;
                  switch(mng) {
                    case 1:  
                         login_librarian->AddStudent(students_db, account_db, faculty_db);
                         break;
                    case 2: 
                          login_librarian->deleteStudent(students_db, account_db);
                          break;
                    case 3: 
                          login_librarian->AddFaculty(faculty_db, account_db, students_db);
                          break;
                    case 4:
                          login_librarian->deleteFaculty(faculty_db, account_db);
                          break;
                    case 5: 
                          login_librarian->PayFine(login_student->userid, account_db);
                          break;
                    default: 
                          break;
                  }

                break;
                }
              // Manage Books
                case 3: {
                  int mng;
                  cout << "1.Add Books\n2. Delete Books\n3.Show All Books\n4.Show Available Books\n";
                  cin >> mng;
                  switch(mng) {
                    case 1: {
                      login_librarian->AddBook(books_db);
                      break;
                    }
                    case 2: {
                      login_librarian->DeleteBook(books_db);
                      break;
                    }
                    case 3: {
                       books_db.Show_All_Books();
                       break;
                    }
                    case 4: {
                      cout << "Total " << books_db.available_books_count() << "are availbale\n";
                      books_db.Show_Available_books();
                    }
                    default: break;
                  }
                break;

                }
                // Logout
                case 4: {
                  logged_in = false;
                  end_prog = true;
                  login_librarian = NULL;
                  break;
                }
              // Default
              default: {
                cout << "Invalid choice try again\n";
              }
              }

             }
             
          }while(logged_in);
          break;
          }

          // Student
          case 2: {
          do {
            
          
            cout << "Student\n";
            cout << "Hello "<< login_student->username << "\n";
             while(logged_in) {
              cout << "1.Manage Profile\n2.View Account\n3.Borrow Book\n4.Return Book\n5.Show Available Books\n6.Logout\n";
              cout << "Enter your choice: ";
              int acc; cin >> acc;
              switch(acc) {
                // update profile
                case 1: {
                  login_student->updateprofile();
                  break;
                }

                // View Account
                case 2: {
                 Account* stdAcc = account_db.Find(login_student->userid);
                 cout << "Your Total Fine : " << stdAcc->fine << "\n";
                 int cnt = 1;
                 try {
                 for(auto isbn: stdAcc->BorrowedBooks) {
                  Books* book = books_db.Find(isbn);
                  cout << cnt << ".  " << book->title << "  " << book->ISBN << "\n";
                  cnt++;
                 } 
                }catch(...) {
                  cout << "No Books Borrowed in yout currect account\n";
                }
                break;
                }

                // Borrow Book
                case 3: {

                  int numBooks;


                  do{
                    cout << "Number of Books: ";
                    cin >> numBooks;
                    if(numBooks > login_student->maxBooksBorrow) {
                    cout << "Max " <<  login_student->maxBooksBorrow << " can be borrowed\n";
                    }
                  } while(numBooks > login_student->maxBooksBorrow);
              
                for(int i=1; i<=numBooks; i++) {
                  int isbn;
                  cout << "Enter ISBN: "; cin >> isbn;
                  login_student->borrowBook(isbn, account_db, books_db);
                }
                  break;
                }
                 
                // Return Book
                case 4: {
                  int numBooks;
                  cout << "Number of Books: ";
                  cin >> numBooks;
              
                for(int i=1; i<=numBooks; i++) {
                  int isbn;
                  cout << "Enter ISBN: "; cin >> isbn;
                  login_student->returnBook(isbn, account_db, books_db);
                }
                  break;
                }
              // Show Available Books for borrwing
              case 5: {
                cout << "Total " << books_db.available_books_count() << "are availbale\n";
                books_db.Show_Available_books();
                break;
              }
              // Logout
              case 6: {
                logged_in = false;
                login_student = NULL;
                end_prog = true;
                break;
              }
              default: {
                cout << "Invalid choice try again\n";
              }
              }

             }
         

          }while(logged_in);
          break;
        }


          case 3: {
            do {
            cout << "Faculty\n";
            cout << "Hello "<< login_faculty->username << "\n";
             while(logged_in) {
              cout << "1.Manage Profile\n2.View Account\n3.Borrow Book\n4.Return Book\n5.Show Available Books";
              cout << "any other can be used for logout";
              int acc; cin >> acc;
              switch(acc) {
                case 1: {
                  login_faculty->updateprofile();
                  break;
                }

                case 2: {
                 Account* stdAcc = account_db.Find(login_faculty->userid);
                 int cnt = 1;
                 for(auto isbn: stdAcc->BorrowedBooks) {
                  Books* book = books_db.Find(isbn);
                  cout << cnt << ".  " << book->title << "  " << book->ISBN << "\n";
                  cnt++;
                 } 
                break;
                }

                case 3: {

                  int numBooks;
                  do{
                    cout << "Number of Books :";
                    cin >> numBooks;
                    if(numBooks > login_faculty->maxBooksBorrow) {
                    cout << "Max " <<  login_faculty->maxBooksBorrow << " can be borrowed";
                    }
                  } while(numBooks > login_faculty->maxBooksBorrow);
              
                for(int i=1; i<=numBooks; i++) {
                  int isbn;
                  cout << "Enter ISBN: "; cin >> isbn;
                  login_faculty->borrowBook(isbn, account_db, books_db);
                }
                  break;
                }
                 

                case 4: {
                  int numBooks;
                  cout << "Number of Books: ";
                  cin >> numBooks;
              
                for(int i=1; i<=numBooks; i++) {
                  int isbn;
                  cout << "Enter ISBN: "; cin >> isbn;
                  login_faculty->returnBook(isbn, account_db, books_db);
                }
                  break;
                }

              case 5: {
                cout << "Total " << books_db.available_books_count() << "are availbale\n";
                books_db.Show_Available_books();
                break;
              }

              default: {
                logged_in = false;
                end_prog = true;
                login_librarian = NULL;
                break;
              }
              }

             }
             

          }while(logged_in);
          break;
        }

    }
    }
  
  }

  // save all the data  
  saveAccounts(account_db.list);
  saveBooks(books_db.list);
  saveFaculties(faculty_db.list);
  saveStudents(students_db.list);
  saveLibrarian(librarian_db.list);
}



