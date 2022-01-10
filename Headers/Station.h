
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>

namespace sdds
{
	class Station
	{
		std::string stationDetails;
		std::string stationName;
		int stationID;
		unsigned int quantity;
		unsigned int stationNum;


		static int newIDstat;
		static size_t maxChar;
	public:
		void display(std::ostream& os, bool full) const;
		unsigned int getNextSerialNumber();
		unsigned int getQuantity() const;
		const std::string& getItemName() const;
		Station(const std::string&);
		void updateQuantity();
	};
}
#endif
