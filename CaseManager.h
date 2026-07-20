#pragma once

#include "Employee.h"

// Publicly inherits the Employee class
class CaseManager : public Employee
{
public:
	// Five-argument constructor with default parameters
	CaseManager(int i = 0, std::string fn = "", std::string ln = " ", double s = 0.0, std::string d = "");

	// Destructor
	~CaseManager();

	// Accessor and mutator functions
	void setSalary(double s);
	void setDegree(std::string d);
	double getSalary() const;
	std::string getDegree() const;

	// Other function
	void printDetails(std::ostream& out) const;
private:
	double salary;
	std::string degree;
};