#include "Aide.h"

// Five-argument constuctor with default parameters
Aide::Aide(int i, std::string fn, std::string ln, double hw, std::string c) : Employee(i, fn, ln)
{
	setHourlyWage(hw);
	setCertification(c);
}

// Destructor
Aide::~Aide()
{

}

// Accessor and Mutators
void Aide::setHourlyWage(double hw)
{
	if (hw < 0)
	{
		std::cout << "Invalid hourly wage. Hourly wage cannot be negative. Please try again.";
		hourly_wage = -1;
	}
	else
		hourly_wage = hw;
}

void Aide::setCertification(std::string c)
{
	certification = c;
}

double Aide::getHourlyWage() const
{
	return hourly_wage;
}

std::string Aide::getCertification() const
{
	return certification;
}

void Aide::printDetails(std::ostream& out) const
{
	Employee::printDetails(out);

	out << std::left << std::setw(14) << hourly_wage << certification << std::endl;
}