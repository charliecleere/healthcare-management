#pragma once

#include <stdexcept>  // Contains runtime_error

// Custom exception class for negative number, inherits from std::runtime_error
class NegativeNumberException : public std::runtime_error
{
public:
	// Constructor that initializes the base class with a custom error message
	NegativeNumberException() : std::runtime_error("Only positive numbers are allowed.")
	{

	}
};
