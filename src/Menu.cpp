#include "Menu.hpp"

Library l;
User currentUser;

void displayInitialMenu(){
    std::cout << "Library!" << std::endl;
    std::cout << "1. Add/remove book to/from library" << std::endl;
    std::cout << "2. Select Current User" << std::endl;
    std::cout << "3. Borrow/Return Books" << std::endl;
    std::cout << "4. Display available Books" << std::endl;
    std::cout << "5. Search for Book" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void addRemoveBookMenu(){
    //bool valid = 1;
    int input;
    std::cout << "1. Add Book to library" << std::endl;
    std::cout << "2. Remove Book from library" << std::endl;

    std::cin >> input;

    switch(input){
        case 1:{
            std::string title, author, isbn;

            std::cout << "Enter isbn of book" << std::endl;
            std::cin >> isbn;

            std::cout << "Enter title of book" << std::endl;
            std::cin >> title;

            std::cout << "Enter author of book" << std::endl;
            std::cin >> author;

            Book newBook(isbn,title,author,1);
            l.addNewBook(newBook);

            std::cout << "\e[1;1H\e[2J" << std::endl;
            std::cout << "Added book" << std::endl;

            break;
        }
        case 2:{
            std::string isbn;
            Book bookToRemove;
            
            std::cout << "Enter isbn of book to be removed" << std::endl;
            std::cin >> isbn;

            bookToRemove = l.findBookByISBN(isbn).second;

            l.deleteBook(bookToRemove);

            std::cout << "\e[1;1H\e[2J" << std::endl;
            std::cout << "Removed book" << std::endl;

            break;
        }
    }
}

void setCurrentUser(){
    int userID;
    std::pair<bool,User> result;

    std::cout << "Enter your user ID" << std::endl;
    std::cin >> userID;

    result = l.findUserByUserID(userID);

    if(result.first){
        currentUser = result.second;
    }else{
        std::cout << "User not found" << std::endl;
    }
}

void searchBookByTitle(){
    std::string title;

    std::cout << "Enter title to search for" << std::endl;
    std::cin >> title;

    l.searchBook(title);
}

void processInitialMenu(){
    bool finish = 0;
    int input;

    while(!finish){
        displayInitialMenu();
        std::cin >> input;
        switch(input){
            case 0:{
                finish = 1;
                break;
            }
            case 1:{
                std::cout << "\n";
                addRemoveBookMenu();
                break;
            }
            case 2:{
                std::cout << "\n";
                setCurrentUser();
                break;
            }
            case 3:
            case 4:{
                std::cout << "\n";
                l.displayAvailableBooks();
                break;
            }
            case 5:{
                std::cout << "\n";
                searchBookByTitle();
                break;
            }
        }
    }
}

//printf("\e[1;1H\e[2J");