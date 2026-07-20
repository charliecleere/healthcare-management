#pragma once

#include <string>
#include "Date.h"
#include "InvalidDateException.h"

class Equipment
{
public:
	// Constructor with default parameters
	Equipment(int i = 0, std::string n = "", double oc = 0.0, int ul = 0, double sv = 0.0);

	// Destructor
	virtual ~Equipment();

	// Accessor and mutator functions
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

	void tokenizeDate(char* c, int& month, int& day, int& year);

	int calculateCenteredTextX(std::string s) const;

	// Pure virtual function to calculate depreciation, making Equipment an abstract class
	virtual void depreciation(std::ostream& out) = 0; 

	// Pure virtual function to print equipment details, can be overridden by derived classes
	virtual void printDetails(std::ostream& out) const = 0;

	// Overloaded less-than operator to compare equipment by equipment ID for sorting
	bool operator<(const Equipment& other) const; 
private:
	int id;
	std::string name;
	Date purchase_date;
	double original_cost;
	int useful_life;  // In years
	double salvage_value;
};