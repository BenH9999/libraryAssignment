/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

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
template <typename T> void displayBorrowedItems();
template <typename T> std::vector<T> getItemContainer();

extern User currentUser;