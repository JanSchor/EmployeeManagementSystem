
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

#define MAX_NAME_LENGTH 50
#define MAX_FILE_NAME_LENGTH 50
#define MAX_FILE_PATH_LENGTH 100
#define MAX_FILE_LINE_LENGTH 100

int numOfEmployees = 0;
Employee employeeList[100];


int isIdUnique(int id) {
    for (int empIdx = 0; empIdx < numOfEmployees; empIdx++) {
        if (employeeList[empIdx].id == id) return 0;
    }
    return 1;
}

void getInputDigit(char inputText[100], int* destination) {
    printf("%s", inputText);
    while (scanf("%d", destination) != 1) {
        while (getchar() != '\n');
        printf("Invalid input, please enter a number: ");
    }
}

int lowestPossibleId() {
    for (int empIdx = 0; numOfEmployees+1; empIdx++) {
        if (isIdUnique(empIdx)) return empIdx;
    }
    return -1;
}

void printMainMenu() {
    printf(
        "\nEmployee Management System\n"
        "--------------------------\n"
        "1. Add Employee\n"
        "2. Display Employees\n"
        "3. Search Employee by ID\n"
        "4. Save Employees to File\n"
        "5. Load Employees from File\n"
        "6. Exit\n\n"
    );
}

void addEmployee() {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    float salary;

    // ID
    while (1) {
        getInputDigit("Enter employee ID: ", &id);
        if (isIdUnique(id)) break;
        printf("This id is already taken! Recommended id: %d\n", lowestPossibleId());
    }

    // Name
    printf("Enter employee name: ");
    while (getchar() != '\n');
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';

    // Age
    getInputDigit("Enter employee age: ", &age);

    // Salary
    printf("Enter employee salary: ");
    scanf("%f", &salary);

    Employee *newEmployee = Create_employee(id, name, age, salary);
    if (newEmployee != NULL) {
        employeeList[numOfEmployees] = *newEmployee;
        printf("Employee added successfully");
        numOfEmployees++;
        return;
    }
    fprintf(stderr, "Error while creating employee");
}

void displayEmployees() {
    printf("ID\tName\tAge\tSalary\n");
    printf("------------------------------\n");
    for (int empIdx = 0; empIdx < numOfEmployees; empIdx++) {
        printEmployeeInfo(&employeeList[empIdx]);
    }
}

int searchEmployeeById() {
    int searchedId;
    getInputDigit("Enter employee ID to search: ", &searchedId);
    for (int empIdx = 0; empIdx < numOfEmployees; empIdx++) {
        if (employeeList[empIdx].id == searchedId) {
            return empIdx;
        }
    }
    return -1;
}

void saveToFile() {
    char fileNameH[MAX_FILE_NAME_LENGTH];
    char fileNameSave[MAX_FILE_NAME_LENGTH+16];
    printf("Enter file name: ");
    scanf("%s", fileNameH);
    sprintf(fileNameSave, "./files/%s.txt", fileNameH);
    FILE* fileSave = fopen(fileNameSave, "w");
    for (int empIdx = 0; empIdx < numOfEmployees; empIdx++) {
        fprintf(fileSave, "%d|%s|%d|%f\n",
            employeeList[empIdx].id, employeeList[empIdx].name,
            employeeList[empIdx].age, employeeList[empIdx].salary
        );
    }
    fclose(fileSave);
    printf("File created succesfully!\n");
}

void loadFromFile() {
    char loadFilePath[MAX_FILE_PATH_LENGTH];
    printf("Enter file path: ");
    scanf("%s", loadFilePath);
    FILE* fileLoad = fopen(loadFilePath, "r");
    if (!fileLoad) {
        printf("Failed to load the file!\n");
        return;
    }

    char fileLine[MAX_FILE_LINE_LENGTH];
    int id;
    int age;
    char name[MAX_NAME_LENGTH];
    float salary;
    Employee* newEmployee;

    char formatString[50];
    sprintf(formatString, "%%d|%%%d[^|]|%%d|%%f", MAX_NAME_LENGTH-1);

    int linesLoaded = 0;
    int linesNotLoaded = 0;
    while (fgets(fileLine, sizeof(fileLine), fileLoad)) {
        if (sscanf(fileLine, formatString, &id, name, &age, &salary) == 4) {
            if (isIdUnique(id)) {
                newEmployee = Create_employee(id, name, age, salary);
                employeeList[numOfEmployees] = *newEmployee;
                numOfEmployees++;
                linesLoaded++;
            } else {
                linesNotLoaded++;
                fprintf(stderr, "Employee with this id already exists: %s", fileLine);
            }
        } else {
            linesNotLoaded++;
            fprintf(stderr, "Invalid line detected: %s", fileLine);
        }
    }
    printf("Lines succesfully loaded: %d\n", linesLoaded);
    printf("Lines that failed to load: %d\n", linesNotLoaded);
}

int main() {
    int choice;
    int searchedEmployeeIdx;
    while (1) {
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
                searchedEmployeeIdx = searchEmployeeById();
                if (searchedEmployeeIdx == -1) {
                    printf("No employee with this ID found!\n");
                } else {
                    printf("Employee found!\n");
                    printEmployeeInfo(&employeeList[searchedEmployeeIdx]);
                }
                break;
            case 4: // Save
                saveToFile();
                break;
            case 5: // Load
                loadFromFile();
                break;
            case 6: // Exit
                printf("Goodbye!\n");
                return 0;
            default: // Invalid
                printf("Invalid choice, try again!\n");
                choice = 0;
                break;
        }
    }
    return 0;
}


/*
Handle these errors:

name to be less than 50 chars
name to not contain pipe character
salary to be float or number
extra chars at digit input
*/