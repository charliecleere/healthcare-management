#pragma once

#include "Employee.h"

// A case manager extends the shared employee identity with salary and degree data.
class CaseManager : public Employee
{
public:
	// Initializes the case manager's employee and role-specific fields.
	CaseManager(int i = 0, std::string fn = "", std::string ln = " ", double s = 0.0, std::string d = "");

	~CaseManager();

	// Accessors and mutators for case-manager-specific fields.
	void setSalary(double s);
	void setDegree(std::string d);
	double getSalary() const;
	std::string getDegree() const;

	// Writes the case manager's complete employee report entry.
	void printDetails(std::ostream& out) const;
private:
	double salary;
	std::string degree;
};
