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

template <typename T> void User::returnItem(int pos){
    std::vector<T>* borrorwedItems = getItemContainer<T>().first;
    remove<T>((*borrorwedItems),pos);
}

template <typename T> void User::addNewBorrowedItem(T newItem){
    std::vector<T>* borrowedItems = getItemContainer<T>().first;
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

template <typename T> std::vector<T> User::getBorrowedItems(){
    std::vector<T>* borrowedItems = getItemContainer<T>().first;

    return (*borrowedItems);
}

void User::setID(int newUserID){
    this->userID = newUserID;
}

void User::setName(std::string newName){
    this->name = newName;
}

template <typename T> void User::setBorrowedItems(std::vector<T> newBorrowedItems){
    std::vector<T>* borrowedItems = getItemContainer<T>().first;
    (*borrowedItems) = newBorrowedItems;
}

template <typename T> std::pair<std::vector<T>*, int> User::getItemContainer(){
    if constexpr(std::is_same_v<T,Book>){
        return std::make_pair(&borrowedBooks, BOOK);
    }else if constexpr(std::is_same_v<T, DVD>){
        return std::make_pair(&borrowedDVDs,DVDs);
    }else{
    }
}

template void User::returnItem<Book>(int pos);
template void User::returnItem<DVD>(int pos);
template std::vector<Book> User::getBorrowedItems<Book>();
template std::vector<DVD> User::getBorrowedItems<DVD>();
template void User::setBorrowedItems<Book>(std::vector<Book> newBorrowedItems);
template void User::setBorrowedItems<DVD>(std::vector<DVD> newBorrowedItems);
template void User::addNewBorrowedItem<Book>(Book newItem);
template void User::addNewBorrowedItem<DVD>(DVD newItem);