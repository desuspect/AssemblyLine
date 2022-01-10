
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include <utility>
#include "Station.h"
using namespace std;

namespace sdds
{
    struct Item
    {
        string m_itemName;
        size_t m_serialNumber{ 0 };
        bool m_isFilled{ false };
        Item(const string& src) : m_itemName(src) {};
    };

    class CustomerOrder
    {
        string m_name;
        string m_product;
        size_t m_cntItem{};
        Item** m_lstItem{};
        static size_t m_widthField;

    public:
        CustomerOrder(const string&);
        CustomerOrder();
        CustomerOrder& operator=(CustomerOrder& cordr) = delete;
        CustomerOrder& operator=(CustomerOrder&& cordr) noexcept;
        void display(ostream& os) const;
        CustomerOrder(CustomerOrder&& cordr) noexcept;
        CustomerOrder(CustomerOrder& cordr);
        bool isItemFilled(const string& str) const;
        ~CustomerOrder();
        bool isFilled() const;
        void fillItem(Station& station, ostream& os);
    };
}
#endif //!SDDS_CUSTOMERORDER_H
