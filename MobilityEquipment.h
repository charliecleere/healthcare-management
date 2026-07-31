#pragma once

#include "Equipment.h"

class MobilityEquipment : public Equipment
{
public:
	// Stores mobility-specific operating information in addition to the base record.
	MobilityEquipment(int i = 0, std::string n = "", double oc = 0.0, int ul = 0, double sv = 0.0, std::string om = "");

	~MobilityEquipment();

	// Accessors and mutators for the operating mode.
	void setOperationMode(std::string om);
	std::string getOperationMode() const;

	// Writes the mobility equipment's double-declining-balance schedule.
	void depreciate(std::ostream& out) const override;

	// Writes the mobility equipment's details in the shared report format.
	void printDetails(std::ostream& out) const;
private:
	std::string operation_mode;

	// Recursively formats the complete double-declining-balance schedule.
	void produceDepreciationSchedule(std::ostream& out, int equipment_id, const std::string& equipment_name, double original_cost_value, int useful_life_value, double salvage_value_value) const;
		
	// Recursively calculates one period while respecting the salvage-value floor.
	void doubleDecliningBalanceDepreciation(std::ostream& out, double book_value, double salvage_value_value, int useful_life_value, int period_number, double& total_depreciation_value) const;
};
