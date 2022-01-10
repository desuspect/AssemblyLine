
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>
#include "Utilities.h"
#include "Workstation.h"
#include "LineManager.h"
using namespace std;

namespace sdds
{

    bool LineManager::run(ostream& os)
    {
        static size_t res = 1u;
        bool state = false;
        os << "Line Manager Iteration: ";
        os << res;
        os << endl;
        res++;
        if (!pending.empty())
        {
            *activeLine.front() += move(pending.front());
            pending.erase(pending.begin());
        }

        for_each(activeLine.begin(), activeLine.end(), [&](Workstation* workStation)
            {
                workStation->fill(os);
            });

        for_each(activeLine.begin(), activeLine.end(), [&](Workstation* workStation)
            {
                workStation->attemptToMoveOrder();
            });

        if (completed.size() + incomplete.size() == m_cntCustomerOrder)
        {
            state = true;
        }
        return state;
    }

    void LineManager::linkStations()
    {
        vector<Workstation*> ordr;
        Workstation* stn = m_firstStation;
        while (stn != nullptr)
        {
            ordr.push_back(stn);
            stn = stn->getNextStation();
        }
        activeLine = ordr;
    }

    LineManager::LineManager(const string& str, const vector<Workstation*>& stations)
    {
        ifstream fRead(str);
        string Size;
        int itrnum = 0;
        bool state = true;
        m_cntCustomerOrder = pending.size();

        while (getline(fRead, Size))
        {
            string::size_type val = Size.find('|');
            for (size_t iname = 0; iname < stations.size(); ++iname)
            {
                if (stations.at(iname)->getItemName() == Size.substr(0, val))
                {
                    if (val != string::npos)
                    {
                        for (size_t ilist = 0; ilist < stations.size(); ++ilist)
                        {
                            if (stations.at(ilist)->getItemName() == Size.substr(val + 1))
                            {
                                stations.at(iname)->setNextStation(stations.at(ilist));
                                activeLine.push_back(move(stations.at(iname)));
                            }
                        }
                    }
                    else
                    {
                        activeLine.push_back(move(stations.at(iname)));
                    }
                }
            }
            for (size_t iname = 0; iname < activeLine.size(); ++iname)
            {
                for (size_t ilist = 0; ilist < activeLine.size(); ++ilist)
                {
                    if (activeLine.at(ilist)->getNextStation() != nullptr)
                    {
                        if (activeLine.at(iname)->getItemName() == activeLine.at(ilist)->getNextStation()->getItemName())
                        {
                            state = false;
                        }
                    }
                }
                if (state)
                {
                    m_firstStation = activeLine.at(iname);
                }
                state = true;
            }
            itrnum++;
        }
    }

    void LineManager::display(ostream& os) const
    {

        for (size_t i = 0; i < activeLine.size(); ++i)
        {
            activeLine.at(i)->display(os);
            os << endl;
        }
    }


}
