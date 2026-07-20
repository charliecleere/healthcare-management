#pragma once

#include <stdexcept>  // Contains runtime_error

// Custom exception class for invalid date format, inherits from std::runtime_error
class InvalidDateException : public std::runtime_error
{
public:
	// Constructor that initializes the base class with a custom error message
	InvalidDateException() : std::runtime_error("Invalid date format.") 
	{
	
	}
};