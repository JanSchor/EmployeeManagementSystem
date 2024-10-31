
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "help_lib.h"
#include "employee.h"
#include "config.h"

int numOfEmployees = 0;
//Employee employeeList[100];
Employee* employeeList = NULL;

int initEmployeeList() {
    employeeList = (Employee*)malloc(sizeof(Employee)*10);
    if (!employeeList) {
        fprintf(stderr, "Failed to allocate memory for employeeList!\n");
        return 1;
    }
    return 0;
}

void addEmployeeToList(Employee* employee) {
    static int allocationSize = 10;
    if (numOfEmployees >= allocationSize) {
        allocationSize *= 2;
        employeeList = (Employee*)realloc(employeeList, sizeof(Employee) * allocationSize);
        if (!employeeList) {
            fprintf(stderr, "Failed to allocate memory for employeeList, employee not added!\n");
        }
    }
    employeeList[numOfEmployees] = *employee;
    numOfEmployees++;
    printf("Employee added successfully");
}

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
        //employeeList[numOfEmployees] = *newEmployee;
        addEmployeeToList(newEmployee);
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

void searchEmployeeById() {
    int searchedId;
    int empFound = 0;
    getInputDigit("Enter employee ID to search: ", &searchedId);
    for (int empIdx = 0; empIdx < numOfEmployees; empIdx++) {
        if (employeeList[empIdx].id == searchedId) {
            printEmployeeInfo(&employeeList[empIdx]);
            break;
        }
    }
    if (!empFound) printf("No employee with this ID found!\n");
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
                addEmployeeToList(newEmployee);
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
