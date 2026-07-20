#include "Employee.h"

// Three-argument constructor with default parameters
Employee::Employee(int i, std::string fn, std::string ln)
{
	id = new int(i);
	first_name = new std::string(fn);
	last_name = new std::string(ln);
}

// Copy constructor
Employee::Employee(const Employee& e)
{
	this->id = new int(e.getId());
	this->first_name = new std::string(e.getFirstName());
	this->last_name = new std::string(e.getLastName());
}

// Destructor
Employee::~Employee()
{
	delete id;
	id = nullptr;
	delete first_name;
	first_name = nullptr;
	delete last_name;
	last_name = nullptr;
}

// Overloaded assignment operator
void Employee::operator=(const Employee& e)
{
	this->setId(e.getId());
	this->setFirstName(e.getFirstName());
	this->setLastName(e.getLastName());
}

void Employee::setId(int i)
{
	if (i < 0)
	{
		std::cout << "Invalid ID. ID cannot be negative. Please try again." << std::endl;
		*id = -1;
	}
	else
		*id = i;
}

void Employee::setFirstName(std::string fn)
{
	*first_name = fn;
}

void Employee::setLastName(std::string ln)
{
	*last_name = ln;
}

int Employee::getId() const
{
	return *id;
}

std::string Employee::getFirstName() const
{
	return *first_name;
}

std::string Employee::getLastName() const
{
	return *last_name;
}

void Employee::printDetails(std::ostream& out) const
{
	out << std::left << std::setw(5) << *id << std::setw(23) << *first_name + " " + *last_name;
}