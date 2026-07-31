#pragma once

#include <string>
#include <iostream>
#include <iomanip>

class Employee
{
public:
	// Initializes the employee identity using explicitly managed storage.
	Employee(int i = 0, std::string fn = "", std::string ln = "");

	// Performs a deep copy of the dynamically allocated identity fields.
	Employee(const Employee& e);

	// Releases the dynamically allocated identity fields.
	~Employee();

	// Replaces this employee with a deep copy of another employee.
	void operator=(const Employee& e);

	// Accessors and mutators for the employee identity.
	void setId(int i);
	void setFirstName(std::string fn);
	void setLastName(std::string ln);
	int getId() const;
	std::string getFirstName() const;
	std::string getLastName() const;

	// Writes the shared employee details.
	void printDetails(std::ostream& out) const;

private:
	int* id;
	std::string* first_name;
	std::string* last_name;
};
