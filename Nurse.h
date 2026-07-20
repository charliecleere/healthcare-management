#pragma once

#include "Employee.h"

// Publicly inherits the Employee class
class Nurse : public Employee
{
public:
	// Five-argument constructor with default parameters
	Nurse(int i = 0, std::string fn = "", std::string ln = "", double hw = 0.0, std::string d = "");

	// Destructor
	~Nurse();

	// Accessor and mutator functions
	void setHourlyWage(double hw);
	void setDesignation(std::string d);
	double getHourlyWage() const;
	std::string getDesignation() const;

	// Other function
	void printDetails(std::ostream& out) const;

private:
	double hourly_wage;
	std::string designation;
};
