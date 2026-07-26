#pragma once

#include "Date.h"
#include "Equipment.h"
#include "InvalidDateException.h"
#include "NegativeNumberException.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

constexpr int STORAGE_UNIT_SCREEN_WIDTH = 64;

// A storage unit holds one concrete equipment type while sharing the same
// rental and inventory behavior with every other unit.
template <typename T>
class StorageUnit
{
public:
	StorageUnit(int i = 0, std::string d = "", int l = 0, int w = 0, int h = 0,
		double cpm = 0.0, bool hc = false, bool ar = false);
	~StorageUnit() = default;

	void setId(int i);
	void setDescription(const std::string& d);
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

	void tokenizeDate(const char* dateStr, int& month, int& day, int& year) const;
	void addEquipment(const T& item);
	bool containsEquipmentId(int equipmentId) const;
	std::size_t getInventorySize() const;
	void sortInventory();
	void printUnitInformation() const;
	void printInventory(const std::string& equipmentType) const;

private:
	int calculateCenteredTextX(const std::string& text) const;

	int id{};
	std::string description;
	int length{};
	int width{};
	int height{};
	double costPerMonth{};
	Date dateRented;
	bool humidityControlled{};
	bool autoRenewal{};
	std::vector<T> inventory;
};

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
void StorageUnit<T>::setId(int i)
{
	if (i < 0)
		throw NegativeNumberException();
	id = i;
}

template <typename T>
void StorageUnit<T>::setDescription(const std::string& d)
{
	description = d;
}

template <typename T>
void StorageUnit<T>::setLength(int l)
{
	if (l < 0)
		throw NegativeNumberException();
	length = l;
}

template <typename T>
void StorageUnit<T>::setWidth(int w)
{
	if (w < 0)
		throw NegativeNumberException();
	width = w;
}

template <typename T>
void StorageUnit<T>::setHeight(int h)
{
	if (h < 0)
		throw NegativeNumberException();
	height = h;
}

template <typename T>
void StorageUnit<T>::setCostPerMonth(double cpm)
{
	if (cpm < 0)
		throw NegativeNumberException();
	costPerMonth = cpm;
}

template <typename T>
void StorageUnit<T>::setDateRented(int m, int d, int y)
{
	dateRented.setDate(m, d, y);
}

template <typename T>
void StorageUnit<T>::setHumidityControlled(bool hc)
{
	humidityControlled = hc;
}

template <typename T>
void StorageUnit<T>::setAutoRenewal(bool ar)
{
	autoRenewal = ar;
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
	return costPerMonth;
}

template <typename T>
Date StorageUnit<T>::getDateRented() const
{
	return dateRented;
}

template <typename T>
bool StorageUnit<T>::getHumidityControlled() const
{
	return humidityControlled;
}

template <typename T>
bool StorageUnit<T>::getAutoRenewal() const
{
	return autoRenewal;
}

template <typename T>
void StorageUnit<T>::tokenizeDate(const char* dateStr, int& month, int& day, int& year) const
{
	if (dateStr == nullptr || std::strlen(dateStr) == 0)
		throw InvalidDateException();

	const std::size_t lengthOfDate = std::strlen(dateStr);
	if (lengthOfDate < 8 || lengthOfDate > 10)
		throw InvalidDateException();

	std::size_t index = 0;
	month = 0;
	while (dateStr[index] != '/' && dateStr[index] != '\0')
	{
		if (!std::isdigit(static_cast<unsigned char>(dateStr[index])))
			throw InvalidDateException();
		month = month * 10 + (dateStr[index++] - '0');
	}
	if (dateStr[index] != '/')
		throw InvalidDateException();

	++index;
	day = 0;
	while (dateStr[index] != '/' && dateStr[index] != '\0')
	{
		if (!std::isdigit(static_cast<unsigned char>(dateStr[index])))
			throw InvalidDateException();
		day = day * 10 + (dateStr[index++] - '0');
	}
	if (dateStr[index] != '/')
		throw InvalidDateException();

	++index;
	year = 0;
	int digitCount = 0;
	while (dateStr[index] != '\0')
	{
		if (!std::isdigit(static_cast<unsigned char>(dateStr[index])))
			throw InvalidDateException();
		year = year * 10 + (dateStr[index++] - '0');
		++digitCount;
	}

	if (digitCount != 4 || month < 1 || month > 12)
		throw InvalidDateException();

	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		daysInMonth[1] = 29;

	if (day < 1 || day > daysInMonth[month - 1])
		throw InvalidDateException();
}

template <typename T>
void StorageUnit<T>::addEquipment(const T& item)
{
	inventory.push_back(item);
}

template <typename T>
bool StorageUnit<T>::containsEquipmentId(int equipmentId) const
{
	return std::any_of(inventory.begin(), inventory.end(), [equipmentId](const T& item)
	{
		return item.getId() == equipmentId;
	});
}

template <typename T>
std::size_t StorageUnit<T>::getInventorySize() const
{
	return inventory.size();
}

template <typename T>
void StorageUnit<T>::sortInventory()
{
	std::sort(inventory.begin(), inventory.end());
}

template <typename T>
void StorageUnit<T>::printUnitInformation() const
{
	std::cout << "Storage Unit Information" << std::endl;
	std::cout << std::setfill('-') << std::setw(STORAGE_UNIT_SCREEN_WIDTH) << "" << std::setfill(' ') << std::endl;
	std::cout << "ID: " << getId() << std::endl;
	std::cout << "Description: " << getDescription() << std::endl;
	std::cout << "Dimensions (LxWxH): " << getLength() << " x " << getWidth() << " x " << getHeight() << " feet" << std::endl << std::endl;
	std::cout << "**Storage unit " << (getHumidityControlled() ? "is" : "is not") << " humidity controlled." << std::endl << std::endl;
	std::cout << "Rental Contract Details" << std::endl;
	std::cout << std::fixed << std::setprecision(2) << "Cost Per Month: $" << getCostPerMonth() << std::endl;
	std::cout << "Date Signed: " << getDateRented() << std::endl << std::endl;
	std::cout << "**Rental contract " << (getAutoRenewal() ? "does" : "does not") << " auto-renew." << std::endl;
}

template <typename T>
void StorageUnit<T>::printInventory(const std::string& equipmentType) const
{
	std::vector<T> sortedInventory = inventory;
	std::sort(sortedInventory.begin(), sortedInventory.end());

	std::cout << std::fixed << std::setprecision(2);
	std::cout << std::setfill('-') << std::setw(100) << "" << std::setfill(' ') << std::endl;
	std::cout << std::right << std::setw(calculateCenteredTextX("Health Care Options, Inc.")) << "Health Care Options, Inc." << std::endl;
	std::cout << std::right << std::setw(calculateCenteredTextX(equipmentType + " Equipment Inventory")) << equipmentType << " Equipment Inventory" << std::endl;
	std::cout << std::setfill('-') << std::setw(100) << "" << std::setfill(' ') << std::endl << std::endl;
	std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Name" << std::setw(15) << "Purchase Date"
		<< std::setw(15) << "Original Cost" << std::setw(14) << "Useful Life" << std::setw(15) << "Salvage Value" << "Type/Mode" << std::endl;
	std::cout << std::setfill('-') << std::setw(100) << "" << std::setfill(' ') << std::endl;

	for (const T& item : sortedInventory)
		item.printDetails(std::cout);
}

template <typename T>
int StorageUnit<T>::calculateCenteredTextX(const std::string& text) const
{
	return STORAGE_UNIT_SCREEN_WIDTH / 2 + static_cast<int>(text.size()) / 2;
}
