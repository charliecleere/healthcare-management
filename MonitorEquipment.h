#pragma once

#include "Equipment.h"

class MonitorEquipment : public Equipment
{
public:
	// Stores monitor-specific display information in addition to the base record.
	MonitorEquipment(int i = 0, std::string n = "", double oc = 0.0, int ul = 0, double sv = 0.0, std::string dt = "");

	~MonitorEquipment();

	// Accessors and mutators for the display type.
	void setDisplayType(std::string dt);
	std::string getDisplayType() const;
	
	// Writes the monitor's straight-line depreciation schedule.
	void depreciate(std::ostream& out) const override;

	// Writes the monitor's details in the shared equipment-report format.
	void printDetails(std::ostream& out) const;
private:
	std::string display_type;

	// Recursively formats the complete straight-line depreciation schedule.
	void produceDepreciationSchedule(std::ostream& out, int equipment_id, const std::string& equipment_name, double original_cost_value, int useful_life_value, double salvage_value_value) const;

	// Recursively calculates one period of straight-line depreciation.
	void straightLineDepreciation(std::ostream& out, double original_cost_value, double book_value, double salvage_value_value, int useful_life_value, int period_number, double& total_depreciation_value) const;
};
