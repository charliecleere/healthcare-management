#include "Date.h"

std::ostream& operator<<(std::ostream& output, const Date& d)
{
	output << std::to_string(d.month) + "/" + std::to_string(d.day) + "/" + std::to_string(d.year);
	return output;
}

Date::Date(int m, int d, int y)
{
	setDate(m, d, y);
}

Date::~Date()
{

}

// Stores the calendar components; callers validate input before setting dates.
void Date::setDate(int  m, int d, int y)
{
	month = m;
	day = d;
	year = y;
}
