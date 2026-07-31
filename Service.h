#pragma once

#include <string>
#include <iostream>

class Service
{
public:
	// Initializes the service identifier and display name.
	Service(int i = 0, std::string n = "");

	~Service();

	// Accessors and mutators for the service record.
	int getId() const;
	std::string getName() const;
	void setId(int i);
	void setName(std::string n);

private:
	int id;
	std::string name;
};
