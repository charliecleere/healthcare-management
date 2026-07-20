#pragma once

#include "Employee.h"

// Publicly inherits the Employee class
class Aide : public Employee
{
public:
	// Five-argument constuctor with default parameters
	Aide(int i = 0, std::string fn = "", std::string ln = "", double hw = 0.0, std::string c = "");

	// Destructor
	~Aide();

	// Accessor and mutator functions
	void setHourlyWage(double hw);
	void setCertification(std::string c);
	double getHourlyWage() const;
	std::string getCertification() const;

	// Other function
	void printDetails(std::ostream& out) const;
private:
	double hourly_wage;
	std::string certification;
};