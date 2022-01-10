

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <vector>
#include "Workstation.h"

using namespace std;
namespace sdds
{
    class LineManager
    {
        vector<Workstation*> activeLine;
        size_t m_cntCustomerOrder;
        Workstation* m_firstStation;

    public:
        explicit LineManager(const string& str, const vector<Workstation*>& stations);
        void display(ostream& os) const;
        void linkStations();
        bool run(ostream& os);
    };
}
#endif //!SDDS_LINEMANAGER_H
