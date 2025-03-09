#include <bits/stdc++.h>
using namespace std;



string booksfile = "../db/Books.txt";
string accfile = "../db/accounts.txt";
string stufile = "../db/students.txt";
string facfile = "../db/faculty.txt";
string libfile = "../db/librarians.txt";

// This is the function after each operation into the data base to Books.txt File 
// which is treated as a database

void saveBooks(vector<Books>& list) {
    ofstream outFile(booksfile);
    for(auto it=list.begin(); it!=list.end(); it++) {
        outFile <<  it->ISBN << "\n";
        outFile << it->title << "\n";
        outFile <<  it->author << "\n";
        outFile <<  it->publisher << "\n";
        outFile <<  it->availableStatus << "\n";
        outFile << it->borrowed_on <<"\n";
        if(it==list.end()-1) return;
        outFile << "\n";
    }
}


void saveAccounts(vector<Account>& list) {
    ofstream outFile(accfile);
    for(auto it=list.begin(); it!=list.end(); it++) {
        
        outFile <<  it->userid << "\n";
        outFile <<  it->fine << "\n";

    
        for(auto borrbooks: it->BorrowedBooks) {
            outFile  << borrbooks << " ";
        }
        outFile << "\n";
        
        for(auto duebooks: it->overDueBooks) {
            outFile  << duebooks << "     ";
        }
        outFile << "\n";
        for(auto books: it->BorrowedHistory) {
            outFile  << books << "     ";
        }
        outFile << "\n";
        if(it==list.end()-1) return;
        outFile << "\n";
    }
}

void saveStudents(vector<Student>& list) {
    ofstream outFile(stufile);
    
    for(auto it=list.begin(); it!=list.end(); it++) {
          outFile << it->userid << "\n" << it->username << "\n" << it->get_password() << "\n"<< it->finePerOverdue << "\n" << it->manageAccess << "\n" << it->maxBooksBorrow << "\n" << it->maxTimeperiod << "\n";
          if(it == (list.end()-1)) return;
          outFile << "\n";
    }
    
}


void saveFaculties(vector<Faculty>& list) {
    ofstream outFile(facfile);
    for(auto it=list.begin(); it!=list.end(); it++) {
        outFile << it->userid << "\n" << it->username << "\n" << it->get_password() << "\n"<< it->finePerOverdue << "\n" << it->manageAccess << "\n" << it->maxBooksBorrow << "\n" << it->maxTimeperiod << "\n";
        if(it==list.end()-1) return;
        outFile << "\n";
  }
   
}

void saveLibrarian(vector<Librarian>& list) {    
    ofstream outFile(libfile);
    for(auto it=list.begin(); it!=list.end(); it++) { 
        outFile << it->userid << "\n" << it->username << "\n" << it->get_password() << "\n"<< it->finePerOverdue << "\n" << it->manageAccess << "\n" << it->maxBooksBorrow << "\n" << it->maxTimeperiod << "\n";
        if(it==list.end()-1) return;
        outFile << "\n";  
    }
}
