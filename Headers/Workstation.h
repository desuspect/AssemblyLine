
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <ostream>
#include <vector>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
using namespace std;

namespace sdds
{
    extern deque<CustomerOrder> pending;
    extern deque<CustomerOrder> completed;
    extern deque<CustomerOrder> incomplete;

    class Workstation : public Station
    {
        deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{ nullptr };
    public:
        void fill(ostream& os);
        Workstation& operator+=(CustomerOrder&& cordr);
        Workstation(const string& str);
        Workstation* getNextStation() const;
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        void display(ostream& os) const;
    };
}
#endif //!SDDS_WORKSTATION_H
