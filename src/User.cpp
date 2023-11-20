#include "User.hpp"

User::User(){
    userID = 0;
    name = "";
}

void User::addNewBorrowedBook(Book newBook){
    this->borrowedBooks.push_back(newBook);
}

/*void User::returnBorrowedBook(Book oldBook){
    std::vector<Book>::iterator it = std::find(borrowedBooks.begin(),borrowedBooks.end(),oldBook);
    size_t i;
    for(i = 0; i < borrowedBooks.size();i++){
        if(oldBook == borrowedBooks[i])i++;
    }

    this->borrowedBooks[i].setAvailable(1);
}*/


int User::getUserID(){
    return this->userID;
}

std::string User::getName(){
    return this->name;
}

std::vector<Book> User::getBorrowedBooks(){
    return this->borrowedBooks;
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