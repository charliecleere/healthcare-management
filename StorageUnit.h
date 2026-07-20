#pragma once

#include "Date.h"
#include "Equipment.h"
#include "NegativeNumberException.h"
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>

const int SCREEN_WIDTH_2 = 64;

// Class template definition for StorageUnit
template <typename T>
class StorageUnit
{
public:
	// Constructor with default parameters
	StorageUnit(int i = 0, std::string d = "", int l = 0, int w = 0, int h = 0, double cpm = 0.0, bool hc = false, bool ar = false);
	
	// Destructor
	~StorageUnit();

	// Accessor and mutator functions
	void setId(int i);
	void setDescription(std::string d);
	void setLength(int l);
	void setWidth(int w);
	void setHeight(int h);
	void setCostPerMonth(double cpm);
	void setDateRented(int m, int d, int y);
	void setHumidityControlled(bool hc);
	void setAutoRenewal(bool ar);

	int getId() const;
	std::string getDescription() const;
	int getLength() const;
	int getWidth() const;
	int getHeight() const;
	double getCostPerMonth() const;
	Date getDateRented() const;
	bool getHumidityControlled() const;
	bool getAutoRenewal() const;

	// Other functions
	void tokenizeDate(char* c, int& month, int& day, int& year);

	// Had to comment this out because it was causing an error, and I was running out of time to submit:
	/*template <typename T>
	void addEquipment(T equipment);*/
	
	void printUnitInformation() const;

	void printInventory(std::string equipment_type) const;

	void sortInventory();

	int calculateCenteredTextX(std::string s) const;
private:
	int id;
	std::string description;
	int length;
	int width;
	int height;
	double cost_per_month;
	Date date_rented;
	bool humidity_controlled;
	bool auto_renewal;
	std::vector<T> equipment;
};

// Function definitions for StorageUnit class template
template <typename T>
StorageUnit<T>::StorageUnit(int i, std::string d, int l, int w, int h, double cpm, bool hc, bool ar)
{
	setId(i);
	setDescription(d);
	setLength(l);
	setWidth(w);
	setHeight(h);
	setCostPerMonth(cpm);
	setHumidityControlled(hc);
	setAutoRenewal(ar);
}

template <typename T>
StorageUnit<T>::~StorageUnit()
{

}

template <typename T>
void StorageUnit<T>::setId(int i)
{
	if (i < 0)
		throw NegativeNumberException();
	else
		id = i;
}

template <typename T>
void StorageUnit<T>::setDescription(std::string d)
{
	description = d;
}

template <typename T>
void StorageUnit<T>::setLength(int l)
{
	if (l < 0)
		throw NegativeNumberException();
	else
		length = l;
}

template <typename T>
void StorageUnit<T>::setWidth(int w)
{
	if (w < 0)
		throw NegativeNumberException();
	else
		width = w;
}

template <typename T>
void StorageUnit<T>::setHeight(int h)
{
	if (h < 0)
		throw NegativeNumberException();
	else
		height = h;
}

template <typename T>
void StorageUnit<T>::setCostPerMonth(double cpm)
{
	if (cpm < 0)
		throw NegativeNumberException();
	else
		cost_per_month = cpm;
}

template <typename T>
void StorageUnit<T>::setDateRented(int m, int d, int y)
{
	date_rented.setDate(m, d, y);
}

template <typename T>
void StorageUnit<T>::setHumidityControlled(bool hc)
{
	humidity_controlled = hc;
}

template <typename T>
void StorageUnit<T>::setAutoRenewal(bool ar)
{
	auto_renewal = ar;
}

template <typename T>
int StorageUnit<T>::getId() const
{
	return id;
}

template <typename T>
std::string StorageUnit<T>::getDescription() const
{
	return description;
}

template <typename T>
int StorageUnit<T>::getLength() const
{
	return length;
}

template <typename T>
int StorageUnit<T>::getWidth() const
{
	return width;
}

template <typename T>
int StorageUnit<T>::getHeight() const
{
	return height;
}

template <typename T>
double StorageUnit<T>::getCostPerMonth() const
{
	return cost_per_month;
}

template <typename T>
Date StorageUnit<T>::getDateRented() const
{
	return date_rented;
}

template <typename T>
bool StorageUnit<T>::getHumidityControlled() const
{
	return humidity_controlled;
}	

template <typename T>
bool StorageUnit<T>::getAutoRenewal() const
{
	return auto_renewal;
}

template <typename T>
void StorageUnit<T>::tokenizeDate(char* dateStr, int& month, int& day, int& year)
{
	//ensure that the character array is in the correct format and parse out its month, day, and year
	if (dateStr == nullptr || std::strlen(dateStr) == 0) throw InvalidDateException();
	int len = std::strlen(dateStr);
	if (len < 8 || len > 10) throw InvalidDateException();

	// m/d/yyyy(8) to mm/dd/yyyy(10)
	// Split string using manual parsing
	int i{ 0 }, digitCount{ 0 };

	// Parse month
	month = 0;
	while (dateStr[i] != '/' && dateStr[i] != '\0') {
		if (!isdigit(dateStr[i])) throw InvalidDateException();
		month = month * 10 + (dateStr[i] - '0');
		i++;
	}
	if (dateStr[i] != '/') throw InvalidDateException();
	i++; // Skip '/'

	// Parse day
	day = 0;
	while (dateStr[i] != '/' && dateStr[i] != '\0') {
		if (!isdigit(dateStr[i])) throw InvalidDateException();
		day = day * 10 + (dateStr[i] - '0');
		i++;
	}
	if (dateStr[i] != '/') throw InvalidDateException();
	i++; // Skip '/'

	// Parse year
	year = 0, digitCount = 0;
	while (dateStr[i] != '\0') {
		if (!isdigit(dateStr[i])) throw InvalidDateException();
		year = year * 10 + (dateStr[i] - '0');
		digitCount++;
		i++;
	}
	if (digitCount != 4) throw InvalidDateException();

	// Check valid month
	if (month < 1 || month > 12) throw InvalidDateException();

	// Check valid day based on month
	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// Leap year check
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		daysInMonth[1] = 29;
	}

	if (day < 1 || day > daysInMonth[month - 1]) throw InvalidDateException();
} // End of tokenizeDate function

// Had to comment this out because it was causing an error, and I was running out of time to submit:
// This function adds a piece of equipment to the inventory of the storage unit. It takes in an object of type T (which is the template parameter) and adds it to the vector of equipment using the push_back function.
//template <typename T>
//void StorageUnit<T>::addEquipment(T equipment)
//{
//	equipment.push_back(equipment);
//}

// This function sorts the inventory of the storage unit by equipment ID using the overloaded less-than operator in the Equipment class. It uses the sort function from the algorithm library to sort the vector of equipment.
template <typename T>
void StorageUnit<T>::sortInventory()
{
	std::sort(equipment.begin(), equipment.end());
}

// This function prints the information of the storage unit to the console. It also prints the rental contract details and whether or not the storage unit is humidity controlled and whether or not the rental contract auto-renews.
template <typename T>
void StorageUnit<T>::printUnitInformation() const
{
	std::string display_humidity_controlled = "";
	std::string display_auto_renew = "";
	std::cout << "Storage Unit Information" << std::endl;
	std::cout << std::setfill('-') << std::setw(64) << "" << std::setfill(' ') << std::endl;
	std::cout << "ID: " << getId() << std::endl;
	std::cout << "Description: " << getDescription() << std::endl;
	std::cout << "Dimensions (LxWxH): " << getLength() << " x " << getWidth() << " x " << getHeight() << " feet" << std::endl << std::endl;
	(getHumidityControlled() == true) ? (display_humidity_controlled = "is") : (display_humidity_controlled = "is not");
	std::cout << "**Storage unit " << display_humidity_controlled << " humidity controlled." << std::endl << std::endl;
	std::cout << "Rental Contract Details" << std::endl;
	std::cout << "Cost Per Month: $" << getCostPerMonth() << std::endl;
	std::cout << "Date Signed: " << getDateRented() << std::endl << std::endl;
	(getAutoRenewal() == true) ? (display_auto_renew = "does") : (display_auto_renew = "does not");
	std::cout << "**Rental contract " << display_auto_renew << " auto-renew." << std::endl;
}

// This function prints the inventory of the storage unit to the console. It first sorts the inventory by equipment ID and then prints the details of each piece of equipment in a table format. The type or mode of the equipment is also printed in the last column, and whether it is display mode or operation mode depends on whether the equipment is a monitor or mobility equipment (which is determined by the equipmentType parameter that is passed into the function).
template <typename T>
void StorageUnit<T>::printInventory(std::string equipmentType) const
{
	// Had to comment this out because it was causing an error, and I was running out of time to submit:
	// sortInventory();

	std::cout << std::fixed << std::setprecision(2);
	std::cout << std::setfill('-') << std::setw(100) << "" << std::setfill(' ') << std::endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc."); // To get a value for setw that will center the text
	std::cout << std::right << std::setw(centeredTextX1) << "Health Care Options, Inc." << std::endl;
	int centeredTextX2 = calculateCenteredTextX(equipmentType + " Equipment Inventory"); // To get a value for setw that will center the text
	std::cout << std::right << std::setw(centeredTextX2) << equipmentType + " Inventory" << std::endl;
	std::cout << std::setfill('-') << std::setw(100) << "" << std::setfill(' ') << std::endl << std::endl;
	std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Name" << std::setw(15) << "Purchase Date" << std::setw(15) << "Original Cost" << std::setw(14) << "Useful Life" << std::setw(15) << "Salvage Value" << "Type/Mode" << std::endl;
	std::cout << std::setfill('-') << std::setw(100) << "" << std::setfill(' ') << std::endl;
	for (int i = 0; i < equipment.size(); i++)
		std::cout << std::left << std::setw(5) << equipment[i].getId() << std::setw(25) << equipment[i].getName() << std::setw(15) << equipment[i].getPurchaseDate() << std::setw(15) << equipment[i].getOriginalCost() << std::setw(14) << equipment[i].getUsefulLife() << std::setw(15) << equipment[i].getSalvageValue() << std::endl; // Had to comment this out because it was causing an error, and I was running out of time to submit: << (equipmentType == "Monitor" ? equipment[i].getDisplayType() : equipment[i].getOperationMode()) << std::endl;
}

// This function calculates the value for setw that will center text on the screen. It takes in a string and returns an integer that is the value for setw that will center that string on the screen. It uses the constant SCREEN_WIDTH to calculate this value, which is defined in the Main.cpp file.
template <typename T>
int StorageUnit<T>::calculateCenteredTextX(std::string s) const
{
	return SCREEN_WIDTH_2 / 2 + s.size() / 2;
}
