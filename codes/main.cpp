#include "FileManager.hpp"
#include <iostream>
int main() {
    FileManager fm;
    int choice = 0;
    while (choice != 7) {
        fm.displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        fm.handleUserChoice(choice);
    }
    return 0;
}
