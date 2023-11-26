#pragma once

#include "Library.hpp"

void displayInitialMenu();
void processInitialMenu();
void addRemoveBookMenu();
void setCurrentUser();
void searchBookByTitle();
void borrowReturnBook();
void borrowBook();
void returnBook();
void displayBorrowedBooks();

extern User currentUser;