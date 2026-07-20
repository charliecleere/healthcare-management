#pragma once

#include "Visit.h"
#include "CaseManager.h"

class Patient
{
public:
	// Multi-argument constructor with default parameters
	Patient(int i = 0, std::string fn = "", std::string ln = "", std::string sa = "", int a = 0, double h = 0.0, double w = 0.0, char g = ' ', bool ia = false, CaseManager cm = CaseManager());
	~Patient();

	// Get and set functions (or accessor and mutator functions)
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
	
	// Overloaded insertion operator to print patient details
	friend std::ostream& operator<<(std::ostream& out, const Patient& patient);  

	// Overloaded less-than operator to compare patients by first name for sorting
	bool operator<(const Patient& other) const;

	// Overloaded pre-increment operator to increment the patient's age by 1 year
	Patient operator++();

	// Overloaded post-increment operator to increment the patient's age by 1 year
	Patient operator++(int);

	// Other functions from Lab 2
	bool addSingleBpm(int temp_bpm_reading);
	int getSingleBpm(int index) const;
	int getBpmCount() const;
	void sortBpms();
	int findMinBpm() const;
	int findMaxBpm() const;
	double calculateAvgBpm() const;

	// Other functions from Lab 3
	void addVisit(Visit v);

	Visit getVisit(int index) const;
	int getNumOfVisits() const;
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
