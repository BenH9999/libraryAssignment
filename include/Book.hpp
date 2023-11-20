#pragma once

#include <iostream>

class Book{
    public:
        Book();
        Book(std::string isbn, std::string title,std::string author,bool available);
        //~Book();

        std::string getTitle();
        std::string getAuthor();
        std::string getISBN();
        bool getAvailable();

        void setTitle(std::string newTitle);
        void setAuthor(std::string newAuthor);
        void setISBN(std::string newISBN);
        void setAvailable(bool newAvailable);

        //overloading operator to be able to compare books for vector
        bool operator==(const Book& other) const {
            return ISBN == other.ISBN && title == other.title && author == other.author && available == other.available;
        }
    private:
        std::string ISBN;
        std::string title;
        std::string author;
        bool available;
};