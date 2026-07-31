#include "Equipment.h"

#include <cctype>
#include <cstring>

const int SCREEN_WIDTH = 64;

Equipment::Equipment(int i, std::string n, double oc, int ul, double sv)
{
	setId(i);
	setName(n);
	setOriginalCost(oc);
	setUsefulLife(ul);
	setSalvageValue(sv);
}

Equipment::~Equipment()
{

}

int Equipment::getId() const
{
	return id;
}

std::string Equipment::getName() const
{
	return name;
}

Date Equipment::getPurchaseDate() const
{
	return purchase_date;
}

double Equipment::getOriginalCost() const
{
	return original_cost;
}

int Equipment::getUsefulLife() const
{
	return useful_life;
}

double Equipment::getSalvageValue() const
{
	return salvage_value;
}

void Equipment::setId(int i)
{
	if (i < 0)
	{
		std::cout << "Invalid ID. ID cannot be negative. Please try again." << std::endl;
		id = -1;
	}
	else
		id = i;
}

void Equipment::setName(std::string n)
{
	name = n;
}

void Equipment::setPurchaseDate(int m, int d, int y)
{
	purchase_date.setDate(m, d, y);
}

void Equipment::setOriginalCost(double oc)
{
	original_cost = oc;
	
	if (oc < 0)
	{
		std::cout << "Invalid original cost. Original cost cannot be negative. Please try again.";
		original_cost = -1;
	}
	else
		original_cost = oc;
}

void Equipment::setUsefulLife(int ul)
{
	useful_life = ul;
	if (ul < 0)
	{
		std::cout << "Invalid useful life. Useful life cannot be negative. Please try again.";
		useful_life = -1;
	}
	else
		useful_life = ul;
}

void Equipment::setSalvageValue(double sv)
{
	salvage_value = sv;
	if (sv < 0)
	{
		std::cout << "Invalid salvage value. Salvage value cannot be negative. Please try again.";
		salvage_value = -1;
	}
	else
		salvage_value = sv;
}
// Parses m/d/yyyy or mm/dd/yyyy and validates the calendar date.
void Equipment::tokenizeDate(const char* dateStr, int& month, int& day, int& year)
{
	if (dateStr == nullptr || std::strlen(dateStr) == 0) throw InvalidDateException();
	const std::size_t len = std::strlen(dateStr);
	if (len < 8 || len > 10) throw InvalidDateException();

	std::size_t i{ 0 };
	int digitCount{ 0 };

	month = 0;
	while (dateStr[i] != '/' && dateStr[i] != '\0') {
		if (!isdigit(dateStr[i])) throw InvalidDateException();
		month = month * 10 + (dateStr[i] - '0');
		i++;
	}
	if (dateStr[i] != '/') throw InvalidDateException();
	i++;

	day = 0;
	while (dateStr[i] != '/' && dateStr[i] != '\0') {
		if (!isdigit(dateStr[i])) throw InvalidDateException();
		day = day * 10 + (dateStr[i] - '0');
		i++;
	}
	if (dateStr[i] != '/') throw InvalidDateException();
	i++;

	year = 0, digitCount = 0;
	while (dateStr[i] != '\0') {
		if (!isdigit(dateStr[i])) throw InvalidDateException();
		year = year * 10 + (dateStr[i] - '0');
		digitCount++;
		i++;
	}
	if (digitCount != 4) throw InvalidDateException();

	if (month < 1 || month > 12) throw InvalidDateException();

	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// February has 29 days in a leap year.
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		daysInMonth[1] = 29;
	}

	if (day < 1 || day > daysInMonth[month - 1]) throw InvalidDateException();
}

int Equipment::calculateCenteredTextX(const std::string& s) const
{
	return SCREEN_WIDTH / 2 + static_cast<int>(s.size()) / 2;
}

// Orders equipment by ID for reports and storage-unit inventories.
bool Equipment::operator<(const Equipment& other) const
{
	if (this->getId() < other.getId())
		return true;
	else
		return false;
}
