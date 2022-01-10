

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "Utilities.h"
#include "Station.h"

using namespace std;

namespace sdds {
	size_t Station::maxChar = 0;
	int Station::newIDstat = 1;

	void Station::display(std::ostream& ostr, bool state) const
	{
		ios todo(NULL);
		todo.copyfmt(cout);
		ostr << right << "[" << setw(3) << setfill('0') << stationID << "]";
		ostr << left << " Item: " << setw(maxChar) << setfill(' ') << stationName;
		ostr << right << " [" << setw(6) << setfill('0') << stationNum << "]";
		ostr << left;

		if (state == true)
		{

			ostr << " Quantity: " << setw(maxChar);
			ostr << setfill(' ') << quantity;
			ostr << " Description: ";
			ostr.copyfmt(todo);
			ostr << stationDetails << endl;
		}
		else
		{
			ostr << endl;
		}
	}

	unsigned int Station::getNextSerialNumber()
	{
		int snum;
		stationNum++;
		snum = stationNum - 1;
		return snum;
	}

	Station::Station(const std::string& arr)
	{
		stationID = newIDstat;
		Utilities values;
		size_t onwards = 0;
		bool state = true;

		try
		{
			stationName = values.extractToken(arr, onwards, state);
			stationNum = stoi(values.extractToken(arr, onwards, state));
			quantity = stoi(values.extractToken(arr, onwards, state));
			maxChar = max(values.getFieldWidth(), maxChar);
			stationDetails = values.extractToken(arr, onwards, state);
		}

		catch (string& context)
		{
			cout << context;
		}

		newIDstat += 1;
	}

	const std::string& Station::getItemName() const
	{
		return stationName;
	}

	unsigned int Station::getQuantity() const
	{
		return quantity;
	}

	void Station::updateQuantity()
	{
		quantity--;
		if (quantity < 0)
		{
			quantity = 0;
		}
	}

}
