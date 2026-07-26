#include "MonitorEquipment.h"

#include <iomanip>

MonitorEquipment::MonitorEquipment(int i, std::string n, double oc, int ul, double sv, std::string dt)
	: Equipment(i, n, oc, ul, sv), display_type(dt)
{
}

MonitorEquipment::~MonitorEquipment()
{
}

void MonitorEquipment::setDisplayType(std::string dt)
{
	display_type = dt;
}

std::string MonitorEquipment::getDisplayType() const
{
	return display_type;
}

void MonitorEquipment::depreciate(std::ostream& out) const
{
	produceDepreciationSchedule(out, getId(), getName(), getOriginalCost(), getUsefulLife(), getSalvageValue());
}

void MonitorEquipment::printDetails(std::ostream& out) const
{
	out << std::left << std::setw(5) << getId() << std::setw(25) << getName() << std::setw(15) << getPurchaseDate()
		<< std::setw(15) << getOriginalCost() << std::setw(14) << getUsefulLife() << std::setw(15) << getSalvageValue()
		<< getDisplayType() << std::endl;
}

void MonitorEquipment::produceDepreciationSchedule(std::ostream& out, int equipment_id, const std::string& equipment_name,
	double original_cost_value, int useful_life_value, double salvage_value_value) const
{
	double total_depreciation_value = 0.0;

	out << std::fixed << std::setprecision(2);
	out << std::setw(calculateCenteredTextX("Straight-Line Depreciation")) << std::right << "Straight-Line Depreciation" << std::endl;
	out << std::setw(21) << "" << std::setw(25) << std::left << "Equipment ID: " << std::right << std::setw(12) << equipment_id << std::endl;
	out << std::setw(21) << "" << std::setw(25) << std::left << "Equipment name: " << std::right << std::setw(12) << equipment_name << std::endl;
	out << std::setw(21) << "" << std::setw(25) << std::left << "Original cost ($): " << std::right << std::setw(12) << original_cost_value << std::endl;
	out << std::setw(21) << "" << std::setw(25) << std::left << "Salvage value ($): " << std::right << std::setw(12) << salvage_value_value << std::endl;
	out << std::setw(21) << "" << std::setw(25) << std::left << "Useful life (in years): " << std::right << std::setw(12) << useful_life_value << std::endl << std::endl;
	out << std::setw(20) << std::right << "Period" << std::setw(28) << "Depreciation Expense ($)" << std::setw(18) << "Book Value ($)" << std::endl;
	out << std::setw(66) << std::right << original_cost_value << std::endl;

	straightLineDepreciation(out, original_cost_value, original_cost_value, salvage_value_value, useful_life_value, 1, total_depreciation_value);

	out << std::endl << " Total Depreciation: " << std::setw(27) << std::right << total_depreciation_value << std::endl << std::endl;
	out << std::setfill('-') << std::setw(80) << "" << std::setfill(' ') << std::endl;
	out << std::setw(calculateCenteredTextX("End of Report")) << std::right << "End of Report" << std::endl;
	out << std::setfill('-') << std::setw(80) << "" << std::setfill(' ') << std::endl;
}

void MonitorEquipment::straightLineDepreciation(std::ostream& out, double original_cost_value, double book_value,
	double salvage_value_value, int useful_life_value, int period_number, double& total_depreciation_value) const
{
	double depreciation_expense = (original_cost_value - salvage_value_value) / useful_life_value;
	double next_book_value = book_value - depreciation_expense;

	if (next_book_value < salvage_value_value || period_number >= useful_life_value)
	{
		depreciation_expense = book_value - salvage_value_value;
		next_book_value = salvage_value_value;
	}

	out << std::setw(20) << std::right << period_number << std::setw(28) << depreciation_expense << std::setw(18) << next_book_value << std::endl;
	total_depreciation_value += depreciation_expense;

	if (period_number < useful_life_value && next_book_value > salvage_value_value)
		straightLineDepreciation(out, original_cost_value, next_book_value, salvage_value_value, useful_life_value, period_number + 1, total_depreciation_value);
}
