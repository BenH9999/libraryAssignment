#include "Book.hpp"

Book::Book(){
    ISBN = "";
    title = "";
    author = "";
    available = 1;
}

Book::Book(std::string isbn,std::string title, std::string author, bool available){
    this->ISBN = isbn;
    this->title = title;
    this->author = author;
    this->available = available;
}

std::string Book::getTitle(){
    return this->title;
}

std::string Book::getAuthor(){
    return this->author;
}

std::string Book::getISBN(){
    return this->ISBN;
}

bool Book::getAvailable(){
    return this->available;
}

void Book::setTitle(std::string newTitle){
    this->title = newTitle;
}

void Book::setAuthor(std::string newAuthor){
    this->author = newAuthor;
}

void Book::setISBN(std::string newISBN){
    this->ISBN = newISBN;
}

void Book::setAvailable(bool newAvailable){
    this->available = newAvailable;
}