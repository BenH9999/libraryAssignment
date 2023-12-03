/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

#include "User.hpp"

User::User(){
    userID = 0;
    name = "";
}

/*
this is a template function to remove from a vector,
i found it on stack overflow while stuck with an issue
with the program crashing when i tried using
'this->books,erease(it)' so i used this instead

it is one of the answers from here:
https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
*/
template <typename T>
void remove(std::vector<T>& vec, size_t pos){
    typename std::vector<T>::iterator it = vec.begin();
    std::advance(it, pos);
    vec.erase(it);
}

/*
template function to return items to user and remove from user item vector
*/
template <typename T> void User::returnItem(int pos){
    std::vector<T>* borrorwedItems = getItemContainer<T>();
    remove<T>((*borrorwedItems),pos);
}

/*
template function to add borrowed item to user borrowed item vector
*/
template <typename T> void User::addNewBorrowedItem(T newItem){
    std::vector<T>* borrowedItems = getItemContainer<T>();
    (*borrowedItems).push_back(newItem);
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

/*
template function to get borrowed items
*/
template <typename T> std::vector<T> User::getBorrowedItems(){
    std::vector<T>* borrowedItems = getItemContainer<T>();

    return (*borrowedItems);
}

void User::setID(int newUserID){
    this->userID = newUserID;
}

void User::setName(std::string newName){
    this->name = newName;
}

/*
template function to set borrowed items
*/
template <typename T> void User::setBorrowedItems(std::vector<T> newBorrowedItems){
    std::vector<T>* borrowedItems = getItemContainer<T>();
    (*borrowedItems) = newBorrowedItems;
}

/*
template helper function to get the container required
*/
template <typename T> std::vector<T>* User::getItemContainer(){
    if constexpr(std::is_same_v<T,Book>){
        return &borrowedBooks;
    }else if constexpr(std::is_same_v<T, DVD>){
        return &borrowedDVDs;
    }else{
    }
}

//explicit instantiation of template functions
template void User::returnItem<Book>(int pos);
template void User::returnItem<DVD>(int pos);
template std::vector<Book> User::getBorrowedItems<Book>();
template std::vector<DVD> User::getBorrowedItems<DVD>();
template void User::setBorrowedItems<Book>(std::vector<Book> newBorrowedItems);
template void User::setBorrowedItems<DVD>(std::vector<DVD> newBorrowedItems);
template void User::addNewBorrowedItem<Book>(Book newItem);
template void User::addNewBorrowedItem<DVD>(DVD newItem);