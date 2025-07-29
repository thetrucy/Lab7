#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <memory>
using namespace std;


class Personnel {
protected:
    string fullName;
    string dateOfBirth;
    string personnelCode;
    
public:
    Personnel();
    Personnel(const string& name, const string& dob, const string& code);
    virtual ~Personnel() = default;
    

    virtual double calculateSalary() const = 0;
    virtual string getPersonnelType() const = 0;

    string getFullName() const;
    string getDateOfBirth() const;
    string getPersonnelCode() const;

    void setFullName(const string& name);
    void setDateOfBirth(const string& dob);
    void setPersonnelCode(const string& code);

    friend ostream& operator << (ostream& os, const Personnel &p);
    friend istream& operator >> (istream& is, Personnel &p);
};



class Doctor : public Personnel {
private:
    int yearsOfExperience;
    string specialty;
    int weeklyConsultations;
    
public:
    Doctor();
    Doctor(const string& name, const string& dob, const string& code,
           int experience, const string& specialty, int consultations);
    

    double calculateSalary() const override;
    string getPersonnelType() const override { return "Doctor"; }

    int getYearsOfExperience() const { return yearsOfExperience; }
    string getSpecialty() const { return specialty; }
    int getWeeklyConsultations() const { return weeklyConsultations; }
    

    void setYearsOfExperience(int years) { yearsOfExperience = years; }
    void setSpecialty(const string& spec) { specialty = spec; }
    void setWeeklyConsultations(int consultations) { weeklyConsultations = consultations; }
    friend ostream& operator << (ostream& os, const Doctor &d);
    friend istream& operator >> (istream& is, Doctor &d);
};

class Nurse : public Personnel {
private:
    int dailyPatientCare;
    
public:
    Nurse();
    Nurse(const string& name, const string& dob, const string& code, int dailyCare);

    double calculateSalary() const override;
    string getPersonnelType() const override { return "Nurse"; }

    int getDailyPatientCare() const { return dailyPatientCare; }
    
    void setDailyPatientCare(int care) { dailyPatientCare = care; }

    friend ostream& operator << (ostream& os, const Nurse &n);
    friend istream& operator >> (istream& is, Nurse &n);
};

class Technician : public Personnel {
private:
    vector<string> equipmentCodes;
    int technicalExperience;
    
public:
    Technician();
    Technician(const string& name, const string& dob, const string& code,
               const vector<string>& equipment, int experience);
    

    double calculateSalary() const override;
    string getPersonnelType() const override { return "Technician"; }

    void addEquipment(const string& equipmentCode);
    void removeEquipment(const string& equipmentCode);
    

    vector<string> getEquipmentCodes() const { return equipmentCodes; }
    int getTechnicalExperience() const { return technicalExperience; }
    int getEquipmentCount() const { return equipmentCodes.size(); }
    

    void setEquipmentCodes(const vector<string>& equipment) { equipmentCodes = equipment; }
    void setTechnicalExperience(int experience) { technicalExperience = experience; }

    friend ostream& operator << (ostream& os, const Technician &t);
    friend istream& operator >> (istream& is, Technician &t);
};

class AdministrativeStaff : public Personnel {
private:
    int workExperience;
    int monthlyProcessedDocuments;
    
public:
    AdministrativeStaff();
    AdministrativeStaff(const string& name, const string& dob, const string& code,
                       int experience, int documents);
    

    double calculateSalary() const override;
    string getPersonnelType() const override { return "Administrative Staff"; }
    
    int getWorkExperience() const { return workExperience; }
    int getMonthlyProcessedDocuments() const { return monthlyProcessedDocuments; }

    void setWorkExperience(int experience) { workExperience = experience; }
    void setMonthlyProcessedDocuments(int documents) { monthlyProcessedDocuments = documents; }

    friend ostream& operator << (ostream& os, const AdministrativeStaff &a);
    friend istream& operator >> (istream& is, AdministrativeStaff &a);
};
