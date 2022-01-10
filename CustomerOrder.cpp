
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	void CustomerOrder::fillItem(Station& station, ostream& os)
	{
		unsigned int i;
		for (i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() > 0)
				{
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					station.updateQuantity();
					m_lstItem[i]->m_isFilled = true;
					os << right;
					os << "    Filled ";
					os << m_name;
					os << ", ";
					os << m_product;
					os << " [";
					os << m_lstItem[i]->m_itemName;
					os << "]";
					os << endl;
				}
				else
				{
					os << right;
					os << "    Unable to fill ";
					os << m_name;
					os << ", ";
					os << m_product;
					os << " [";
					os << m_lstItem[i]->m_itemName;
					os << "]";
					os << endl;
				}
			}
		}
	}

	CustomerOrder::CustomerOrder(const string& str)
	{

		Utilities Util;
		auto state = true;
		size_t coming = 0;
		m_name = Util.extractToken(str, coming, state);
		m_product = Util.extractToken(str, coming, state);
		m_cntItem = 0;
		auto startwith = coming;
		while (state)
		{
			Util.extractToken(str, coming, state);
			m_cntItem++;
		}
		m_lstItem = new Item * [m_cntItem];
		state = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item(Util.extractToken(str, startwith, state));
		}
		if (Util.getFieldWidth() > m_widthField)
		{
			m_widthField = Util.getFieldWidth();
		}
	}

	bool CustomerOrder::isFilled() const
	{
		unsigned int i;
		for (i = 0; i < m_cntItem; i++)
			if (!m_lstItem[i]->m_isFilled)
			{
				return false;
			}
		return true;
	}

	bool CustomerOrder::isItemFilled(const string& str) const
	{
		unsigned int i;
		for (i = 0; i < m_cntItem; i++)
			if (m_lstItem[i]->m_itemName == str)
			{
				return m_lstItem[i]->m_isFilled;
			}
		return true;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& cordr) noexcept
	{
		*this = move(cordr);
	}

	CustomerOrder::~CustomerOrder()
	{
		unsigned int i;
		if (m_lstItem)
			for (i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& cordr) noexcept
	{
		unsigned int i;
		if (&cordr != this)
		{
			if (m_lstItem)
				for (i = 0; i < m_cntItem; i++)
				{
					delete this->m_lstItem[i];
				}
			delete[] this->m_lstItem;
			this->m_name = cordr.m_name;
			this->m_product = cordr.m_product;
			this->m_cntItem = cordr.m_cntItem;
			this->m_lstItem = cordr.m_lstItem;
			cordr.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::CustomerOrder()
	{
		m_name = "default";
		m_product = "default";
		m_lstItem = nullptr;
		m_cntItem = 0;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&)
	{
		string str = "A CustomerOrder object should not allow copy operations";
		throw str;
	}



	void CustomerOrder::display(ostream& os) const
	{
		unsigned int i;
		os << m_name;
		os << " - ";
		os << m_product;
		os << endl;
		for (i = 0; i < m_cntItem; i++)
		{
			os << "[";
			os << setfill('0');
			os << right;
			os << setw(6);
			os << m_lstItem[i]->m_serialNumber;
			os << "] ";
			os << setfill(' ');
			os << setw(m_widthField);
			os << left;
			os << m_lstItem[i]->m_itemName;
			os << setfill(' ');
			os << " - ";
			os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
			os << endl;
		}
	}
}
