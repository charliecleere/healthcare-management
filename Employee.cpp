#include "Employee.h"

Employee::Employee(int i, std::string fn, std::string ln)
{
	id = new int(i);
	first_name = new std::string(fn);
	last_name = new std::string(ln);
}

// Deep-copy the dynamically allocated identity fields.
Employee::Employee(const Employee& e)
{
	this->id = new int(e.getId());
	this->first_name = new std::string(e.getFirstName());
	this->last_name = new std::string(e.getLastName());
}

// Release the dynamically allocated identity fields.
Employee::~Employee()
{
	delete id;
	id = nullptr;
	delete first_name;
	first_name = nullptr;
	delete last_name;
	last_name = nullptr;
}

// Copy the identity values into already allocated storage.
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
