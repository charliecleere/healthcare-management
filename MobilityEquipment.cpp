#include "MobilityEquipment.h"
#include <iomanip>

MobilityEquipment::MobilityEquipment(int i, std::string n, double oc, int ul, double sv, std::string om) : Equipment(i, n, oc, ul, sv)
{
	operation_mode = om;
}

MobilityEquipment::~MobilityEquipment()
{

}

void MobilityEquipment::setOperationMode(std::string om)
{
	operation_mode = om;
}

std::string MobilityEquipment::getOperationMode() const
{
	return operation_mode;
}

void MobilityEquipment::depreciation(std::ostream& out)
{
	int id = getId();
	std::string name = getName();
	Date purchase_date = getPurchaseDate();
	double original_cost = getOriginalCost();
	int useful_life = getUsefulLife();
	double salvage_value = getSalvageValue();
	
	produceDepreciationSchedule(out, id, name, purchase_date, original_cost, useful_life, salvage_value);
}

void MobilityEquipment::printDetails(std::ostream& out) const
{
	out << std::left << std::setw(5) << getId() << std::setw(25) << getName() << std::setw(15) << getPurchaseDate() << std::setw(15) << getOriginalCost() << std::setw(14) << getUsefulLife() << std::setw(15) << getSalvageValue() << getOperationMode() << std::endl;
}

void MobilityEquipment::produceDepreciationSchedule(std::ostream& out, int id, std::string name, Date purchase_date, double original_cost, int useful_life, double salvage_value)
{
	double total_depreciation = 0.0;

	// printHeader(out);

	// Echo of user inputs
	out << std::fixed << std::setprecision(2);
	int centeredTextX1 = calculateCenteredTextX("Double-Declining Balance Depreciation"); // To get a value for setw that will center the text
	out << std::setw(centeredTextX1) << std::right << "Double-Declining Balance Depreciation" << std::endl;
	out << std::setw(21) << "" << std::setw(25) << std::left << "Equipment ID: " << std::right << std::setw(12) << id << std::endl;
	out << std::setw(21) << "" << std::setw(25) << std::left << "Equipment name: " << std::right << std::setw(12) << name << std::endl;
	out << std::setw(21) << "" << std::setw(25) << std::left << "Original cost ($): " << std::right << std::setw(12) << original_cost << std::endl;
	out << std::setw(21) << "" << std::setw(25) << std::left << "Salvage value ($): " << std::right << std::setw(12) << salvage_value << std::endl;
	out << std::setw(21) << "" << std::setw(25) << std::left << "Useful life (in years): " << std::right << std::setw(12) << useful_life << std::endl << std::endl;

	// Column headers
	out << std::setw(20) << std::right << "Period" << std::setw(28) << "Depreciation Expense ($)" << std::setw(18) << "Book Value ($)" << std::endl;

	// Print original cost for the first book value
	out << std::setw(66) << std::right << original_cost << std::endl;

	// Call double declining balance depreciation function
	doubleDecliningBalanceDepreciation(out, original_cost, salvage_value, useful_life, 1, total_depreciation);

	// Total depreciation
	out << std::endl << " Total Depreciation: " << std::setw(27) << std::right << total_depreciation << std::endl << std::endl;

	// Footer
	out << std::setfill('-') << std::setw(80) << "" << std::setfill(' ') << std::endl;
	int centeredTextX2 = calculateCenteredTextX("End of Report"); // To get a value for setw that will center the text
	out << std::setw(centeredTextX2) << std::right << "End of Report" << std::endl;
	out << std::setfill('-') << std::setw(80) << "" << std::setfill(' ') << std::endl;
	
}

void MobilityEquipment::doubleDecliningBalanceDepreciation(std::ostream& out, double book_value, double salvage_value, int useful_life, int period_number, double& total_depreciation)
{
	double depreciation_expense;
	double next_book_value;

	depreciation_expense = ((static_cast<double>(1) / useful_life) * 2) * book_value;

	next_book_value = book_value - depreciation_expense;

	if (next_book_value < salvage_value) {
		depreciation_expense -= (salvage_value - next_book_value);
		next_book_value = (salvage_value - next_book_value) + next_book_value;

		out << std::setw(20) << std::right << period_number << std::setw(28) << depreciation_expense << std::setw(18) << next_book_value << std::endl;

		total_depreciation += depreciation_expense;
	}
	else if (next_book_value == salvage_value) {
		out << std::setw(20) << std::right << period_number << std::setw(28) << depreciation_expense << std::setw(18) << next_book_value << std::endl;

		total_depreciation += depreciation_expense;
	}
	else if (period_number >= useful_life) {
		depreciation_expense = book_value - salvage_value;
		next_book_value = book_value - depreciation_expense;

		out << std::setw(20) << std::right << period_number << std::setw(28) << depreciation_expense << std::setw(18) << next_book_value << std::endl;

		total_depreciation += depreciation_expense;
	}
	else {
		out << std::setw(20) << std::right << period_number << std::setw(28) << depreciation_expense << std::setw(18) << next_book_value << std::endl;

		total_depreciation += depreciation_expense;

		doubleDecliningBalanceDepreciation(out, next_book_value, salvage_value, useful_life, period_number + 1, total_depreciation);
	}
}

