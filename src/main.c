
#include <stdio.h>
#include "help_lib.h"


int main() {
    int end = 0;
    if (initEmployeeList()) end = 1;
    int choice;
    
    while (!end) {
        printMainMenu();
        getInputDigit("Enter your choice: ", &choice);
        switch(choice) {
            case 1: // Add
                addEmployee();
                break;
            case 2: // Display
                displayEmployees();
                break;
            case 3: // Search
                searchEmployeeById();
                break;
            case 4: // Save
                saveToFile();
                break;
            case 5: // Load
                loadFromFile();
                break;
            case 6: // Exit
                end = 1;
                break;
            default: // Invalid
                printf("Invalid choice, try again!\n");
                choice = 0;
                break;
        }
    }
    freeAllEmployees();
    printf("Goodbye!\n");
    return 0;
}

/*
Handle these errors:

name to be less than 50 chars
name to not contain pipe character
salary to be float or number
extra chars at digit input
*/