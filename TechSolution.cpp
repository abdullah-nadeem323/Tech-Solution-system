#include <iostream>
#include <string>
using namespace std;

/*
    "TechSolutions Employee Management System"

    . Manages employee personal data, salary, and performance
    . Demonstrates OOP concepts: constructors, copy constructors,
      deep copy vs shallow copy, const/static members, and object handling
    Author: [Abdullah Nadeem]
    Date  : [10-11-2025]
*/

class Employee {
private:
    string* name;                 // dynamically allocated for deep copy demonstration
    int id;
    float salary;
    float performance;           // overall performance score (0-10)

    static int count;            // total number of employees
    static const string companyName; // constant company name

public:
    // Constructor using initializer list
    Employee(const string& n, int id, float salary, float performance = 0.0f)
        : id(id), salary(salary), performance(performance) {
        this->name = new string(n);
        count++;  // increment total employees
    }

    // Deep copy constructor
    Employee(const Employee& other)
        : id(other.id), salary(other.salary), performance(other.performance) {
        name = new string(*(other.name)); // allocate new memory
        count++;
        cout << "[Deep Copy Constructor Called for " << *name << "]\n";
    }

    // Shallow copy constructor
    Employee(Employee* other, bool shallow) {
        id = other->id;
        salary = other->salary;
        performance = other->performance;
        name = other->name; // share memory
        count++;
        cout << "[Shallow Copy Constructor Called for " << *name << "]\n";
    }

    // Destructor to free dynamically allocated memory
    ~Employee() {
        delete name;
    }

    // Set salary
    void setSalary(float salary) {
        this->salary = salary;
    }

    // Set performance
    void setPerformance(float perf) {
        performance = perf;
    }

    // Change employee name 
    void changeName(const string& newName) {
        delete name;
        name = new string(newName);
    }

    // Display employee details
    void display() const {
        cout << "Company: " << companyName << endl;
        cout << "ID      : " << id << endl;
        cout << "Name    : " << *name << endl;
        cout << "Salary  : " << salary << endl;
        cout << "Performance: " << performance << endl;
        cout << "-----------------------------" << endl;
    }

    // Compare salaries
    void compareSalary(const Employee& other) const {
        if (salary > other.salary)
            cout << *name << " has a higher salary than " << *(other.name) << ".\n";
        else if (salary < other.salary)
            cout << *name << " has a lower salary than " << *(other.name) << ".\n";
        else
            cout << *name << " and " << *(other.name) << " have equal salaries.\n";
    }

    // Return a new employee object with a bonus applied
    Employee getBonusEmployee(float bonus) const {
        Employee temp(*name, id, salary + bonus, performance);
        return temp;
    }

    // Static function to show total employees
    static void showTotalEmployees() {
        cout << "Total employees currently: " << count << endl;
    }
};

// Initialize static members
int Employee::count = 0;
const string Employee::companyName = "TechSolutions";

int main() {
    cout << "TechSolutions Employee Management System\n";
    cout << "========================================\n\n";

    Employee* e1 = new Employee("Ali", 101, 50000, 7.5);
    cout << "Employee 1 :\n";
    e1->display();

    Employee e2("Sara", 102, 60000, 8.5);
    cout << "Employee 2:\n";
    e2.display();

    cout << "Comparing Salaries:\n";
    e1->compareSalary(e2);
    cout << "-----------------------------" << endl;

    Employee e3 = e2.getBonusEmployee(5000);
    cout << "After bonus\n";
    cout << "Employee 3:\n";
    e3.display();

    Employee::showTotalEmployees();
    cout << endl;

    // Deep copy demonstration
    cout << "Deep Copy Demonstration\n";
    cout << "-----------------------------" << endl;
    Employee deepOriginal("Abdullah", 201, 70000, 9.0);
    Employee deepCopy(deepOriginal); // deep copy

    cout << "Before changing original:\n";
    deepOriginal.display();
    cout << "The copy is as follow:\n";
    deepCopy.display();

    deepOriginal.changeName("Abdullah Nadeem");
    deepOriginal.setPerformance(9.5);
    cout << "After changing original:\n";
    deepOriginal.display();
    cout << "The effect on the copy is as follow:\n";
    deepCopy.display();
    cout << endl;

    // Shallow copy demonstration
    cout << "Shallow Copy Demonstration\n";
    cout << "-----------------------------" << endl;
    Employee shallowOriginal("Ayesha", 301, 80000, 8.0);
    cout << "Original:\n";
    shallowOriginal.display();

    Employee shallowCopy(&shallowOriginal, true); // shallow copy

    cout << "Shallow Copy after assignment:\n";
    shallowCopy.display();

    // Change original
    shallowOriginal.changeName("Ayesha Khan");
    shallowOriginal.setPerformance(8.5);

    cout << "After changing original:\n";
    shallowOriginal.display();
    cout << "Effect on shallow copy:\n";
    shallowOriginal.display();

    delete e1;

    cout << endl;
    Employee::showTotalEmployees();
    system("pause");
    return 0;
}