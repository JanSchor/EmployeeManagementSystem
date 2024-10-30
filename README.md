# EmployeeManagementSystem
Simple emplyee management system for learning C

## About
This project is simply to learn C and get the basics.

It is simple employee management system, that has a few functions:
1. Add new employee
2. Display all employees
3. Search employee by id
4. Save employees to file
5. Load employees from file
6. Exit

```bash
Employee Management System
--------------------------
1. Add Employee
2. Display Employees
3. Search Employee by ID
4. Save Employees to File
5. Load Employees from File
6. Exit

Enter your choice:
```

Each employee should have ID, Name, Age and Salary

### Adding new employees
User is asked to enter all the desired information for employee.
Except some wrong input cases, there is need to check if ID is unique.
If it is not, the recommendation for lowest ID possible is given.

### Displaying employees
Displays all the employees and their informations

### Searching employees
Searches for employee based on given ID

### Saving to file
Saves all the employees to desired file destination.
Format: `id|name|age|salary`

### Loading from file
Loads all the employees from the file with the same format.
If line is in invalid format or the employee ID on given line is not unique, system does not load the line and prints error on stderr.

### Exit
Just exit
