#include "Library.hpp"

Library::Library(){
    readInventory();
    readUsers();
}

void Library::borrowBook(Book newBook){
    currentUser.addNewBorrowedBook(newBook);

    for(size_t i = 0; i < books.size();i++){
        if(newBook == books[i]){
            books[i].setAvailable(0);
        }
    }
}

void Library::borrowDVD(DVD newDVD){
    currentUser.addNewBorrowedDVD(newDVD);

    for(size_t i = 0; i < dvds.size();i++){
        if(newDVD == dvds[i]){
            dvds[i].setAvailable(0);
        }
    }
}

void Library::returnBorrowedBook(Book oldBook){
    std::vector<Book>::iterator it = std::find(currentUser.getBorrowedBooks().begin(),currentUser.getBorrowedBooks().end(),oldBook);

    if(it != this->books.end()){
        currentUser.returnBook(it);
    }else{
        std::cout << "Book not found" << std::endl;
    }

    for(size_t i = 0; i < books.size(); i++){
        if(oldBook == books[i]){
            std::cout << "Old book: " << books[i].getTitle() << std::endl;
            books[i].setAvailable(1);
        }
    }
}

void Library::returnBorrowedDVD(DVD oldDVD){
    std::vector<DVD>::iterator it = std::find(currentUser.getBorrowedDVDs().begin(),currentUser.getBorrowedDVDs().end(),oldDVD);

    if(it != this->dvds.end()){
        currentUser.returnDVD(it);
    }else{
        std::cout << "DVD not found" << std::endl;
    }

    for(size_t i = 0; i < dvds.size(); i++){
        if(oldDVD == dvds[i]){
            std::cout << "Old DVD: " << dvds[i].getTitle() << std::endl;
            dvds[i].setAvailable(1);
        }
    }
}

void Library::searchBook(std::string searchTitle){
    bool resultFound = 0;
    std::vector<Book> searchResults;

    for(size_t i = 0; i < books.size();i++){
        resultFound = books[i].getTitle().find(searchTitle) != std::string::npos;
        if(resultFound){
            searchResults.push_back(books[i]);
        }
        resultFound = 0;
    }

    for(size_t i = 0; i < searchResults.size(); i++){
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
        if(users[i].getUserID() == currentUser.getUserID()){
            users[i].setBorrowedBooks(currentUser.getBorrowedBooks());
            users[i].setBorrowedDVDs(currentUser.getBorrowedDVDs());
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
            }
        }
    }
    fileBooks.close();
}

void Library::writeUsers(){
    std::ofstream file("Sample Data Files/users.txt");

    for(size_t i = 0; i < users.size(); i++){
        file << users[i].getUserID() << " ";
        file << users[i].getName();
        for(size_t j = 0; j < users[i].getBorrowedBooks().size();j++){
            file << " " << users[i].getBorrowedBooks()[j].getISBN();
        }
        for(size_t j = 0; j < users[i].getBorrowedDVDs().size();j++){
            file << " " << users[i].getBorrowedDVDs()[j].getID();
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
        user.setUserID(userID);
        user.setName(name);

        std::string isbnOrDVDID;
        while(iss >> isbnOrDVDID){
            if(isbnOrDVDID.find('-') != std::string::npos){
                Book borrowedBook = findBookByISBN(isbnOrDVDID).second;

                if(borrowedBook.getISBN() == isbnOrDVDID){
                    user.addNewBorrowedBook(borrowedBook);
                }
            }else{
                int dvdID = std::stoi(isbnOrDVDID);
                DVD borrowedDVD = findDVDByID(dvdID).second;

                if(borrowedDVD.getID() == dvdID){
                    user.addNewBorrowedDVD(borrowedDVD);
                }
            }
        }
        this->users.push_back(user);
    }
    fileUsers.close();
}

std::pair<bool,User> Library::findUserByUserID(int userID){
    std::vector<User>::iterator it = std::find_if(users.begin(), users.end(),[userID](User& user){
        return user.getUserID() == userID;
    });

    if(it != users.end()){
        return std::make_pair(true, *it);
    }else{
        return std::make_pair(false,User());
    }
}

std::pair<bool,Book> Library::findBookByISBN(std::string isbn){
    std::vector<Book>::iterator it = std::find_if(books.begin(), books.end(), [isbn](Book& book){
        return book.getISBN() == isbn;
    });

    if(it != books.end()){
        return std::make_pair(true,*it);
    }else{
        return std::make_pair(false,Book());
    }
}

std::pair<bool,DVD> Library::findDVDByID(int dvdID){
    std::vector<DVD>::iterator it = std::find_if(dvds.begin(),dvds.end(),[dvdID](DVD& dvd){
        return dvd.getID() == dvdID;
    });

    if(it != dvds.end()){
        return std::make_pair(true, *it);
    }else{
        return std::make_pair(false,DVD());
    }
}

std::string Library::readQuotedString(std::istringstream& iss){
    std::string token;
    char quote;

    iss >> quote;

    std::getline(iss,token,quote);

    return token;
}

size_t Library::findBookIndex(int choice){
    size_t index;
    size_t counter =0;
    for(index = 0; index < books.size(); index++){
        if(books[index].getAvailable()) counter++;
        if(counter == choice) return index;
    }
    return 0;
}

size_t Library::findDVDIndex(int choice){
    size_t index;
    size_t counter =0;
    for(index = 0; index < dvds.size(); index++){
        if(dvds[index].getAvailable())counter++;
        if(counter == choice) return index;
    }
    return 0;
}

void Library::displayAvailableBooks(){
    size_t counter =0;
    for(size_t i = 0; i < this->books.size();i++){
        if(this->books[i].getAvailable()){
            std::cout << counter+1 << ". " << this->books[i].getTitle() << std::endl;
            counter++;
        }
    }
}

void Library::displayAvailableDVDs(){
    size_t counter = 0;
    for(size_t i = 0; i < this->dvds.size(); i++){
        if(this->dvds[i].getAvailable()){
            std::cout << counter+1 << ". " << this->dvds[i].getTitle() << std::endl;
            counter++;
        }
    }
}

void Library::displayAllUsers(){
    for(size_t i = 0; i < this->users.size(); i++){
        std::cout << this->users[i].getUserID() << std::endl;
        std::cout << this->users[i].getName() << std::endl;
        std::cout << "Books: " << std::endl;
        for(size_t j = 0; j < this->users[i].getBorrowedBooks().size(); j++){
            std::cout << this->users[i].getBorrowedBooks()[j].getTitle() << std::endl;
        }
        std::cout << "\n";
    }
}

void Library::addNewBook(Book newBook){
    this->books.push_back(newBook);
}

void Library::addNewUser(User newUser){
    this->users.push_back(newUser);
}

void Library::deleteBook(Book bookToDelete){
    std::vector<Book>::iterator it = std::find(this->books.begin(),this->books.end(),bookToDelete);
    
    if(it != this->books.end()){
        this->books.erase(it);
    }else{
        std::cout << "Book not found" << std::endl;
    }
}

void Library::deleteUser(User userToDelete){
    std::vector<User>::iterator it = std::find(this->users.begin(),this->users.end(),userToDelete);

    if(it != this->users.end()){
        this->users.erase(it);
    }else{
        std::cout << "User not found" << std::endl;
    }
}

std::vector<Book> Library::getBooks(){
    return this->books;
}

std::vector<User> Library::getUsers(){
    return this->users;
}

void Library::setBooks(std::vector<Book> newBooks){
    this->books = newBooks;
}

void Library::setUsers(std::vector<User> newUsers){
    this->users = newUsers;
}