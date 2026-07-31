#pragma once

#include <stdexcept>

// Signals a date that is malformed or outside the calendar's valid range.
class InvalidDateException : public std::runtime_error
{
public:
	// Supplies the user-facing validation message.
	InvalidDateException() : std::runtime_error("Invalid date format.") 
	{
	
	}
};
