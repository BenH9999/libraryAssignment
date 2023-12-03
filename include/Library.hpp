/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

#pragma once

#include "User.hpp"

class Library{
    public:
        Library();

        template <typename T> void addNewItem(T newItem);
        template <typename T> void deleteItem(T itemToDelete);
        template <typename T> void searchItem(std::string searchTitle);
        template <typename T> void displayAvailableItems();
        template <typename T, typename ID> std::pair<bool,T> findItemByID(ID id);
        template <typename T> void borrowItem(T newItem);
        template <typename T> void returnBorrowedItem(T oldItem);
        template <typename T> size_t findItemIndex(size_t choice);
        template <typename T> std::vector<T> getItems();
        template <typename T> void setItems(std::vector<T> newItems);
        void displayAllUsers();
        void readInventory();
        void writeInventory();
        void readUsers();
        void writeUsers();
        void createNewUser();
        std::string readQuotedString(std::istringstream& iss);
        void syncUserChanges();
    private:
        std::vector<Book> books;
        std::vector<User> users;
        std::vector<DVD> dvds;

        template <typename T> std::vector<T>* getItemContainer();
};

extern User currentUser;