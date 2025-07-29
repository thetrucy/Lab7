#include "hospital.h"
#include <sstream>


//--------------------------------PERSONNEL-------------------------------------

Personnel::Personnel() : fullName(""), dateOfBirth(""), personnelCode("") {}

Personnel::Personnel(const string& name, const string& dob, const string& code)
    : fullName(name), dateOfBirth(dob), personnelCode(code) {}

void Personnel::displayInfo() const {
    cout << *this;
}

void Personnel::inputInfo() {
    cin >> *this;
}

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

void Doctor::displaySpecificInfo() const {
    cout << "Years of Experience: " << yearsOfExperience << endl;
    cout << "Specialty: " << specialty << endl;
    cout << "Weekly Consultations: " << weeklyConsultations << endl;
}

void Doctor::inputInfo() {
    cin >> *this;
}

//--------------------------------NURSES-------------------------------------

Nurse::Nurse() : Personnel(), dailyPatientCare(0) {}

Nurse::Nurse(const string& name, const string& dob, const string& code, int dailyCare)
    : Personnel(name, dob, code), dailyPatientCare(dailyCare) {}

double Nurse::calculateSalary() const {
    return (dailyPatientCare * 0.8) * 20000;
}

void Nurse::displaySpecificInfo() const {
    cout << "Daily patient care Count: " << dailyPatientCare << endl;
}

void Nurse::inputInfo() {
    cin >> *this;
}

//--------------------------------TECHNICIAN-------------------------------------

Technician::Technician() : Personnel(), technicalExperience(0) {}

Technician::Technician(const string& name, const string& dob, const string& code,
                       const vector<string>& equipment, int experience)
    : Personnel(name, dob, code), equipmentCodes(equipment), technicalExperience(experience) {}

double Technician::calculateSalary() const {
    return (equipmentCodes.size() * 2 + technicalExperience) * 25000;
}

void Technician::displaySpecificInfo() const {
    cout << "Technical Experience: " << technicalExperience << " years" << endl
     << "Equipment Count: " << equipmentCodes.size() << endl
     << "Equipment Codes: ";
    for (int i = 0; i < equipmentCodes.size(); ++i) {
        cout << equipmentCodes[i];
        if (i < equipmentCodes.size() - 1) cout << ", ";
    }
    cout << endl;
}

void Technician::inputInfo() {
    cin >> *this;
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

void AdministrativeStaff::displaySpecificInfo() const {
    cout << "Work Experience: " << workExperience << " years\n";
    cout << "Monthly Processed Documents: " << monthlyProcessedDocuments << endl;
}

void AdministrativeStaff::inputInfo() {
    cin >> *this;
}


//------------------Operator Overloading------------------------------

ostream& operator<<(ostream& os, const Personnel& p) {
    os << "\n=== " << p.getPersonnelType() << " Information ===\n";
    os << "Full Name: " << p.getFullName() << endl;
    os << "Date of Birth: " << p.getDateOfBirth() << endl;
    os << "Personnel Code: " << p.getPersonnelCode() << endl;
    p.displaySpecificInfo();
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
    os << dynamic_cast<const Personnel&>(d);
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
    os << dynamic_cast<const Personnel&>(n);
    return os;
}

istream& operator>>(istream& is, Nurse& n) {
    is >> dynamic_cast<Personnel&>(n);
    cout << "Enter daily patient care count: ";
    is >> n.dailyPatientCare;
    return is;
}

ostream& operator<<(ostream& os, const Technician& t) {
    os << dynamic_cast<const Personnel&>(t);
    os << "Technical Experience: " << t.technicalExperience << " years" << endl;
    os << "Equipment Count: " << t.equipmentCodes.size() << endl;
    os << "Equipment Codes: ";
    for (int i = 0; i < t.equipmentCodes.size(); ++i) {
        os << t.equipmentCodes[i];
        if (i < t.equipmentCodes.size() - 1) os << ", ";
    }
    os << endl;
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
    os << dynamic_cast<const Personnel&>(a);
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