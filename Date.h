#pragma once

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>

class Date
{
	friend std::ostream& operator<<(std::ostream& output, const Date& d);

public:
	Date(int = 0, int = 0, int = 0);
	~Date();
	void setDate(int m, int d, int y);

private:
	int month;
	int day;
	int year;
};
