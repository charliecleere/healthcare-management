#pragma once

#include <string>
#include <iostream>
#include <iomanip>

class Employee
{
public:
	// Three-argument constructor with default parameters
	Employee(int i = 0, std::string fn = "", std::string ln = "");

	// Copy constructor
	Employee(const Employee& e);

	// Destructor
	~Employee();

	// Overloaded assignment operator
	void operator=(const Employee& e);

	// Accessor and mutator functions
	void setId(int i);
	void setFirstName(std::string fn);
	void setLastName(std::string ln);
	int getId() const;
	std::string getFirstName() const;
	std::string getLastName() const;

	// Other function
	void printDetails(std::ostream& out) const;

private:
	int* id;
	std::string* first_name;
	std::string* last_name;
};