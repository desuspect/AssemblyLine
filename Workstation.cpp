

#include <iostream>
#include "Workstation.h"
#include "Station.h"

using namespace std;
namespace sdds
{
    deque<CustomerOrder> pending{};
    deque<CustomerOrder> completed{};
    deque<CustomerOrder> incomplete{};

    Workstation::Workstation(const string& str) : Station(str)
    {
    }

    bool Workstation::attemptToMoveOrder()
    {
        bool state = false;
        if (m_orders.empty())
        {
            return state;
        }

        if (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() == 0)
        {
            if (m_pNextStation != nullptr)
            {
                *m_pNextStation += move(m_orders.front());
            }
            else if (m_orders.front().isFilled())
            {
                completed.push_back(move(m_orders.front()));
            }
            else
            {
                incomplete.push_back(move(m_orders.front()));
            }
            m_orders.erase(m_orders.begin());
            return state == true;
        }
        else
        {
            return state;
        }
    }

    void Workstation::fill(ostream& os)
    {
        if (!m_orders.empty())
        {
            m_orders.begin()->fillItem(*this, os);
        }
    }

    Workstation& Workstation::operator+=(CustomerOrder&& cordr)
    {
        m_orders.push_back(move(cordr));
        return *this;
    }

    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(ostream& os) const
    {
        os << getItemName();
        os << " --> ";

        if (m_pNextStation != nullptr)
        {
            os << m_pNextStation->getItemName();
        }
        else
        {
            os << "End of Line";
        }
    }

    void Workstation::setNextStation(Workstation* station)
    {
        m_pNextStation = station;
    }


}
