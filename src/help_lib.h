
//#include <stdio.h>

#ifndef HELP_LIB_H
#define HELP_LIB_h

int initEmployeeList();
int isIdUnique(int id);
void getInputDigit(char inputText[100], int* destination);
int lowestPossibleId();
void printMainMenu();
void addEmployee();
void displayEmployees();
void searchEmployeeById();
void saveToFile();
void loadFromFile();

#endif // HELP_LIB_H
