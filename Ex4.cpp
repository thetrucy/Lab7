#include "hospital.h"
#include <sstream>


//--------------------------------PERSONNEL-------------------------------------

Personnel::Personnel() : fullName(""), dateOfBirth(""), personnelCode("") {}

Personnel::Personnel(const string& name, const string& dob, const string& code)
    : fullName(name), dateOfBirth(dob), personnelCode(code) {}

string Personnel::getFullName() const {
    return fullName; 
}
string Personnel::getDateOfBirth() const {
    return dateOfBirth; 
}
string Personnel::getPersonnelCode() const {
    return personnelCode; 
}

void Personnel::setFullName(const string& name) {
    fullName = name; 
}
void Personnel::setDateOfBirth(const string& dob) {
    dateOfBirth = dob; 
}
void Personnel::setPersonnelCode(const string& code) {
    personnelCode = code;
}

//--------------------------------DOCTOR-------------------------------------

Doctor::Doctor() : Personnel(), yearsOfExperience(0), specialty(""), weeklyConsultations(0) {}

Doctor::Doctor(const string& name, const string& dob, const string& code,
               int experience, const string& spec, int consultations)
    : Personnel(name, dob, code), yearsOfExperience(experience), 
      specialty(spec), weeklyConsultations(consultations) {}

double Doctor::calculateSalary() const {
    return (yearsOfExperience * 1.5 + weeklyConsultations * 0.5) * 30000;
}


//--------------------------------NURSES-------------------------------------

Nurse::Nurse() : Personnel(), dailyPatientCare(0) {}

Nurse::Nurse(const string& name, const string& dob, const string& code, int dailyCare)
    : Personnel(name, dob, code), dailyPatientCare(dailyCare) {}

double Nurse::calculateSalary() const {
    return (dailyPatientCare * 0.8) * 20000;
}

//--------------------------------TECHNICIAN-------------------------------------

Technician::Technician() : Personnel(), technicalExperience(0) {}

Technician::Technician(const string& name, const string& dob, const string& code,
                       const vector<string>& equipment, int experience)
    : Personnel(name, dob, code), equipmentCodes(equipment), technicalExperience(experience) {}

double Technician::calculateSalary() const {
    return (equipmentCodes.size() * 2 + technicalExperience) * 25000;
}

void Technician::addEquipment(const string& equipmentCode) {
    equipmentCodes.push_back(equipmentCode);
}

void Technician::removeEquipment(const string& equipmentCode) {
    for(int i = 0; i < equipmentCodes.size(); i++) {
        if (equipmentCodes[i] == equipmentCode)
            equipmentCodes.erase(equipmentCodes.begin() + i);
    }
}

//--------------------------------ADMIN-------------------------------------

AdministrativeStaff::AdministrativeStaff() : Personnel(), workExperience(0), monthlyProcessedDocuments(0) {}

AdministrativeStaff::AdministrativeStaff(const string& name, const string& dob, const string& code,
                                       int experience, int documents)
    : Personnel(name, dob, code), workExperience(experience), monthlyProcessedDocuments(documents) {}

double AdministrativeStaff::calculateSalary() const {
    return (monthlyProcessedDocuments * 0.3 + workExperience * 1.2) * 22000;
}



//------------------Operator Overloading------------------------------

ostream& operator<<(ostream& os, const Personnel& p) {
    os << "\n=== " << p.getPersonnelType() << " Information ===\n";
    os << "Full Name: " << p.getFullName() << endl;
    os << "Date of Birth: " << p.getDateOfBirth() << endl;
    os << "Personnel Code: " << p.getPersonnelCode() << endl;
    os << "Monthly Salary: " << fixed << setprecision(2) << p.calculateSalary() << endl;
    return os;
}

istream& operator>>(istream& is, Personnel& p) {
    cout << "Enter full name: ";
    is.ignore();
    getline(is, p.fullName);
    cout << "Enter date of birth (DD/MM/YYYY): ";
    getline(is, p.dateOfBirth);
    cout << "Enter personnel code: ";
    getline(is, p.personnelCode);
    return is;
}

ostream& operator<<(ostream& os, const Doctor& d) {
    os << "\n=== Doctor Information ===\n";
    os << "Full Name: " << d.getFullName() << endl;
    os << "Date of Birth: " << d.getDateOfBirth() << endl;
    os << "Personnel Code: " << d.getPersonnelCode() << endl;
    os << "Years of Experience: " << d.yearsOfExperience << endl;
    os << "Specialty: " << d.specialty << endl;
    os << "Weekly Consultations: " << d.weeklyConsultations << endl;
    os << "Monthly Salary: " << fixed << setprecision(2) << d.calculateSalary() << endl;
    return os;
}

istream& operator>>(istream& is, Doctor& d) {
    is >> dynamic_cast<Personnel&>(d);
    cout << "Enter years of experience: ";
    is >> d.yearsOfExperience;
    cout << "Enter specialty: ";
    is.ignore();
    getline(is, d.specialty);
    cout << "Enter weekly consultations: ";
    is >> d.weeklyConsultations;
    return is;
}

ostream& operator<<(ostream& os, const Nurse& n) {
    os << "\n=== Nurse Information ===\n";
    os << "Full Name: " << n.getFullName() << endl;
    os << "Date of Birth: " << n.getDateOfBirth() << endl;
    os << "Personnel Code: " << n.getPersonnelCode() << endl;
    os << "Daily patient care Count: " << n.dailyPatientCare << endl;
    os << "Monthly Salary: " << fixed << setprecision(2) << n.calculateSalary() << endl;
    return os;
}

istream& operator>>(istream& is, Nurse& n) {
    is >> dynamic_cast<Personnel&>(n);
    cout << "Enter daily patient care count: ";
    is >> n.dailyPatientCare;
    return is;
}

ostream& operator<<(ostream& os, const Technician& t) {
    os << "\n=== Technician Information ===\n";
    os << "Full Name: " << t.getFullName() << endl;
    os << "Date of Birth: " << t.getDateOfBirth() << endl;
    os << "Personnel Code: " << t.getPersonnelCode() << endl;
    os << "Technical Experience: " << t.technicalExperience << " years" << endl;
    os << "Equipment Count: " << t.equipmentCodes.size() << endl;
    os << "Equipment Codes: ";
    for (int i = 0; i < t.equipmentCodes.size(); ++i) {
        os << t.equipmentCodes[i];
        if (i < t.equipmentCodes.size() - 1) os << ", ";
    }
    os << endl;
    os << "Monthly Salary: " << fixed << setprecision(2) << t.calculateSalary() << endl;
    return os;
}

istream& operator>>(istream& is, Technician& t) {
    is >> dynamic_cast<Personnel&>(t);
    cout << "Enter technical experience years: ";
    is >> t.technicalExperience;
    cout << "Enter number of equipment managed: ";
    int equipmentCount;
    is >> equipmentCount;
    t.equipmentCodes.clear();
    cout << "Enter equipment codes:\n";
    for (int i = 0; i < equipmentCount; ++i) {
        string code;
        cout << "Equipment " << (i + 1) << ": ";
        is >> code;
        t.equipmentCodes.push_back(code);
    }
    return is;
}

ostream& operator<<(ostream& os, const AdministrativeStaff& a) {
    os << "\n=== Administrative Staff Information ===\n";
    os << "Full Name: " << a.getFullName() << endl;
    os << "Date of Birth: " << a.getDateOfBirth() << endl;
    os << "Personnel Code: " << a.getPersonnelCode() << endl;
    os << "Work Experience: " << a.workExperience << " years" << endl;
    os << "Monthly Processed Documents: " << a.monthlyProcessedDocuments << endl;
    os << "Monthly Salary: " << fixed << setprecision(2) << a.calculateSalary() << endl;
    return os;
}

istream& operator>>(istream& is, AdministrativeStaff& a) {
    is >> dynamic_cast<Personnel&>(a);
    cout << "Enter work experience years: ";
    is >> a.workExperience;
    cout << "Enter monthly processed documents: ";
    is >> a.monthlyProcessedDocuments;
    return is;
}
