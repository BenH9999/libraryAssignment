/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

#include "Book.hpp"

Book::Book(){
    ISBN = "";
    author = "";
}

/*
main constructor used
*/
Book::Book(std::string isbn,std::string title, std::string author, bool available) : Item(title,available){   
    this->ISBN = isbn;
    this->author = author;
}

/*
getters
*/
std::string Book::getAuthor(){
    return this->author;
}

std::string Book::getISBN(){
    return this->ISBN;
}

/*
setters
*/
void Book::setAuthor(std::string newAuthor){
    this->author = newAuthor;
}

void Book::setISBN(std::string newISBN){
    this->ISBN = newISBN;
}