/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

#include "Menu.hpp"

Library l;
User currentUser;

/* 
    Function to just print all menu options, in function for
    the sake of being clean(lots of functions in this file are
    split apart for the sake of being more organised)
 */
void displayInitialMenu(){
    std::cout << "Library!" << std::endl;
    std::cout << "1. Add/remove Item to/from library" << std::endl;
    std::cout << "2. Select Current User" << std::endl;
    std::cout << "3. Borrow/Return Items" << std::endl;
    std::cout << "4. Display Library" << std::endl;
    std::cout << "5. Search Through Library" << std::endl;
    std::cout << "6. Save current Library Books and Users to file" << std::endl;
    std::cout << "0. Save and Exit" << std::endl;
}

/* 
function to process whether to add or remove an item
 */
void addRemoveItemMenu(){
    int input;
    std::cout << "1. Add Item to library" << std::endl;
    std::cout << "2. Remove Item from library" << std::endl;

    std::cin >> input;

    std::cout << "\e[1;1H\e[2J";
    /* 
    the nested switch statements are to decide what
    item to add/remove
     */
    switch(input){
        default:{
            std::cout << "Invalid input" << std::endl;
            break;
        }
        //Adding an item
        case 1:{
            int itemChoice;
            std::cout << "Item to add" << std::endl;
            std::cout << "1. Book" << std::endl;
            std::cout << "2. DVD" << std::endl;
            std::cin >> itemChoice;

            std::cout << "\e[1;1H\e[2J";

            switch(itemChoice){
                default:{
                std::cout << "Invalid input" << std::endl;
                break;
            }
                //book
                case 1:{
                    std::string title, author, isbn;

                    std::cout << "Enter isbn of book" << std::endl;
                    std::cin >> isbn;

                    //check if it already exists
                    for(size_t i = 0; i < l.getItems<Book>().size(); i++){
                        if(l.getItems<Book>()[i].getISBN() == isbn){
                            std::cout << "Book already exists" << std::endl;
                            return;
                        }
                    }

                    std::cout << "Enter title of book" << std::endl;
                    std::cin >> title;

                    std::cout << "Enter author of book" << std::endl;
                    std::cin >> author;

                    Book newBook(isbn,title,author,1);
                    l.addNewItem<Book>(newBook);

                    std::cout << "\e[1;1H\e[2J";
                    std::cout << "Added book" << std::endl;

                    break;
                }
                case 2:{
                    //dvd
                    std::string title,genre;
                    int id;
                    double rating;

                    std::cout << "Enter id of DVD" << std::endl;

                    std::cin >> id;

                    //check if it already exists
                    if(l.findItemByID<DVD>(id).first){
                        std::cout << "DVD already exists" << std::endl;
                        return;
                    }

                    std::cout << "Enter title of DVD" << std::endl;
                    std::cin >> title;

                    std::cout << "Enter genre of DVD" << std::endl;
                    std::cin >> genre;

                    std::cout << "Enter rating of DVD" << std::endl;
                    std::cin >> rating;

                    DVD newDVD(title,id,genre,rating,1);
                    l.addNewItem<DVD>(newDVD);

                    std::cout << "\e[1;1H\e[2J" << std::endl;
                    std::cout << "Added DVD" << std::endl;

                    break;
                }
            }
            break;
        }
        case 2:{
            //removing an item
            int itemChoice;
            std::cout << "Item to remove" << std::endl;
            std::cout << "1. Book" << std::endl;
            std::cout << "2. DVD" << std::endl;
            std::cin >> itemChoice;

            std::cout << "\e[1;1H\e[2J";

            switch(itemChoice){
                default:{
                    std::cout << "Invalid input" << std::endl;
                    break;
                }
                //book
                case 1:{
                    std::string isbn;
                    Book bookToRemove;
            
                    std::cout << "Enter isbn of book to be removed" << std::endl;
                    std::cin >> isbn;

                    //check if it exists
                    if(!l.findItemByID<Book>(isbn).first){
                        std::cout << "Book not found" << std::endl;
                        return;
                    }

                    bookToRemove = l.findItemByID<Book>(isbn).second;

                    l.deleteItem<Book>(bookToRemove);

                    std::cout << "\e[1;1H\e[2J";
                    std::cout << "Removed book" << std::endl;

                    break;
                }
                case 2:{
                    //dvd
                    int dvdID;
                    DVD dvdToRemove;

                    std::cout << "Enter id of DVD to be removed" << std::endl;
                    std::cin >> dvdID;

                    //check if it exists
                    if(!l.findItemByID<DVD>(dvdID).first){
                        std::cout << "DVD not found" << std::endl;
                        return;
                    }

                    dvdToRemove = l.findItemByID<DVD>(dvdID).second;
                    l.deleteItem<DVD>(dvdToRemove);

                    std::cout << "\e[1;1H\e[2J";
                    std::cout << "Removed DVD" << std::endl;

                    break;
                }
            }
            break;
        }
    }
}

/* 
set current user so that i dont need
to remember the position of the current
user in the users vector
 */
void setCurrentUser(){
    int userID;
    std::pair<bool,User> result;

    std::cout << "Enter your user ID" << std::endl;
    std::cin >> userID;

    result = l.findItemByID<User>(userID);

    //checks if user exists
    if(result.first){
        currentUser = result.second;
        std::cout << "\e[1;1H\e[2J";
        std::cout << "Hello, " << currentUser.getName() << std::endl;
    }else{
        std::cout << "\e[1;1H\e[2J";
        std::cout << "User not found" << std::endl;
    }

    //these for loops below were used for testing when i was having issues reading the user file

    /* std::cout << "Borrowed Books: " << std::endl;
    for(size_t i = 0; i < currentUser.getBorrowedItems<Book>().size();i++){
        std::cout << i+1 << ". " << currentUser.getBorrowedItems<Book>()[i].getTitle() << std::endl;
    }
    std::cout << "\n";
    std::cout << "Borrowed DVDs: " << std::endl;
    for(size_t i = 0; i < currentUser.getBorrowedItems<DVD>().size();i++){
        std::cout << i+1 << ". " << currentUser.getBorrowedItems<DVD>()[i].getTitle() << std::endl;
    } */
}

/*
this function is to search for a user.
i wanted to make it more in depth but i
didnt have time, it takes the input string
and searches for it in the books vector.getTitle()
string and if it finds the set of characters
in that order it adds it to a vector of search results
 */
void searchItemByTitle(){
    int itemChoice;
    std::cout << "Items to search" << std::endl;
    std::cout << "1. Books" << std::endl;
    std::cout<< "2. DVDs" << std::endl;

    std::cin >> itemChoice;

    std::cout << "\e[1;1H\e[2J";

    std::string title;

    std::cout << "Enter title to search for" << std::endl;
    std::cin >> title;

    std::cout << "\e[1;1H\e[2J";

    switch(itemChoice){
        default:{
            std::cout << "Invalid input" << std::endl;
            break;
        }
        case 1:{
            l.searchItem<Book>(title);
            break;
        }
        case 2:{
            l.searchItem<DVD>(title);
            break;
        }
    }
}

/*
borrow item menu to decide if borrow or return
*/
void borrowReturnItem(){
    int input;
    std::cout << "1. Borrow Item" << std::endl;
    std::cout << "2. Return Item" << std::endl;

    std::cin >> input;

    std::cout << "\e[1;1H\e[2J";
    switch(input){
        default:{
            std::cout << "Invalid input" << std::endl;
            break;
        }
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

/*
borrow item menu, asks if the user wants to borrow a book or a dvd
then prints the available items with index+1 next to them and takes the users integer
and finds the items real index in the vector, then gets the item by id and borrows it
*/
void borrowItem(){
    int itemChoice;
    std::cout << "Item to Borrow: " << std::endl;
    std::cout << "1. Book" << std::endl;
    std::cout << "2. DVD" << std::endl;

    std::cin >> itemChoice;

    std::cout << "\e[1;1H\e[2J";
    switch(itemChoice){
        default:{
            std::cout << "Invalid input" << std::endl;
            break;
        }
        case 1:{
            //book
            size_t choice;
            std::cout << "\nAvailable Books" << std::endl;
            l.displayAvailableItems<Book>();
            std::cout << "0. Return to menu" << std::endl;
            std::cin >> choice;

            if(choice == 0){
                std::cout << "\e[1;1H\e[2J";
                processInitialMenu();
            }
            else{
                size_t index = l.findItemIndex<Book>(choice);
                Book bookToBorrow = l.findItemByID<Book>(l.getItems<Book>()[index].getISBN()).second;
                std::cout << "Book to borrow: " << bookToBorrow.getTitle() << std::endl;
                l.borrowItem<Book>(bookToBorrow);
            }

            std::cout << "\e[1;1H\e[2J";
            std::cout << "Book Borrowed!\n" << std::endl;
            break;
        }
        case 2:{
            //dvd
            size_t choice;
            std::cout << "\nAvailable DVDs" << std::endl;
            l.displayAvailableItems<DVD>();
            std::cout << "0. Return to menu" << std::endl;
            std::cin >> choice;

            if(choice == 0){
                std::cout << "\e[1;1H\e[2J";
                processInitialMenu();
            }
            else{
                size_t index = l.findItemIndex<DVD>(choice);
                DVD dvdToBorrow = l.findItemByID<DVD>(l.getItems<DVD>()[index].getID()).second;
                l.borrowItem<DVD>(dvdToBorrow);
            }
            std::cout << "\e[1;1H\e[2J";
            std::cout << "DVD Borrowed!\n" << std::endl;
            break;
        }
    }
    
}

/*
function to return item, like borrowing it asks the user if they want to return a book or a dvd
however it is simpler as it doesnt need to find the 'real' index. It prints all the borrowed items
with index+1 next to it and takes the users choice and finds the item based off of the id
*/
void returnItem(){
    int itemChoice;
    std::cout << "Item to Return: " << std::endl;
    std::cout << "1. Book" << std::endl;
    std::cout << "2. DVD" << std::endl;

    std::cin >> itemChoice;

    std::cout << "\e[1;1H\e[2J";
    switch(itemChoice){
        default:{
            std::cout << "Invalid input" << std::endl;
            break;
        }
        case 1:{
            //book
            int choice;
            std::cout << "Currently borrowed books: " << std::endl;
            displayBorrowedItems<Book>();
            std::cout << "0. Return to menu" << std::endl;
            std::cin >> choice;

            if(choice == 0){
                std::cout << "\e[1;1H\e[2J" << std::endl;
                processInitialMenu();
            }else{
                Book bookToReturn = l.findItemByID<Book>(currentUser.getBorrowedItems<Book>()[choice-1].getISBN()).second;
                /*
                    this below and the matching line of code for dvd were used for debugging
                    a major issue with returning items that i was having
                */
                //std::cout << "Book to return: " << bookToReturn.getTitle() << std::endl;
                l.returnBorrowedItem<Book>(bookToReturn);
            }

            std::cout << "\e[1;1H\e[2J";

            break;
        }
        case 2:{
            //dvd
            int choice;
            std::cout << "Currently borrowed DVDs: " << std::endl;
            displayBorrowedItems<DVD>();
            std::cout << "0. Return to menu" << std::endl;
            std::cin >> choice;

            std::cout << "\e[1;1H\e[2J";

            if(choice == 0){
                processInitialMenu();
            }else{
                DVD dvdToReturn = l.findItemByID<DVD>(currentUser.getBorrowedItems<DVD>()[choice-1].getID()).second;
                //std::cout << "DVD to return: " << dvdToReturn.getTitle() << std::endl;
                l.returnBorrowedItem<DVD>(dvdToReturn);
            }

            std::cout << "\e[1;1H\e[2J";

            break;
        }
    }
}

/*
template function where T is either class book or dvd,
to display the current users borrowed items
*/
template <typename T> void displayBorrowedItems(){
    std::vector<T> currentBorrowedItems = getItemContainer<T>();

    if(currentBorrowedItems.size() == 0){
        std::cout << "You have no borrowed Items" << std::endl;
    }else{
        for(size_t i = 0; i < currentBorrowedItems.size(); i++){
            std::cout << i+1 << ". " << currentBorrowedItems[i].getTitle() << std::endl;
        }
    }
}

/*
function to process the initial menu with all options on
what the user can do*/
void processInitialMenu(){
    bool finish = 0;
    int input;

    while(!finish){
        displayInitialMenu();
        std::cin >> input;
        std::cout << "\e[1;1H\e[2J";
        switch(input){
            default:{
                std::cout << "Invalid input" << std::endl;
                break;
            }
            case 0:{
                //save and exit
                l.writeInventory();
                l.writeUsers();
                finish = 1;
                break;
            }
            case 1:{
                //add/remove item from library
                std::cout << "\n";
                addRemoveItemMenu();
                break;
            }
            case 2:{
                //set the current user
                std::cout << "\n";
                setCurrentUser();
                break;
            }
            case 3:{
                //borrow/return item, if it is empty gives an error and returns to menu
                if(currentUser.isEmpty()){
                    std::cout << "No user selected, please select one first\n" << std::endl;
                    break;
                }
                borrowReturnItem();
                break;
            }
            case 4:{
                //display all available items of a specific type
                std::cout << "\n";
                int itemChoice;
                std::cout << "Items to display" << std::endl;
                std::cout << "1. Books" << std::endl;
                std::cout << "2. DVDs" << std::endl;
                
                std::cin >> itemChoice;

                std::cout << "\e[1;1H\e[2J";

                switch(itemChoice){
                    default:{
                        std::cout << "Invalid input" << std::endl;
                        break;
                    }
                    case 1:{
                        l.displayAvailableItems<Book>();
                        break;
                    }
                    case 2:{
                        l.displayAvailableItems<DVD>();
                        break;
                    }
                }
                break;
            }
            case 5:{
                //search through items
                std::cout << "\n";
                searchItemByTitle();
                break;
            }
            case 6:{
                l.writeInventory();
                l.writeUsers();
                break;
            }
        }
    }
}

/*
template helper function to get borrowed items
from user depending on what is needed
*/
template <typename T> std::vector<T> getItemContainer(){
    if constexpr(std::is_same_v<T,Book>){
        return currentUser.getBorrowedItems<Book>();
    }else if constexpr(std::is_same_v<T, DVD>){
        return currentUser.getBorrowedItems<DVD>();
    }else{
    }
}

//explicit instantiation of template functions
template void displayBorrowedItems<Book>();
template void displayBorrowedItems<DVD>();