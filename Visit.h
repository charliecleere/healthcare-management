#pragma once

#include "Date.h"
#include "Service.h"
#include "Nurse.h"
#include "Aide.h"
#include "InvalidDateException.h"
#include <vector>
#include <iomanip>

class Visit
{
public:
	// Constructor with a default parameter
	Visit(int i = 0, Nurse n = Nurse(), Aide a = Aide());

	// Destructor
	~Visit();

	// Accessor and mutator functions
	int getId() const;
	Date getDate() const;
	Nurse getNurse() const;
	Aide getAide() const;
	void setId(int vid);
	void setDate(int m, int d, int y);
	void setNurse(Nurse n);
	void setAide(Aide a);

	// Other functions
	void addService(Service s);
	void printVisit(std::ostream& out) const;

	void tokenizeDate(const char* c, int& month, int& day, int& year) const;

private:
	int id;
	Date date;
	std::vector<Service> services;
	Nurse nurse;
	Aide aide;
};
