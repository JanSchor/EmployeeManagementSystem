
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

int numOfEmployees = 0;
Employee employeeList[100];


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
    char name[50];
    int age;
    float salary;

    // ID
    printf("Enter employee ID: "); // need to search for unique ID
    scanf("%d", &id);

    // Name
    printf("Enter employee name: ");
    while (getchar() != '\n');
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';

    // Age
    printf("Enter employee age: ");
    scanf("%d", &age);

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
    printf("Enter employee ID to search: ");
    scanf("%d", &searchedId);
    for (int empIdx = 0; empIdx < numOfEmployees; empIdx++) {
        if (employeeList[empIdx].id == searchedId) {
            return empIdx;
        }
    }
    return -1;
}

void saveToFile() {
    char fileNameH[32];
    char fileNameSave[50];
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
    char loadFileName[50];
    printf("Enter file path: ");
    scanf("%s", loadFileName);
    FILE* fileLoad = fopen(loadFileName, "r");
    if (!fileLoad) {
        printf("Failed to load the file!\n");
        return;
    }

    char fileLine[100];
    int id;
    int age;
    char name[50];
    float salary;
    Employee* newEmployee;
    while (fgets(fileLine, sizeof(fileLine), fileLoad)) {
        if (sscanf(fileLine, "%d|%49[^|]|%d|%f", &id, name, &age, &salary) == 4) {
            newEmployee = Create_employee(id, name, age, salary);
            employeeList[numOfEmployees] = *newEmployee;
            numOfEmployees++;
        } else {
            fprintf(stderr, "Invalid line detected: \"%s\"", fileLine);
        }
    }
}

int main() {
    
    /*
    Employee* newEmployee = Create_employee(0, "John Doe", 20, 65000);
    if (newEmployee != NULL) {
        employeeList[numOfEmployees] = *newEmployee;
        printf("Employee added successfully");
        numOfEmployees++;
    }
    newEmployee = Create_employee(1, "Michael Scott", 30, 20000);
    if (newEmployee != NULL) {
        employeeList[numOfEmployees] = *newEmployee;
        printf("Employee added successfully");
        numOfEmployees++;
    }
    */
    int choice;
    int searchedEmployeeIdx;
    while (1) {
        printMainMenu();
        printf("Enter your choice: ");
        while (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number: ");  
        }
        switch(choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
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
            case 6:
                printf("Goodbye!\n");
                // destroy all structs
                return 0;
                break;
            default:
                printf("Invalid choice, try again!\n");
                choice = 0;
                break;
        }
    }
    return 0;
}