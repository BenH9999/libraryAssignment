/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

#include "Library.hpp"

/*
constructor
*/
Library::Library(){
    readInventory();
    readUsers();
}

/*
template function to borrow item, it gets the items as a vector pointer
then adds it to the current users borrowed items and sets the item in the library
to unavailable
*/
template <typename T> void Library::borrowItem(T newItem){
    std::vector<T>* items = getItemContainer<T>();

    currentUser.addNewBorrowedItem<T>(newItem);

    for(size_t i = 0; i < items->size();i++){
        if(newItem == items->at(i)){
            items->at(i).setAvailable(0);
        }
    }
}

/*
template function to return a borrowed item, it gets the items as a vector pointer
then removes the item from the users borrowed items then it sets it to available
again in the library items vector
*/
template <typename T> void Library::returnBorrowedItem(T oldItem){
    std::vector<T>* items = getItemContainer<T>();

    for(size_t i = 0; i < currentUser.getBorrowedItems<T>().size(); i++){
        if(currentUser.getBorrowedItems<T>()[i] == oldItem){
            currentUser.returnItem<T>(i);
        }
    }

    typename std::vector<T>::iterator libraryIT = std::find(items->begin(),items->end(),oldItem);
    if(libraryIT != items->end()){
        libraryIT->setAvailable(1);
        std::cout << "Item returned\n" << std::endl;
    }else{
        std::cerr << "Error: Item not found in library" << std::endl;
    }
}

/*
template function to search for item, it takes the search title from the menu
and makes a vector of all the items where item.getTitle() contains
the search title in any way
*/
template <typename T> void Library::searchItem(std::string searchTitle) {
    bool resultFound = false;
    std::vector<T>* itemsForSearch = getItemContainer<T>();
    std::vector<T> searchResults;

    for (size_t i = 0; i < itemsForSearch->size(); i++) {
        resultFound = itemsForSearch->at(i).getTitle().find(searchTitle) != std::string::npos;
        if (resultFound) {
            searchResults.push_back(itemsForSearch->at(i));
        }
        resultFound = false;
    }

    for (size_t i = 0; i < searchResults.size(); i++) {
        std::cout << searchResults[i].getTitle() << std::endl;
    }
}

/*
writes inventory to file, when writing the lines it prints a 1 or a 0
at the start based off of what it is, then all of the data sequentially
after separated by spaces
*/
void Library::writeInventory(){
    std::ofstream file("Sample Data Files/inventory.txt");

    char quote = '"';

    for(size_t i = 0; i < books.size(); i++){
        file << "0" << " ";
        file << books[i].getISBN() << " ";
        file << quote << books[i].getTitle() << quote << " ";
        file << quote << books[i].getAuthor() << quote << " ";
        file << books[i].getAvailable();
        if(!dvds.empty() || i != dvds.size()-1) file << "\n";
    }

    for(size_t i = 0; i < dvds.size(); i++){
        file << "1" << " ";
        file << quote << dvds[i].getTitle() << quote << " ";
        file << dvds[i].getID() << " ";
        file << quote << dvds[i].getGenre() << quote << " ";
        file << dvds[i].getRating() << " ";
        file << dvds[i].getAvailable() << " ";
        if(i != dvds.size()-1) file << "\n";
    }
    file.close();
}

/*
syncs user changes, runs after borrowing or returning
a book
*/
void Library::syncUserChanges(){
    for(size_t i = 0; i < users.size(); i++){
        if(users[i].getID() == currentUser.getID()){
            users[i].setBorrowedItems<Book>(currentUser.getBorrowedItems<Book>());
            users[i].setBorrowedItems<DVD>(currentUser.getBorrowedItems<DVD>());
            break;
        }
    }
}

/*
function to read the inventory, it decides whether or not it is a book
or a dvd based on the first character in the line then reads all data
sequentially accordingly
*/
void Library::readInventory(){
    std::string fileNameBooks = "Sample Data Files/inventory.txt";
    std::ifstream fileBooks(fileNameBooks);

    if(!fileBooks.is_open()){
        std::cerr << "Error opening file " << fileNameBooks << std::endl;
    }

    std::string buff;
    while(std::getline(fileBooks,buff)){
        int type;
        std::istringstream iss(buff);
        std::string title;
        bool available;

        iss >> type;

        switch(type){
            case BOOK:{
                std::string isbn, author;

                iss >> isbn;
                title = readQuotedString(iss);
                author = readQuotedString(iss);
                iss >> available;

                this->books.emplace_back(Book(isbn,title,author,available));
                break;
            }
            case DVDs:{
                int id;
                std::string genre;
                double rating;

                title = readQuotedString(iss);
                iss >> id;
                genre = readQuotedString(iss);
                iss >> rating;
                iss >> available;

                this->dvds.emplace_back(DVD(title,id,genre,rating,available));
                break;
            }
        }
    }
    fileBooks.close();
}

/*
writing the users to file, literally just writes
sequentially, nothing important to note
*/
void Library::writeUsers(){
    std::ofstream file("Sample Data Files/users.txt");

    for(size_t i = 0; i < users.size(); i++){
        file << users[i].getID() << " ";
        file << users[i].getName();
        for(size_t j = 0; j < users[i].getBorrowedItems<Book>().size();j++){
            file << " " << users[i].getBorrowedItems<Book>()[j].getISBN();
        }
        for(size_t j = 0; j < users[i].getBorrowedItems<DVD>().size();j++){
            file << " " << users[i].getBorrowedItems<DVD>()[j].getID();
        }
        if(i != users.size()-1)file << "\n";
    }
}

/*
function to read the users, after reading in id and name it decides that
it is reading in a book or a dvd based on whether the id contains a
'-' as the dvdID is just an int after that it just reads them into a their vectors
until there are no more lines to read
*/
void Library::readUsers(){
    std::string fileNameUsers = "Sample Data Files/users.txt";
    std::ifstream fileUsers(fileNameUsers);

    if(!fileUsers.is_open()){
        std::cerr << "Error opening file " << fileNameUsers << std::endl;
    }

    std::string buff;
    while(std::getline(fileUsers,buff)){
        std::istringstream iss(buff);
        int userID;
        std::string name;
        iss >> userID >> name;

        User user;
        user.setID(userID);
        user.setName(name);

        std::string isbnOrDVDID;
        while(iss >> isbnOrDVDID){
            if(isbnOrDVDID.find('-') != std::string::npos){
                std::pair<bool,Book> borrowedBook = findItemByID<Book>(isbnOrDVDID);

                if(borrowedBook.first){
                    user.addNewBorrowedItem<Book>(borrowedBook.second);
                }else {
                    std::cerr << "Error: Book with ISBN " << isbnOrDVDID << " not found." << std::endl;
                }
            }else{
                int dvdID = std::stoi(isbnOrDVDID);
                std::pair<bool,DVD> borrowedDVD = findItemByID<DVD>(dvdID);

                if(borrowedDVD.first){
                    user.addNewBorrowedItem<DVD>(borrowedDVD.second);
                }else {
                    std::cerr << "Error: DVD with ID " << dvdID << " not found." << std::endl;
                }
            }
        }
        this->users.push_back(user);
    }
    fileUsers.close();
}

/*
template function to find an item by id(also works for users)
it takes the id iterates through the items vector and finds the position of the id
returns true or false on whether or not it exists and returns the iterator pointer
i.e. where the item is located
*/
template <typename T, typename ID> std::pair<bool, T> Library::findItemByID(ID id){
    std::vector<T>* items = getItemContainer<T>();

    typename std::vector<T>::iterator it = std::find_if(items->begin(),items->end(), [id](T& item)->bool{
        if constexpr (std::is_same_v<T,Book>){
            return id == item.getISBN();
        }else{
            return id == item.getID();
        }
    });

    if(it != items->end()){
        return std::make_pair(true, *it);
    }else{
        return std::make_pair(false, T());
    }return std::make_pair(false, T());
}

/*
reading quoted string, only used when reading the inventory file
*/
std::string Library::readQuotedString(std::istringstream& iss){
    std::string token;
    char quote;

    iss >> quote;

    std::getline(iss,token,quote);

    return token;
}

/*
template function to find an item's index, used when borrowing a book
due to my decision to print the available items with index+1 for the user to
be able to just input that
*/
template <typename T> size_t Library::findItemIndex(size_t choice){
    size_t index;
    size_t counter = 0;
    std::vector<T>* items = getItemContainer<T>();
    for(index = 0; index < items->size();index++){
        if(items->at(index).getAvailable())counter++;
        if(counter==choice)return index;
    }
    return 0;
}

/*
template function to display available items, just prints each available item with
counter+1 at the start
*/
template <typename T> void Library::displayAvailableItems(){
    size_t counter = 0;
    std::vector<T>* items = getItemContainer<T>();
    for(size_t i = 0; i < items->size(); i++){
        if(items->at(i).getAvailable()){
            std::cout << counter+1 << ". " << items->at(i).getTitle() << std::endl;
            counter++;
        }
    }
}

void Library::createNewUser(){
    int newUserID;
    std::string newName;
    bool valid = 0;
    std::cout << "Enter id of new user" << std::endl;

    while(!valid){
        std::cin >> newUserID;
        if(findItemByID<User>(newUserID).first){
            std::cout << "User id already taken please enter another" << std::endl;
        }else{
            valid = 1;
        }
    }
    std::cout << "Enter name" << std::endl;
    std::cin >> newName;

    User newUser;
    newUser.setID(newUserID);
    newUser.setName(newName);

    this->users.push_back(newUser);
}

/*
display all users function, i believe this was just for testing and isnt actually used anywhere
but it works
*/
void Library::displayAllUsers(){
    for(size_t i = 0; i < this->users.size(); i++){
        std::cout << this->users[i].getID() << std::endl;
        std::cout << this->users[i].getName() << std::endl;
        std::cout << "Books: " << std::endl;
        for(size_t j = 0; j < this->users[i].getBorrowedItems<Book>().size(); j++){
            std::cout << this->users[i].getBorrowedItems<Book>()[j].getTitle() << std::endl;
        }
        std::cout << "\n";
    }
}

/*
template function to add a new item to either books or dvds
*/
template <typename T>
void Library::addNewItem(T newItem){
    std::vector<T>* items = getItemContainer<T>();
    items->push_back(newItem);
}

/*
template function to remove an item from books or dvds, opposite of add
but has to iterate through the items to find the position first
*/
template <typename T> void Library::deleteItem(T itemToDelete){
    std::vector<T>* items = getItemContainer<T>();

    typename std::vector<T>::iterator it = std::find(items->begin(),items->end(),itemToDelete);

    if(it != items->end()){
        items->erase(it);
    }else{
        std::cout << "Item not found" << std::endl;
    }
}

/*
template function to get items
*/
template <typename T> std::vector<T> Library::getItems(){
    std::vector<T>* items = getItemContainer<T>();
    return (*items);
}

/*
template function to set items, i dont think this is ever used
but i made it just in case
*/
template <typename T> void Library::setItems(std::vector<T> newItems){
    std::vector<T>* items = getItemContainer<T>();
    (*items) = newItems;
}

/*
template helper function to get the vector needed depended on the scenario
*/
template <typename T> std::vector<T>* Library::getItemContainer(){
    if constexpr(std::is_same_v<T,Book>){
        return &books;
    }else if constexpr(std::is_same_v<T, DVD>){
        return &dvds;
    }else if constexpr(std::is_same_v<T, User>){
        return &users;
    }else{
    }
}

//explicit instantiation of template functions
template void Library::addNewItem<Book>(Book newItem);
template void Library::addNewItem<DVD>(DVD newItem);
template void Library::addNewItem<User>(User newItem);
template void Library::deleteItem<Book>(Book itemToDelete);
template void Library::deleteItem<DVD>(DVD itemToDelete);
template void Library::deleteItem<User>(User itemToDelete);
template void Library::searchItem<Book>(std::string searchTitle);
template void Library::searchItem<DVD>(std::string searchTitle);
template void Library::displayAvailableItems<Book>();
template void Library::displayAvailableItems<DVD>();
template std::pair<bool, Book> Library::findItemByID<Book>(std::string id);
template std::pair<bool, DVD> Library::findItemByID<DVD>(int id);
template std::pair<bool, User> Library::findItemByID<User>(int id);
template size_t Library::findItemIndex<Book>(size_t choice);
template size_t Library::findItemIndex<DVD>(size_t choice);
template void Library::borrowItem<Book>(Book newItem);
template void Library::borrowItem<DVD>(DVD newItem);
template void Library::returnBorrowedItem<Book>(Book oldItem);
template void Library::returnBorrowedItem<DVD>(DVD oldItem);
template std::vector<Book> Library::getItems<Book>();
template std::vector<DVD> Library::getItems<DVD>();
template std::vector<User> Library::getItems<User>();
template void Library::setItems<Book>(std::vector<Book> newItems);
template void Library::setItems<DVD>(std::vector<DVD> newItems);
template void Library::setItems<User>(std::vector<User> newItems);