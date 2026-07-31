#include "CaseManager.h"

CaseManager::CaseManager(int i, std::string fn, std::string ln, double s, std::string d) : Employee(i, fn, ln)
{
	setSalary(s);
	setDegree(d);
}

CaseManager::~CaseManager()
{

}

void CaseManager::setSalary(double s)
{
	if (s < 0)
	{
		std::cout << "Invalid salary. Salary cannot be negative. Please try again.";
		salary = -1;
	}
	else
		salary = s;
}

void CaseManager::setDegree(std::string d)
{
	degree = d;
}

double CaseManager::getSalary() const
{
	return salary;
}

std::string CaseManager::getDegree() const
{
	return degree;
}

void CaseManager::printDetails(std::ostream& out) const
{
	Employee::printDetails(out);

	out << std::left << std::setw(14) << salary << degree << std::endl;
}
