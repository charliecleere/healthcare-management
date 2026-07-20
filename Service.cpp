#include "Service.h"

// Constructor with default parameters
Service::Service(int i, std::string n)
{
	setId(i);
	setName(n);
}

// Destructor
Service::~Service()
{

}

// Accessor and mutator functions
int Service::getId() const
{
	return id;
}

std::string Service::getName() const
{
	return name;
}

void Service::setId(int i)
{
	if (i < 0)
	{
		std::cout << "Invalid ID. ID cannot be negative. Please try again." << std::endl;
		id = -1;
	}
	else
		id = i;
}

void Service::setName(std::string n)
{
	name = n;
}