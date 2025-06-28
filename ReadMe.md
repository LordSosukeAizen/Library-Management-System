# 📚 Library Management System

A lightweight C++ project that simulates a functional Library Management System. This system allows library administrators and users to manage books, user accounts, and lending operations. It uses plain-text files as a simple database solution for persistent storage.

---

## 🧩 Features

- 📖 Add, view, search, and remove books
- 👤 Register, authenticate, and manage user accounts
- 📕 Borrow and return books
- 💾 Persist all data using `.txt` files (no external DB required)
- 🧹 Clean modular design with separate classes for system components

---

## 🗂️ Project Structure

Library-Management-System/
│
├── db/ # Flat-file storage for all data (acts as database)
│ ├── users.txt # Stores user details
│ ├── books.txt # Stores book records
│ └── accounts.txt # Stores login/account credentials
│
├── src/ # Source code
│ ├── main.cpp # Entry point for the system
│ ├── System.cpp # Method implementations for core system logic
│ └── System.h # Class declarations and function prototypes
│
└── README.md # Project documentation


---

## 🏗️ Classes Overview

| Class     | Description |
|-----------|-------------|
| `User`    | Represents library members and their profiles |
| `Account` | Manages account creation, login, and authentication |
| `Books`   | Maintains the library’s book collection |
| `Database`| Handles reading and writing data from/to text files |
| `System`  | Coordinates high-level functionality and user flow |

---

## 🧪 How to Compile

Navigate to the `src/` directory and compile using:

```bash
g++ -o main main.cpp
This command will generate an executable named main.
```
## 🚀 How to Run

After compilation, run the system using:

```bash
./main
You will be presented with a simple CLI interface to interact with the system.
```
## 🧭 Usage Guide

You can perform various tasks such as:

Add new books to the catalog
Search for books by title
Register and manage library members
Borrow and return books
View current inventory of available books
All changes are saved automatically in the db/ folder.

## 💾 Data Management

Data is persistently stored in the following text files:

users.txt: Contains registered user info
books.txt: Tracks all available/borrowed books
accounts.txt: Stores login credentials securely (in plain text for simplicity)
These files act as a minimalistic database and can be edited manually if needed.


## 📬 Contact
For queries, suggestions, or collaborations, reach out via GitHub.
