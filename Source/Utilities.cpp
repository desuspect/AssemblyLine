
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <algorithm>
#include "Utilities.h"

using namespace std;
namespace sdds
{
	size_t Utilities::getFieldWidth() const
	{
		return widthsize;
	}

	char Utilities::limit = ' ';

	void Utilities::setFieldWidth(size_t n_widthSize)
	{
		widthsize = n_widthSize;
	}

	std::string Utilities::extractToken(const std::string& arr, size_t& onwards, bool& extra)
	{
		string output = "";
		size_t startwith = onwards;

		onwards = arr.find(limit, startwith);

		if (startwith == onwards)
		{
			extra = false;
			throw "No token between delimiters!";
		}

		else if (onwards == string::npos)
		{
			output = arr.substr(startwith);
			widthsize = max(output.length(), widthsize);
			extra = false;
		}

		else
		{
			output = arr.substr(startwith, onwards - startwith);
			widthsize = max(output.length(), widthsize);
			extra = true;
		}

		onwards += 1;

		return output;
	}

	void Utilities::setDelimiter(char newlimit)
	{

		limit = newlimit;

	}

	char Utilities::getDelimiter()
	{
		return limit;
	}

}
