#pragma once

#include "Employee.h"

// A nurse extends the shared employee identity with wage and designation data.
class Nurse : public Employee
{
public:
	// Initializes the nurse's employee and role-specific fields.
	Nurse(int i = 0, std::string fn = "", std::string ln = "", double hw = 0.0, std::string d = "");

	~Nurse();

	// Accessors and mutators for nurse-specific fields.
	void setHourlyWage(double hw);
	void setDesignation(std::string d);
	double getHourlyWage() const;
	std::string getDesignation() const;

	// Writes the nurse's complete employee report entry.
	void printDetails(std::ostream& out) const;

private:
	double hourly_wage;
	std::string designation;
};
