#include "Nurse.h"

Nurse::Nurse(int i, std::string fn, std::string ln, double hw, std::string d) : Employee(i, fn, ln)
{
	setHourlyWage(hw);
	setDesignation(d);
}

Nurse::~Nurse()
{

}

void Nurse::setHourlyWage(double hw)
{
	if (hw < 0)
	{
		std::cout << "Invalid hourly wage. Hourly wage cannot be negative. Please try again.";
		hourly_wage = -1;
	}
	else
		hourly_wage = hw;
}

void Nurse::setDesignation(std::string d)
{
	designation = d;
}

double Nurse::getHourlyWage() const
{
	return hourly_wage;
}

std::string Nurse::getDesignation() const
{
	return designation;
}

void Nurse::printDetails(std::ostream& out) const
{
	Employee::printDetails(out);

	out << std::left << std::setw(14) << hourly_wage << designation << std::endl;
}
