#pragma once

#include "Equipment.h"

class MonitorEquipment : public Equipment
{
public:
	// Constructor with default parameters
	MonitorEquipment(int i = 0, std::string n = "", double oc = 0.0, int ul = 0, double sv = 0.0, std::string dt = "");

	// Destructor
	~MonitorEquipment();

	// Accessor and mutator functions
	void setDisplayType(std::string dt);
	std::string getDisplayType() const;
	
	// Override the pure virtual function to calculate depreciation
	void depreciation(std::ostream& out);

	// Override the virtual function to print equipment details
	void printDetails(std::ostream& out) const;
private:
	std::string display_type;

	// Utility function that is only to be called from the depreciation() function
	void produceDepreciationSchedule(std::ostream& out, int id, std::string name, Date purchase_date, double original_cost, int useful_life, double salvage_value);

	// Utility function that is only to be called from the produceDepreciationSchedule() function
	void straightLineDepreciation(std::ostream& out, double original_cost, double book_value, double salvage_value, int useful_life, int period_number, double& total_depreciation);
};