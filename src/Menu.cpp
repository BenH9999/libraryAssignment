#include "Menu.hpp"

Library l;
User currentUser;

void displayInitialMenu(){
    std::cout << "Library!" << std::endl;
    std::cout << "1. Add/remove Item to/from library" << std::endl;
    std::cout << "2. Select Current User" << std::endl;
    std::cout << "3. Borrow/Return Items" << std::endl;
    std::cout << "4. Display Library" << std::endl;
    std::cout << "5. Search Through Library" << std::endl;
    //std::cout << "6. Save current Library Books and Users to file" << std::endl;
    std::cout << "0. Save and Exit" << std::endl;
}

void addRemoveItemMenu(){
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

            for(size_t i = 0; i < l.getBooks().size(); i++){
                if(l.getBooks()[i].getISBN() == isbn){
                    std::cout << "Book already exists" << std::endl;
                    return;
                }
            }

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

void searchItemByTitle(){
    std::string title;

    std::cout << "Enter title to search for" << std::endl;
    std::cin >> title;

    l.searchBook(title);
}

void borrowReturnItem(){
    int input;
    std::cout << "1. Borrow Item" << std::endl;
    std::cout << "2. Return Item" << std::endl;

    std::cin >> input;

    switch(input){
        case 1:{
            borrowItem();
            break;
        }
        case 2:{
            returnItem();
            break;
        }
    }
    l.syncUserChanges();
}

void borrowItem(){
    int itemChoice;
    std::cout << "Item to Borrow: " << std::endl;
    std::cout << "1. Book" << std::endl;
    std::cout << "2. DVD" << std::endl;

    std::cin >> itemChoice;

    switch(itemChoice){
        case 1:{
            int choice;
            std::cout << "\nAvailable Books" << std::endl;
            l.displayAvailableBooks();
            std::cout << "0. Return to menu" << std::endl;
            std::cin >> choice;

            if(choice == 0){
                std::cout << "\e[1;1H\e[2J" << std::endl;
                processInitialMenu();
            }
            else{
                Book bookToBorrow = l.findBookByISBN(l.getBooks()[choice-1].getISBN()).second;
                l.borrowBook(bookToBorrow);
            }

            std::cout << "\e[1;1H\e[2J" << std::endl;
            std::cout << "Book Borrowed!\n" << std::endl;
        }
        case 2:{
            int choice;
            std::cout << "\nAvailable DVDs" << std::endl;
            l.displayAvailableDVDs();
            std::cout << "0. Return to menu" << std::endl;
            std::cin >> choice;

            if(choice == 0){
                std::cout << "\e[1;1H\e[2J" << std::endl;
                processInitialMenu();
            }
            else{
                DVD dvdToBorrow = l.findDVDByID(l.getDVDs()[choice-1].getID()).second;
                l.borrowDVD(dvdToBorrow);
            }
            std::cout << "\e[1;1H\e[2J" << std::endl;
            std::cout << "DVD Borrowed!\n" << std::endl;
        }
    }
    
}

void returnItem(){
    int itemChoice;
    std::cout << "Item to Return: " << std::endl;
    std::cout << "1. Book" << std::endl;
    std::cout << "2. DVD" << std::endl;

    std::cin >> itemChoice;
    switch(itemChoice){
        case 1:{
            int choice;
            std::string isbnToReturn;
            std::cout << "Currently borrowed books: " << std::endl;
            displayBorrowedBooks();
            std::cout << "0. Return to menu" << std::endl;
            std::cin >> choice;

            if(choice == 0){
                std::cout << "\e[1;1H\e[2J" << std::endl;
                processInitialMenu();
            }else{
                Book bookToReturn = l.findBookByISBN(currentUser.getBorrowedBooks()[choice-1].getISBN()).second;
                std::cout << "Book to return: " << bookToReturn.getTitle() << std::endl;
                l.returnBorrowedBook(bookToReturn);
            }

            //std::cout << "\e[1;1H\e[2J" << std::endl;
            std::cout << "Book Returned!\n" << std::endl;
        }
        case 2:{
            int choice;
            int dvdIDToReturn;
            std::cout << "Currently borrowed DVDs: " << std::endl;
            displayBorrowedDVDs();
            std::cout << "0. Return to menu" << std::endl;
            std::cin >> choice;

            if(choice == 0){
                std::cout << "\e[1;1H\e[2J" << std::endl;
                processInitialMenu();
            }else{
                DVD dvdToReturn = l.findDVDByID(currentUser.getBorrowedDVDs()[choice-1].getID()).second;
                std::cout << "DVD to return: " << dvdToReturn.getTitle() << std::endl;
                l.returnBorrowedDVD(dvdToReturn);
            }

            //std::cout << "\e[1;1H\e[2J" << std::endl;
            std::cout << "DVD Returned!\n" << std::endl;
        }
    }
}

void displayBorrowedBooks(){
    if(currentUser.getBorrowedBooks().size() == 0){
        std::cout << "You have no borrowed books" << std::endl;
    }else{
        for(size_t i = 0; i < currentUser.getBorrowedBooks().size(); i++){
            std::cout << i+1 << ". " << currentUser.getBorrowedBooks()[i].getTitle() << std::endl;
        }
    }
}

void displayBorrowedDVDs(){
    if(currentUser.getBorrowedDVDs().size() == 0){
        std::cout << "You have no borrowed DVDs" << std::endl;
    }else{
        for(size_t i = 0; i < currentUser.getBorrowedDVDs().size(); i++){
            std::cout << i+1 << ". " << currentUser.getBorrowedDVDs()[i].getTitle() << std::endl;
        }
    }
}

void processInitialMenu(){
    bool finish = 0;
    int input;

    while(!finish){
        displayInitialMenu();
        std::cin >> input;
        switch(input){
            case 0:{
                l.writeInventory();
                l.writeUsers();
                finish = 1;
                break;
            }
            case 1:{
                std::cout << "\n";
                addRemoveItemMenu();
                break;
            }
            case 2:{
                std::cout << "\n";
                setCurrentUser();
                break;
            }
            case 3:{
                if(currentUser.isEmpty()){
                    std::cout << "No user selected, please select one first" << std::endl;
                    break;
                }
                borrowReturnItem();
                break;
            }
            case 4:{
                std::cout << "\n";
                l.displayAvailableBooks();
                break;
            }
            case 5:{
                std::cout << "\n";
                searchItemByTitle();
                break;
            }
        }
    }
}

//printf("\e[1;1H\e[2J");