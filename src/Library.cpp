#include "Library.hpp"

Library::Library(){
    readInventory();
    readUsers();
}

template <typename T> void Library::borrowItem(T newItem){
    std::pair<std::vector<T>*, int> items = getItemContainer<T>();

    if constexpr (std::is_same_v<T, Book>) {
        currentUser.addNewBorrowedItem<Book>(newItem);
    } else if constexpr (std::is_same_v<T, DVD>) {
        currentUser.addNewBorrowedItem<DVD>(newItem);
    }

    for(size_t i = 0; i < items.first->size();i++){
        if(newItem == items.first->at(i)){
            items.first->at(i).setAvailable(0);
        }
    }
}

template <typename T> void Library::returnBorrowedItem(T oldItem){
    std::pair<std::vector<T>*, int> items = getItemContainer<T>();

    for(size_t i = 0; i < currentUser.getBorrowedItems<T>().size(); i++){
        if(currentUser.getBorrowedItems<T>()[i] == oldItem){
            currentUser.returnItem<T>(i);
        }
    }

    typename std::vector<T>::iterator libraryIT = std::find(items.first->begin(),items.first->end(),oldItem);
    if(libraryIT != items.first->end()){
        libraryIT->setAvailable(1);
        std::cout << "Item returned\n" << std::endl;
    }else{
        std::cerr << "Error: Item not found in library" << std::endl;
    }
}

template <typename T> void Library::searchItem(std::string searchTitle) {
    bool resultFound = false;
    std::vector<T>* itemsForSearch = getItemContainer<T>().first;
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

void Library::syncUserChanges(){
    for(size_t i = 0; i < users.size(); i++){
        if(users[i].getID() == currentUser.getID()){
            users[i].setBorrowedItems<Book>(currentUser.getBorrowedItems<Book>());
            users[i].setBorrowedItems<DVD>(currentUser.getBorrowedItems<DVD>());
            break;
        }
    }
}

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

template <typename T, typename ID> std::pair<bool, T> Library::findItemByID(ID id){
    std::pair<std::vector<T>*, int> items = getItemContainer<T>();

    typename std::vector<T>::iterator it = std::find_if(items.first->begin(),items.first->end(), [id](T& item)->bool{
        if constexpr (std::is_same_v<T,Book>){
            return id == item.getISBN();
        }else{
            return id == item.getID();
        }
    });

    if(it != items.first->end()){
        return std::make_pair(true, *it);
    }else{
        return std::make_pair(false, T());
    }
}

std::string Library::readQuotedString(std::istringstream& iss){
    std::string token;
    char quote;

    iss >> quote;

    std::getline(iss,token,quote);

    return token;
}

template <typename T> size_t Library::findItemIndex(size_t choice){
    size_t index;
    size_t counter = 0;
    std::vector<T>* items = getItemContainer<T>().first;
    for(index = 0; index < items->size();index++){
        if(items->at(index).getAvailable())counter++;
        if(counter==choice)return index;
    }
    return 0;
}

template <typename T> void Library::displayAvailableItems(){
    size_t counter = 0;
    std::vector<T>* items = getItemContainer<T>().first;
    for(size_t i = 0; i < items->size(); i++){
        if(items->at(i).getAvailable()){
            std::cout << counter+1 << ". " << items->at(i).getTitle() << std::endl;
            counter++;
        }
    }
}

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

template <typename T>
void Library::addNewItem(T newItem){
    std::pair<std::vector<T>*, int> items = getItemContainer<T>();
    items.first->push_back(newItem);
}

template <typename T> void Library::deleteItem(T itemToDelete){
    std::pair<std::vector<T>*, int> items = getItemContainer<T>();

    typename std::vector<T>::iterator it = std::find(items.first->begin(),items.first->end(),itemToDelete);

    if(it != items.first->end()){
        items.first->erase(it);
    }else{
        std::cout << "Item not found" << std::endl;
    }
}

template <typename T> std::vector<T> Library::getItems(){
    std::vector<T>* items = getItemContainer<T>().first;
    return (*items);
}

template <typename T> void Library::setItems(std::vector<T> newItems){
    std::vector<T>* items = getItemContainer<T>().first;
    (*items) = newItems;
}

template <typename T> std::pair<std::vector<T>*, int> Library::getItemContainer(){
    if constexpr(std::is_same_v<T,Book>){
        return std::make_pair(&books, BOOK);
    }else if constexpr(std::is_same_v<T, DVD>){
        return std::make_pair(&dvds,DVDs);
    }else if constexpr(std::is_same_v<T, User>){
        return std::make_pair(&users,USER);
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