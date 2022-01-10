#pragma once


#pragma once
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>

namespace sdds
{
	class Utilities
	{
		static char limit;
		size_t widthsize = 1;
	public:
		std::string extractToken(const std::string&, size_t&, bool&);
		static void setDelimiter(char);
		static char getDelimiter();
		void setFieldWidth(size_t);
		size_t getFieldWidth() const;

	};
}
#endif
