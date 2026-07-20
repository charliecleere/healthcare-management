#pragma once

#include <stdexcept>  // Contains runtime_error

// Custom exception class for duplicate ID, inherits from std::runtime_error
class DuplicateIdException : public std::runtime_error
{
public:
	// Constructor that initializes the base class with a custom error message
	DuplicateIdException() : std::runtime_error("This ID already exists.")
	{

	}
};