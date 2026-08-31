#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Employee {
private:
    int empId;                  // Auto-assigned starting from 1001
    string name;                // Non-empty[cite: 4]
    string department;          // Engineering, HR, Finance, Operations[cite: 4]
    char grade;                 // 'A', 'B', 'C', 'D'[cite: 4]
    double basicSalary;         // > 10,000 and < 5,00,000[cite: 4]
    bool isActive;              // Default true; modified via deactivate()[cite: 4]
    static int employeeCount;   // Shared across all objects[cite: 4]

public:
    // Constructor
    Employee() {
        employeeCount++;
        empId = employeeCount;
        name = "Unknown";
        department = "Engineering";
        grade = 'D';
        basicSalary = 10001.0;
        isActive = true;
    }

    // Static member function to retrieve count[cite: 4]
    static int getEmployeeCount() {
        return employeeCount - 1000;
    }

    // Setters with validations[cite: 4, 5]
    void setName(const string& n) {
        if (!n.empty()) {
            name = n;
        } else {
            cout << "ERROR: Name cannot be empty.\n";
        }
    }

    void setDepartment(const string& dept) {
        if (dept == "Engineering" || dept == "HR" || dept == "Finance" || dept == "Operations") {
            department = dept;
        } else {
            cout << "ERROR: '" << dept << "' is not a registered department.\n";
        }
    }

    void setGrade(char g) {
        if (g == 'A' || g == 'B' || g == 'C' || g == 'D') {
            grade = g;
        } else {
            cout << "ERROR: Invalid grade '" << g << "'. Accepted values: A, B, C, D.\n";
        }
    }

    void setBasicSalary(double salary) {
        if (salary > 10000.0 && salary < 500000.0) {
            basicSalary = salary;
        } else {
            cout << "ERROR: Salary must be between Rs.10,000 and Rs.5,00,000. Value rejected.\n";
        }
    }

    void deactivate() {
        isActive = false;
    }

    // Getters (all marked const)[cite: 4, 5]
    int getEmpId() const { return empId; }
    string getName() const { return name; }
    string getDepartment() const { return department; }
    char getGrade() const { return grade; }
    double getBasicSalary() const { return basicSalary; }
    bool getIsActive() const { return isActive; }

    // Business Logic Functions (all marked const)[cite: 4]
    double computeAllowances() const {
        switch (grade) {
            case 'A': return basicSalary * 0.40; // 40%[cite: 4]
            case 'B': return basicSalary * 0.30; // 30%[cite: 4]
            case 'C': return basicSalary * 0.20; // 20%[cite: 4]
            case 'D': return basicSalary * 0.10; // 10%[cite: 4]
            default: return 0.0;
        }
    }

    double computeGrossSalary() const {
        return basicSalary + computeAllowances();
    }

    double computeTax() const {
        double gross = computeGrossSalary();
        if (gross <= 50000.0) {
            return 0.0;
        } else if (gross <= 100000.0) {
            return (gross - 50000.0) * 0.10; // 10% on amount above 50,000[cite: 4]
        } else {
            return 5000.0 + (gross - 100000.0) * 0.20; // 5,000 + 20% on amount above 1,00,000[cite: 4]
        }
    }

    double computeNetSalary() const {
        return computeGrossSalary() - computeTax();
    }

    // Details Input via setters[cite: 4]
    void acceptDetails() {
        string inName, inDept;
        char inGrade;
        double inSalary;

        cout << "\nEnter Details for Employee ID " << empId << ":\n";
        cout << "Enter name: ";
        cin >> ws;
        getline(cin, inName);
        setName(inName);

        cout << "Enter department (Engineering/HR/Finance/Operations): ";
        cin >> inDept;
        setDepartment(inDept);

        cout << "Enter grade (A/B/C/D): ";
        cin >> inGrade;
        setGrade(inGrade);

        cout << "Enter basic salary: ";
        cin >> inSalary;
        setBasicSalary(inSalary);
    }

    // Formatted Payslip Display[cite: 4]
    void printPayslip() const {
        cout << fixed << setprecision(2);
        cout << "\n============================================\n";
        cout << "             EMPLOYEE PAYSLIP               \n";
        cout << "                 AUG 2026                   \n";
        cout << "============================================\n";
        cout << left << setw(18) << "Emp ID" << ": " << empId << "\n";
        cout << left << setw(18) << "Name" << ": " << name << "\n";
        cout << left << setw(18) << "Department" << ": " << department << "\n";
        cout << left << setw(18) << "Grade" << ": " << grade << "\n";
        cout << left << setw(18) << "Status" << ": " << (isActive ? "Active" : "Inactive") << "\n";
        cout << left << setw(18) << "Basic Salary" << ": Rs. " << right << setw(10) << basicSalary << "\n";
        
        string allowLabel = "Allowances (";
        if (grade == 'A') allowLabel += "40%):";
        else if (grade == 'B') allowLabel += "30%):";
        else if (grade == 'C') allowLabel += "20%):";
        else allowLabel += "10%):";
        
        cout << left << setw(18) << allowLabel << ": Rs. " << right << setw(10) << computeAllowances() << "\n";
        cout << left << setw(18) << "Gross Salary" << ": Rs. " << right << setw(10) << computeGrossSalary() << "\n";
        cout << left << setw(18) << "Tax Deduction" << ": Rs. " << right << setw(10) << computeTax() << "\n";
        cout << left << setw(18) << "Net Salary" << ": Rs. " << right << setw(10) << computeNetSalary() << "\n";
        cout << "============================================\n";
    }
};

// Initialize static member starting at 1000 (first employee gets 1001)[cite: 4]
int Employee::employeeCount = 1000;

// Structs for Bonus Question[cite: 4]
struct Layout1 { char c1; int i; char c2; }; // char (1) + pad(3) + int (4) + char (1) + pad(3) = 12 bytes[cite: 4, 5]
struct Layout2 { int i; char c1; char c2; }; // int (4) + char (1) + char (1) + pad(2) = 8 bytes[cite: 4, 5]

int main() {
    // 1. Create objects: one on stack, two on heap[cite: 4]
    Employee e1;
    Employee* e2 = new Employee();
    Employee* e3 = new Employee();

    // 2. Accept Details[cite: 4]
    e1.acceptDetails();
    e2->acceptDetails();
    e3->acceptDetails();

    /*
     * COMPILER ERROR EXPLANATION:
     * e1.empId = 999;
     * e1.basicSalary = -1000;
     * 
     * Reason: 'empId' and 'basicSalary' are private members of class Employee[cite: 4, 5].
     * Direct access from outside the class violates encapsulation and is blocked by the compiler[cite: 5].
     */

    // 3. Print Payslips[cite: 4]
    e1.printPayslip();
    e2->printPayslip();
    e3->printPayslip();

    // 4. Simulate Resignation[cite: 4]
    e3->deactivate();
    if (!e3->getIsActive()) {
        cout << "\n" << e3->getName() << " is no longer active. Payroll skipped." << endl;
    }

    cout << "Total Employees : " << Employee::getEmployeeCount() << endl;

    // Clean up heap objects[cite: 2, 4, 5]
    delete e2;
    delete e3;

    // --- Bonus: Struct Padding & Memory Alignment ---[cite: 4, 5]
    cout << "\n--- BONUS: Struct Padding Analysis ---" << endl;
    cout << "sizeof(Layout1): " << sizeof(Layout1) << " bytes" << endl;
    cout << "sizeof(Layout2): " << sizeof(Layout2) << " bytes" << endl;

    /*
     * PADDING ANALYSIS[cite: 4, 5]:
     * 1. Why sizes differ: CPU accesses memory in word-aligned chunks (typically 4 or 8 bytes)[cite: 5].
     *    In Layout1, int requires 4-byte boundary alignment, inserting 3 padding bytes after c1, and 3 padding bytes after c2 to align the struct (Total: 12 bytes)[cite: 5].
     *    In Layout2, grouping c1 and c2 together needs only 2 padding bytes at the end (Total: 8 bytes)[cite: 5].
     * 2. Compiler adds padding to maximize CPU memory-bus retrieval performance and prevent unaligned memory faults[cite: 5].
     * 3. Member order is critical in network packets and hardware register maps where exact byte offsets must strictly map to protocol fields[cite: 4].
     */

    return 0;
}