
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"


Employee* Create_employee(int id, char name[50], int age, float salary) {
    Employee* employee = (Employee*)malloc(sizeof(Employee));
    if (!employee) {
        fprintf(stderr, "Failed to allocate memory for employee struct");
        return NULL;
    }

    employee->id = id;
    employee->age = age;
    employee->salary = salary;
    strcpy(employee->name, name);

    return employee;
}

void Destroy_employee(Employee* employee) {
    if (employee) {
        free(employee);
    }
}

void printEmployeeInfo(Employee* employee) {
    printf("%d, %s, %d, %f\n", employee->id, employee->name, employee->age, employee->salary);
}