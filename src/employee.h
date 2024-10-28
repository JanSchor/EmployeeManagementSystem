
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

typedef struct Employee {
    int id;
    char name[50];
    int age;
    float salary;
} Employee;

Employee* Create_employee(int id, char name[50], int age, float salary);
void Destroy_employee(Employee* employee);

void printEmployeeInfo(Employee* employee);


#endif // EMPLOYEE_H