Library Management System
This repository contains the files for a Library Management System. It includes the necessary classes, methods, and system implementation for managing a library's books, users, and accounts.

Project Structure
db/: Contains .txt files for storing all data related to users, accounts, and books.

The .txt files act as the database for the system, holding relevant data in a text format.
src/: Contains the source code files and class implementations.

main.cpp: The main system implementation file. It ties together all the components and contains the entry point for the system.
System.cpp: Implements the methods for managing the system functionality.
System.h: Header file defining the structure and method prototypes of the system.
README.md: This file, providing a brief description and instructions for the Library Management System.

Classes
The system consists of the following main classes:

User: Represents users of the library, including member information and interaction with the system.
Account: Handles user accounts, including logins and authentication.
Books: Manages the book collection, including adding, searching, and removing books.
Database: Responsible for storing and retrieving data from text files in the db/ folder.
Compilation Instructions
To compile the code, navigate to the src/ directory and run the following command:

bash
Copy
g++ -o main main.cpp
This will generate the executable file main.

Execution Instructions
Once compiled, execute the program by running the following command:

bash
Copy
./main
This will start the Library Management System and allow you to interact with the system.

How to Use
When the system starts, follow the on-screen prompts to interact with the system.
The system will allow you to perform tasks like:
Add and remove books
Register and manage user accounts
Borrow and return books
View available books in the library
Database Files
The db/ directory contains .txt files that act as a simple database. These files store:

User information
Book details
Account details
Each file stores relevant data in a simple text format, which the system reads and writes to.
