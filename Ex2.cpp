#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// a) Implement class Person containing:
//  Data members: full name, date of birth, address
//  Methods: input, output person information
// b) Implement class Employee inheriting from Person with additions:
//  Data members: department, salary coefficient, allowance
//  Methods: override input/output to include all information
//  Main program:
// – Input an array of employees
// – Output the list of employees based on specific conditions: filter and display employees
// whose salaries fall within a given range or/and whose dates of birth are within a
// specified range.

class Date {
private:
    int day;
    int month;
    int year;
public:
    Date();
    Date(int day, int month, int year);
    Date(const string& dateStr); // "dd-mm-yyyy"
    Date(const Date& other);
    Date& operator=(const Date& other);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    friend istream& operator >> (istream& in, Date& date);
    friend ostream& operator << (ostream& out, const Date& date);

    bool operator >= (const Date& other) const;
    bool operator <= (const Date& other) const;
    bool isLeapYear(int year) const;
    int daysInMonth(int m, int y) const;
    bool isValidDate(int d, int m, int y) const;
};

Date::Date() : day(1), month(1), year(1) {}

Date::Date(int d, int m, int y) {
    if (isValidDate(d, m, y)) {
        day = d;
        month = m;
        year = y;
    } else {
        cout << "Invalid date. Using default.\n";
        day = 1;
        month = 1;
        year = 2000;
    }
}

Date::Date(const string& dateStr) { // dd-mm-yyyy format
    
    if (dateStr.length() >= 10) {
        int d = stoi(dateStr.substr(0, 2));
        int m = stoi(dateStr.substr(3, 2));
        int y = stoi(dateStr.substr(6, 4));
        if (! isValidDate(d,m,y)) {
            cout<< "Invalid date\n";
        }
        this->day = d;    
        this->month = m;
        this->year = y;
    } else {
        this->day = 1;
        this->month = 1;
        this->year = 1;
    }
}

Date::Date(const Date& other) {
    day = other.day;
    month = other.month;
    year = other.year;
}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

bool Date::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int Date::daysInMonth(int m, int y) const {
    static const int days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && isLeapYear(y)) return 29;
    return days[m];
}
bool Date::isValidDate(int d, int m, int y) const {
    int daysOfMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year))
        daysOfMonths[2] = 29;
    return (y >= 0 && m >= 1 && m <= 12 && d >= 1 && d <= daysInMonth(m,y));

}

istream& operator>>(istream& in, Date& date) {
    string s;
    getline(in, s);
    date = Date(s);
    return in;
}

ostream& operator<<(ostream& out, const Date& date) {
    out << setfill('0') << setw(2) << date.day << "-" 
        << setw(2) << date.month << "-" << setw(4) << date.year;
    out << setfill(' '); // Reset fill character
    return out;
}

bool Date::operator>=(const Date& other) const {
    if (year != other.year)
        return year >= other.year;
    if (month != other.month)
        return month >= other.month;
    return day >= other.day;
}

bool Date::operator<=(const Date& other) const {
    if (year != other.year)
        return year <= other.year;
    if (month != other.month)
        return month <= other.month;
    return day <= other.day;
}

class Person
{
protected:
    string full_name;
    string dob;
    string address;

public:
    Person();
    Person(string name, string dob, string address);
    Person(const Person &p);
    friend istream &operator>>(istream &in, Person &p);
    friend ostream &operator<<(ostream &out, const Person &p);

    string getDOB() const;
    string getName() const;
};

class Employee : public Person
{
private:
    string department;
    double coefficient;
    double allowance;

public:
    Employee();
    Employee(string name, string dob, string address, string department, double co, double allow);
    Employee(const Employee &e);

    friend istream &operator>>(istream &in, Employee &e);
    friend ostream &operator<<(ostream &out, const Employee &e);

    double getSalary() const;
    string getDepartment() const;
    double getCoefficient() const;
    double getAllowance() const;
};

Person::Person() : full_name(""), dob(""), address("") {}

Person::Person(string name, string dob, string address)
{
    this->full_name = name;
    this->dob = dob;
    this->address = address;
}

Person::Person(const Person &p)
{
    this->full_name = p.full_name;
    this->address = p.address;
    this->dob = p.dob;
}

istream &operator>>(istream &in, Person &p)
{
    cout << "Enter person's full name: ";
    in.ignore();
    getline(in, p.full_name);
    cout << "Enter person's date of birth (dd-mm-yyyy): ";
    getline(in, p.dob);
    cout << "Enter person's address: ";
    getline(in, p.address);
    return in;
}

ostream &operator<<(ostream &out, const Person &p)
{
    out << "Name: " << p.full_name << endl
        << "Date of birth: " << p.dob << endl
        << "Address: " << p.address << endl;
    return out;
}

string Person::getDOB() const {
    return dob;
}

string Person::getName() const {
    return full_name;
}

Employee::Employee() : department(""), coefficient(0), allowance(0), Person() {}

Employee::Employee(string name, string dob, string address, string department, double co, double allow) 
    : Person(name, dob, address)
{
    this->department = department;
    this->coefficient = co;
    this->allowance = allow;
}

Employee::Employee(const Employee &e) : Person(e)
{
    this->department = e.department;
    this->coefficient = e.coefficient;
    this->allowance = e.allowance;
}

istream &operator>>(istream &in, Employee &e)
{
    cout << "Enter employee's full name: ";
    in.ignore();
    getline(in, e.full_name);
    cout << "Enter employee's date of birth (dd-mm-yyyy): ";
    getline(in, e.dob);
    cout << "Enter employee's address: ";
    getline(in, e.address);
    cout << "Enter employee's department: ";
    getline(in, e.department);
    cout << "Enter employee's salary coefficient: ";
    in >> e.coefficient;
    cout << "Enter employee's allowance: ";
    in >> e.allowance;
    return in;
}

ostream &operator<<(ostream &out, const Employee &e)
{
    out << "Name: " << e.full_name << endl
        << "Date of birth: " << e.dob << endl
        << "Address: " << e.address << endl
        << "Department: " << e.department << endl  // Fixed typo
        << "Salary coefficient: " << e.coefficient << endl
        << "Allowance: " << e.allowance << endl
        << "Total salary: " << (e.coefficient + e.allowance) << endl;
    return out;
}

double Employee::getSalary() const { 
    return coefficient + allowance; 
}

string Employee::getDepartment() const { 
    return department; 
}

double Employee::getCoefficient() const { 
    return coefficient; 
}

double Employee::getAllowance() const { 
    return allowance; 
}

// Utility functions for date comparison
bool isDateInRange(const string& date, const string& startDate, const string& endDate) {
    try {
        Date start(startDate);
        Date end(endDate);
        Date edate(date);
        
        return (edate >= start && edate <= end);
    } catch (...) {
        return false; // Return false if date parsing fails
    }
}

// Function to input array of employees
void inputEmployees(vector<Employee>& employees, int count) {
    cout << "\n=== INPUT " << count << " EMPLOYEES ===\n";
    for (int i = 0; i < count; i++) {
        cout << "\nEmployee " << (i + 1) << ":\n";
        Employee emp;
        cin >> emp;
        employees.push_back(emp);
    }
}

// Function to display all employees
void displayAllEmployees(const vector<Employee>& employees) {
    cout << "\n=== ALL EMPLOYEES ===\n";
    for (size_t i = 0; i < employees.size(); i++) {
        cout << "\nEmployee " << (i + 1) << ":\n";
        cout << employees[i];
    }
}

// Function to filter and display employees by salary range
void filterBySalaryRange(const vector<Employee>& employees, double minSalary, double maxSalary) {
    cout << "\n=== EMPLOYEES WITH SALARY BETWEEN " << minSalary << " AND " << maxSalary << " ===\n";
    bool found = false;
    
    for (size_t i = 0; i < employees.size(); i++) {
        double salary = employees[i].getSalary();
        if (salary >= minSalary && salary <= maxSalary) {
            cout << "\nEmployee " << (i + 1) << ":\n";
            cout << employees[i];
            found = true;
        }
    }
    
    if (!found) {
        cout << "No employees found with salary in the specified range.\n";
    }
}

// Function to filter and display employees by date of birth range
void filterByDOBRange(const vector<Employee>& employees, const string& startDate, const string& endDate) {
    cout << "\n=== EMPLOYEES WITH DOB BETWEEN " << startDate << " AND " << endDate << " ===\n";
    bool found = false;
    
    for (size_t i = 0; i < employees.size(); i++) {
        if (isDateInRange(employees[i].getDOB(), startDate, endDate)) {
            cout << "\nEmployee " << (i + 1) << ":\n";
            cout << employees[i];
            found = true;
        }
    }
    
    if (!found) {
        cout << "No employees found with DOB in the specified range.\n";
    }
}

// Function to filter by both salary and DOB range
void filterBySalaryAndDOB(const vector<Employee>& employees, double minSalary, double maxSalary, 
                          const string& startDate, const string& endDate) {
    cout << "\n=== EMPLOYEES WITH SALARY BETWEEN " << minSalary << "-" << maxSalary 
         << " AND DOB BETWEEN " << startDate << "-" << endDate << " ===\n";
    bool found = false;
    
    for (size_t i = 0; i < employees.size(); i++) {
        double salary = employees[i].getSalary();
        if (salary >= minSalary && salary <= maxSalary && 
            isDateInRange(employees[i].getDOB(), startDate, endDate)) {
            cout << "\nEmployee " << (i + 1) << ":\n";
            cout << employees[i];
            found = true;
        }
    }
    
    if (!found) {
        cout << "No employees found matching both criteria.\n";
    }
}

int main()
{
    vector<Employee> employees;
    int numEmployees;
    int choice;
    
    cout << "=== EMPLOYEE MANAGEMENT SYSTEM ===\n";
    cout << "Enter number of employees: ";
    cin >> numEmployees;
    
    if (numEmployees > 0) {
        inputEmployees(employees, numEmployees);
        
        do {
            cout << "\n=== MENU ===\n";
            cout << "1. Display all employees\n";
            cout << "2. Filter by salary range\n";
            cout << "3. Filter by date of birth range\n";
            cout << "4. Filter by both salary and DOB range\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    displayAllEmployees(employees);
                    break;
                    
                case 2: {
                    double minSalary, maxSalary;
                    cout << "Enter minimum salary: ";
                    cin >> minSalary;
                    cout << "Enter maximum salary: ";
                    cin >> maxSalary;
                    filterBySalaryRange(employees, minSalary, maxSalary);
                    break;
                }
                
                case 3: {
                    string startDate, endDate;
                    cout << "Enter start date (dd-mm-yyyy): ";
                    cin.ignore();
                    getline(cin, startDate);
                    cout << "Enter end date (dd-mm-yyyy): ";
                    getline(cin, endDate);
                    filterByDOBRange(employees, startDate, endDate);
                    break;
                }
                
                case 4: {
                    double minSalary, maxSalary;
                    string startDate, endDate;
                    cout << "Enter minimum salary: ";
                    cin >> minSalary;
                    cout << "Enter maximum salary: ";
                    cin >> maxSalary;
                    cout << "Enter start date (dd-mm-yyyy): ";
                    cin.ignore();
                    getline(cin, startDate);
                    cout << "Enter end date (dd-mm-yyyy): ";
                    getline(cin, endDate);
                    filterBySalaryAndDOB(employees, minSalary, maxSalary, startDate, endDate);
                    break;
                }
                
                case 0:
                    cout << "Goodbye!\n";
                    break;
                    
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }
    
    return 0;
}