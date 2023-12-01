#include "User.hpp"

User::User(){
    userID = 0;
    name = "";
}

void User::returnBook(std::vector<Book>::iterator pos){
    this->borrowedBooks.erase(pos);
}

void User::addNewBorrowedBook(Book newBook){
    this->borrowedBooks.push_back(newBook);
}

bool User::isEmpty(){
    return this->userID==0 && this->name == "" && this->borrowedBooks.empty();
}

int User::getUserID(){
    return this->userID;
}

std::string User::getName(){
    return this->name;
}

std::vector<Book> User::getBorrowedBooks(){
    return this->borrowedBooks;
}

std::vector<DVD> User::getBorrowedDVDs(){
    return this->borrowedDVDs;
}

void User::setUserID(int newUserID){
    this->userID = newUserID;
}

void User::setName(std::string newName){
    this->name = newName;
}

void User::setBorrowedBooks(std::vector<Book> newBorrowedBooks){
    this->borrowedBooks = newBorrowedBooks;
}

void User::setBorrowedDVDs(std::vector<DVD> newBorrowedDVDs){
    this->borrowedDVDs = newBorrowedDVDs;
}