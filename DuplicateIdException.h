#pragma once

#include <stdexcept>

// Signals an attempt to reuse an identifier that must be unique.
class DuplicateIdException : public std::runtime_error
{
public:
	// Supplies the user-facing validation message.
	DuplicateIdException() : std::runtime_error("This ID already exists.")
	{

	}
};
