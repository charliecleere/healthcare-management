#include "Visit.h"

#include <cctype>
#include <cstring>

Visit::Visit(int i, Nurse n, Aide a)
{
	setId(i);
	setNurse(n);
	setAide(a);
}

Visit::~Visit()
{

}

int Visit::getId() const
{
	return id;
}

Date Visit::getDate() const
{
	return date;
}

Nurse Visit::getNurse() const
{
	return nurse;
}

Aide Visit::getAide() const
{
	return aide;
}

void Visit::setId(int i)
{
	if (i < 0)
	{
		std::cout << "Invalid ID. ID cannot be negative. Please try again." << std::endl;
		i = -1;
	}
	else
		id = i;
}

void Visit::setDate(int m, int d, int y)
{
	date.setDate(m, d, y);
}

void Visit::setNurse(Nurse n)
{
	nurse = n;
}

void Visit::setAide(Aide a)
{
	aide = a;
}

void Visit::addService(Service s)
{
	services.push_back(s);
}

void Visit::printVisit(std::ostream& out) const
{
	out << std::setw(12) << "" << std::left << std::setw(26) << "Visit ID: " << id << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Visit date: " << date << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Nurse: " << nurse.getFirstName() << " " << nurse.getLastName() << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Aide: " << aide.getFirstName() << " " << aide.getLastName() << std::endl;
	if (services.size() > 0)
	{
		out << std::setw(12) << "" << std::left << std::setw(25) << "Service(s) provided: " << std::endl;
		for (std::size_t i = 0; i < services.size(); i++)
		{
			out << std::setw(12) << "" << std::left << "- " << services[i].getName() << std::endl;
		}
	}
	out << std::endl;
}

// Parses m/d/yyyy or mm/dd/yyyy and validates the calendar date.
void Visit::tokenizeDate(const char* dateStr, int& month, int& day, int& year) const
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
