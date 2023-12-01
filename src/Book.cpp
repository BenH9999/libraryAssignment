#include "Book.hpp"

Book::Book(){
    ISBN = "";
    author = "";
}

Book::Book(std::string isbn,std::string title, std::string author, bool available) : Item(title,available){   
    this->ISBN = isbn;
    this->author = author;
}

//std::string Book::getTitle(){
    //return this->title;
//}

std::string Book::getAuthor(){
    return this->author;
}

std::string Book::getISBN(){
    return this->ISBN;
}

void Book::setAuthor(std::string newAuthor){
    this->author = newAuthor;
}

void Book::setISBN(std::string newISBN){
    this->ISBN = newISBN;
}