#pragma once

#include "Employee.h"

// An aide extends the shared employee identity with wage and certification data.
class Aide : public Employee
{
public:
	// Initializes the aide's employee and role-specific fields.
	Aide(int i = 0, std::string fn = "", std::string ln = "", double hw = 0.0, std::string c = "");

	~Aide();

	// Accessors and mutators for aide-specific fields.
	void setHourlyWage(double hw);
	void setCertification(std::string c);
	double getHourlyWage() const;
	std::string getCertification() const;

	// Writes the aide's complete employee report entry.
	void printDetails(std::ostream& out) const;
private:
	double hourly_wage;
	std::string certification;
};
