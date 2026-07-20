#pragma once

#include <string>
#include <iostream>

class Service
{
public:
	// Two-argument constructor with default parameters
	Service(int i = 0, std::string n = "");

	// Destructor
	~Service();

	// Accessor and mutator functions
	int getId() const;
	std::string getName() const;
	void setId(int i);
	void setName(std::string n);

private:
	int id;
	std::string name;
};