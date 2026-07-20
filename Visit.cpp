#include "Visit.h"

// Constructor with a default parameter
Visit::Visit(int i, Nurse n, Aide a)
{
	setId(i);
	setNurse(n);
	setAide(a);
}

// Destructor
Visit::~Visit()
{

}

// Accessor and mutator functions
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

void::Visit::setId(int i)
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
	//out << std::setw(12) << "" << std::left << std::setw(26) << "Provider: " << employee_name << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Visit date: " << date << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Nurse: " << nurse.getFirstName() << " " << nurse.getLastName() << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Aide: " << aide.getFirstName() << " " << aide.getLastName() << std::endl;
	if (services.size() > 0)
	{
		out << std::setw(12) << "" << std::left << std::setw(25) << "Service(s) provided: " << std::endl;
		for (int i = 0; i < services.size(); i++)
		{
			out << std::setw(12) << "" << std::left << "- " << services[i].getName() << std::endl;
		}
	}
	out << std::endl;
}

// Function to tokenize the date
void Visit::tokenizeDate(char* dateStr, int& month, int& day, int& year)
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