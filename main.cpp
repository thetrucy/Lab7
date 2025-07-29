#include "hospital.h"


struct Node {
    Personnel* staff;
    Node* pnext;
    
    Node(Personnel* person) : staff(person), pnext(nullptr) {}
};

class HospitalHR {
private:
    string hospitalName;
    Node* phead;
    static int numstaff;
    
public:
    HospitalHR(const string& name);
    ~HospitalHR();

    void addPersonnel(Personnel* person);
    void removePersonnel(const string& personnelCode);
    Personnel* findPersonnel(const string& personnelCode);
    void updatePersonnel(const string& personnelCode);
    
    void displayAllStaff() const;
    void displayStaffByType(const string& type) const;
};

int HospitalHR::numstaff = 0;
HospitalHR::HospitalHR(const string& name) : hospitalName(name), phead(nullptr) {}

HospitalHR::~HospitalHR() {
    Node* current = phead;
    while (current != nullptr) {
        Node* temp = current;
        current = current->pnext;
        delete temp->staff;  
        delete temp;         
    }
}

void HospitalHR::addPersonnel(Personnel* person) {
    if (person == nullptr) return;
    if(findPersonnel(person->getPersonnelCode()) == nullptr){
        Node* newNode = new Node(person);
        newNode->pnext = phead;
        phead = newNode;
        numstaff++;
        cout << "Added " << person->getPersonnelType() << ": " << person->getFullName() << endl;
    } else {
        cout << "Personnel code '" << person->getPersonnelCode() << "' already exists. Cannot add duplicate." << endl;
    }
}

void HospitalHR::removePersonnel(const string& personnelCode) {
    if (phead == nullptr) {
        cout << "No personnel to remove.\n";
        return;
    }
    
    if (phead->staff->getPersonnelCode() == personnelCode) {
        Node* temp = phead;
        cout << "Removed " << temp->staff->getPersonnelType() << ": " << temp->staff->getFullName() << endl;
        phead = phead->pnext;
        delete temp->staff;
        delete temp;
        numstaff--;
        return;
    }
    
    Node* current = phead;
    while (current->pnext != nullptr && current->pnext->staff->getPersonnelCode() != personnelCode) {
        current = current->pnext;
    }
    
    if (current->pnext == nullptr) {
        cout << "Personnel with code " << personnelCode << " not found.\n";
        return;
    }
    
    Node* temp = current->pnext;
    cout << "Removed " << temp->staff->getPersonnelType() << ": " << temp->staff->getFullName() << endl;
    current->pnext = temp->pnext;
    delete temp->staff;
    delete temp;
    numstaff--;
}

Personnel* HospitalHR::findPersonnel(const string& personnelCode) {
    Node* current = phead;
    while (current != nullptr) {
        if (current->staff->getPersonnelCode() == personnelCode) {
            return current->staff;
        }
        current = current->pnext;
    }
    return nullptr;
}

void HospitalHR::updatePersonnel(const string& personnelCode) {
    Personnel* person = findPersonnel(personnelCode);
    if (person == nullptr) {
        cout << "Personnel with code " << personnelCode << " not found.\n";
        return;
    }
    
    cout << "Current information:\n";
    cout << *person;
    cout << "Enter updated information:\n";
    cin >> *person;
    cout << "Personnel updated successfully.\n";
}

void HospitalHR::displayAllStaff() const {
    cout << "\n" << string(60, '=') << endl;
    cout << "ALL STAFF AT " << hospitalName << endl;
    cout << string(60, '=') << endl;
    
    if (phead == nullptr) {
        cout << "No staff members found.\n";
        return;
    }
    
    Node* current = phead;
    while (current != nullptr) {
        cout << *current->staff;
        cout << string(40, '-') << endl;
        current = current->pnext;
    }
}

void HospitalHR::displayStaffByType(const string& type) const {
    cout << "\n=== " << type << "S AT " << hospitalName << " ===\n";
    bool found = false;
    
    Node* current = phead;
    while (current != nullptr) {
        if (current->staff->getPersonnelType() == type) {
            cout << *current->staff;
            cout << string(40, '-') << endl;
            found = true;
        }
        current = current->pnext;
    }
    
    if (!found) {
        cout << "No " << type << "s found.\n";
    }
}

void displayMenu() {
    cout << "\n" << string(50, '=') << endl;
    cout << "HOSPITAL HR MANAGEMENT SYSTEM\n";
    cout << string(50, '=') << endl;
    cout << "1. Add Doctor\n";
    cout << "2. Add Nurse\n";
    cout << "3. Add Technician\n";
    cout << "4. Add Administrative Staff\n";
    cout << "5. Display All Staff\n";
    cout << "6. Display All Staff by type\n";
    cout << "7. Search Personnel\n";
    cout << "8. Remove Personnel\n";
    cout << "9. Update Personnel\n";
    cout << "0. Exit\n";
    cout << string(50, '-') << endl;
    cout << "Enter your choice: ";
}

int main() {
    cout << "=== HOSPITAL HUMAN RESOURCES MANAGEMENT SYSTEM ===\n";
    
    string hospitalName;
    cout << "Enter hospital name: ";
    getline(cin, hospitalName);
    
    HospitalHR hospital(hospitalName);
    int choice;
    
    //Perform
    hospital.addPersonnel(new Doctor("Dr. John Smith", "15/03/1980", "DOC001", 10, "Internal Medicine", 25));
    hospital.addPersonnel(new Doctor("Dr. Nguyen", "15/03/2000", "DOC002", 12, "Something", 4));
    hospital.addPersonnel(new Nurse("Sarah Johnson", "22/07/1985", "NUR001", 15));
    hospital.addPersonnel(new Technician("Mike Wilson", "10/01/1990", "TEC001", vector<string>{"T01", "D03", "M22"}, 5));
    hospital.addPersonnel(new Technician("Mike Wilson", "10/01/1990", "TEC004", vector<string>{"T02", "E03", "F42"}, 5));
    hospital.addPersonnel(new AdministrativeStaff("Lisa Brown", "05/12/1982", "ADM001", 8, 150));
    
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                Doctor* doctor = new Doctor();
                cin >> *doctor;
                hospital.addPersonnel(doctor);
                break;
            }
            
            case 2: {
                Nurse* nurse = new Nurse();
                cin >> *nurse;
                hospital.addPersonnel(nurse);
                break;
            }
            
            case 3: {
                Technician* technician = new Technician();
                cin >> *technician;
                hospital.addPersonnel(technician);
                break;
            }
            
            case 4: {
                AdministrativeStaff* admin = new AdministrativeStaff();
                cin >> *admin;
                hospital.addPersonnel(admin);
                break;
            }
            
            case 5:
                hospital.displayAllStaff();
                break;
                
            case 6: {
                cout << "Enter staff type (Doctor/Nurse/Technician/Administrative Staff): ";
                string type;
                cin.ignore();
                getline(cin, type);
                hospital.displayStaffByType(type);
                break;
            }
 
            case 7: {
                cout << "Enter personnel code: ";
                string code;
                cin >> code;
                Personnel* person = hospital.findPersonnel(code);
                if (person) {
                    cout << *person;
                } else {
                    cout << "Personnel not found.\n";
                }
                break;
            }
            
            case 8: {
                cout << "Enter personnel code to remove: ";
                string code;
                cin >> code;
                hospital.removePersonnel(code);
                break;
            }
            
            case 9: {
                cout << "Enter personnel code to update: ";
                string code;
                cin >> code;
                hospital.updatePersonnel(code);
                break;
            }
                   
            case 0:
                cout << "Thank you for using Hospital HR Management System!\n";
                break;
                
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        
        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
