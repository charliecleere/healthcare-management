#pragma once

#include "Equipment.h"

class MobilityEquipment : public Equipment
{
public:
	// Constructor with default parameters
	MobilityEquipment(int i = 0, std::string n = "", double oc = 0.0, int ul = 0, double sv = 0.0, std::string om = "");

	// Destructor
	~MobilityEquipment();

	// Accessor and mutator functions
	void setOperationMode(std::string om);
	std::string getOperationMode() const;

	// Override the pure virtual function to calculate depreciation
	void depreciate(std::ostream& out) const override;

	// Override the virtual function to print equipment details
	void printDetails(std::ostream& out) const;
private:
	std::string operation_mode;

	// Utility function that is only to be called from the depreciation() function
	void produceDepreciationSchedule(std::ostream& out, int equipment_id, const std::string& equipment_name, double original_cost_value, int useful_life_value, double salvage_value_value) const;
		
	// Utility function that is only to be called from the produceDepreciationSchedule() function
	void doubleDecliningBalanceDepreciation(std::ostream& out, double book_value, double salvage_value_value, int useful_life_value, int period_number, double& total_depreciation_value) const;
};
