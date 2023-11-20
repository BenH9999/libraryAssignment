#pragma once

#include "User.hpp"

class Library{
    public:
        Library();
        //~Library();

        void addNewBook(Book newBook);
        void addNewUser(User newUser);
        void deleteBook(Book bookToDelete);
        void deleteUser(User userToDelete);
        void searchBook(std::string searchTitle);
        void displayAvailableBooks();
        void displayAllUsers();
        void readInventory();
        void readUsers();
        std::string readQuotedString(std::istringstream& iss);
        std::pair<bool,Book> findBookByISBN(std::string isbn);
        std::pair<bool,User> findUserByUserID(int userID);
        void borrowBook(Book newBook);
        void returnBorrowedBook(Book oldBook);

        std::vector<Book> getBooks();
        std::vector<User> getUsers();

        void setBooks(std::vector<Book> newBooks);
        void setUsers(std::vector<User> newUsers);
    private:
        std::vector<Book> books;
        std::vector<User> users;
};

extern User currentUser;