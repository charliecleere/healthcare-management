#pragma once

#include <string>
#include "Date.h"
#include "InvalidDateException.h"

class Equipment
{
public:
	// Stores the equipment identity, purchase information, and depreciation inputs.
	Equipment(int i = 0, std::string n = "", double oc = 0.0, int ul = 0, double sv = 0.0);

	virtual ~Equipment();

	// Accessors and mutators for the equipment record.
	int getId() const;
	std::string getName() const;
	Date getPurchaseDate() const;
	double getOriginalCost() const;
	int getUsefulLife() const;
	double getSalvageValue() const;
	void setId(int i);
	void setName(std::string n);
	void setPurchaseDate(int m, int d, int y);
	void setOriginalCost(double oc);
	void setUsefulLife(int ul);
	void setSalvageValue(double sv);

	void tokenizeDate(const char* c, int& month, int& day, int& year);

	int calculateCenteredTextX(const std::string& s) const;

	// Writes the derived equipment type's depreciation schedule.
	virtual void depreciate(std::ostream& out) const = 0;

	// Writes the derived equipment type's display fields.
	virtual void printDetails(std::ostream& out) const = 0;

	// Orders equipment by ID for sorted reports and inventories.
	bool operator<(const Equipment& other) const; 
private:
	int id;
	std::string name;
	Date purchase_date;
	double original_cost;
	int useful_life;
	double salvage_value;
};
