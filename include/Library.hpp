#pragma once

#include "User.hpp"

class Library{
    public:
        Library();
        //~Library();

        template <typename T> void addNewItem(T newItem);
        template <typename T> void deleteItem(T itemToDelete);
        template <typename T> void searchItem(std::string searchTitle);
        template <typename T> void displayAvailableItems();
        void displayAllUsers();
        void readInventory();
        void writeInventory();
        void readUsers();
        void writeUsers();
        std::string readQuotedString(std::istringstream& iss);
        template <typename T, typename ID> std::pair<bool,T> findItemByID(ID id);
        template <typename T> void borrowItem(T newItem);
        void returnBorrowedBook(Book oldBook);
        void returnBorrowedDVD(DVD oldDVD);
        void syncUserChanges();
        template <typename T> size_t findItemIndex(size_t choice);

        std::vector<Book> getBooks();
        std::vector<User> getUsers();
        std::vector<DVD> getDVDs();

        void setBooks(std::vector<Book> newBooks);
        void setUsers(std::vector<User> newUsers);
        void setDVDs(std::vector<DVD> newDVDs);
    private:
        std::vector<Book> books;
        std::vector<User> users;
        std::vector<DVD> dvds;

        template <typename T>
        std::pair<std::vector<T>*, int> getItemContainer();
};

extern User currentUser;