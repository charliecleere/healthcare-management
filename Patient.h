#pragma once

#include "Visit.h"
#include "CaseManager.h"

class Patient
{
public:
	// Initializes the patient's demographics and optional case-manager assignment.
	Patient(int i = 0, std::string fn = "", std::string ln = "", std::string sa = "", int a = 0, double h = 0.0, double w = 0.0, char g = ' ', bool ia = false, CaseManager cm = CaseManager());
	~Patient();

	// Accessors and mutators for the patient's record.
	void setId(int i);
	void setFirstName(std::string fn);
	void setLastName(std::string ln);
	void setStreetAddress(std::string sa);
	void setAge(int a);
	void setHeight(double h);
	void setWeight(double w);
	void setGender(char g);
	void setIsAmbulatory(bool ia);
	void setCaseManager(CaseManager cm);
	int getId() const;
	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getStreetAddress() const;
	int getAge() const;
	double getHeight() const;
	double getWeight() const;
	char getGender() const;
	bool getIsAmbulatory() const;
	CaseManager getCaseManager() const;
	
	// Writes the patient's report, including case-manager and visit information.
	friend std::ostream& operator<<(std::ostream& out, const Patient& patient);  

	// Orders patients by first name for alphabetical reports.
	bool operator<(const Patient& other) const;

	// Increments the patient's age and returns the updated patient.
	Patient operator++();

	// Increments the patient's age and returns its previous value.
	Patient operator++(int);

	// BPM readings and summary statistics.
	bool addSingleBpm(int temp_bpm_reading);
	int getSingleBpm(int index) const;
	int getBpmCount() const;
	void sortBpms();
	int findMinBpm() const;
	int findMaxBpm() const;
	double calculateAvgBpm() const;

	// Visit management and duplicate-visit checks.
	void addVisit(Visit v);

	Visit getVisit(int index) const;
	int getNumVisits() const;
	bool hasVisitId(int visit_id) const;
private:
	int id;
	std::string first_name;
	std::string last_name;
	std::string street_address;
	int age;
	double height;
	double weight;
	char gender;
	bool is_ambulatory;
	std::vector<int> bpms;
	std::vector<Visit> visits;
	CaseManager case_manager;
};
