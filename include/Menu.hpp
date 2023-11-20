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

extern User currentUser;