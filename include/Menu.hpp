#pragma once

#include "Library.hpp"

void displayInitialMenu();
void processInitialMenu();
void addRemoveItemMenu();
void setCurrentUser();
void searchItemByTitle();
void borrowReturnItem();
void borrowItem();
void returnItem();
void displayBorrowedBooks();
void displayBorrowedDVDs();

extern User currentUser;