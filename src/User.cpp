#include "User.hpp"

User::User(){
    userID = 0;
    name = "";
}

template <typename T>
void remove(std::vector<T>& vec, size_t pos){
    typename std::vector<T>::iterator it = vec.begin();
    std::advance(it, pos);
    vec.erase(it);
}

void User::returnBook(int pos){
    remove<Book>(borrowedBooks, pos);
}

void User::returnDVD(int pos){
    remove<DVD>(borrowedDVDs, pos);
}

void User::addNewBorrowedBook(Book newBook){
    this->borrowedBooks.push_back(newBook);
}

void User::addNewBorrowedDVD(DVD newDVD){
    this->borrowedDVDs.push_back(newDVD);
}

bool User::isEmpty(){
    return this->userID==0 && this->name == "" && this->borrowedBooks.empty();
}

int User::getID(){
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

void User::setID(int newUserID){
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