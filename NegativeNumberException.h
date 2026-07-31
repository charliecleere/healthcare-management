#pragma once

#include <stdexcept>

// Signals a negative value where the domain requires a non-negative value.
class NegativeNumberException : public std::runtime_error
{
public:
	// Supplies the user-facing validation message.
	NegativeNumberException() : std::runtime_error("Only positive numbers are allowed.")
	{

	}
};
