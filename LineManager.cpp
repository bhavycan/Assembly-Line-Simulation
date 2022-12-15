#include <string>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds
{
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		std::ifstream f(file);
		Utilities ut;

		bool more = false;
		size_t pos = 0;
		std::string str;
		std::string item;
		std::string nextItem;

		if (!f)
		{
			throw std::string("Error: Unable to open file!");
		}
		else
		{
			Workstation* curStation{};
			Workstation* nextStation{};
			Workstation* firstStation{};
			while (getline(f, str))
			{
				item = ut.extractToken(str, pos, more);
				curStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* s) {
					return s->getItemName() == item;
				});

				m_activeLine.push_back(curStation);

				if (more != false)
				{
					nextItem = ut.extractToken(str, pos, more);
					nextStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* s) {
						return s->getItemName() == nextItem;
					});

					curStation->setNextStation(nextStation);
				}
			}

			for_each(stations.begin(), stations.end(), [&](Workstation* s) {
				firstStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* s) {
					return s->getNextStation() == firstStation;
				});
			});

			m_firstStation = firstStation;
		}

		f.close();
		m_cntCustomerOrder = g_pending.size();
	}
	void LineManager::reorderStations()
	{
		Workstation* station = m_firstStation;
		std::vector<Workstation*> reOrdered;
		while (station)
		{
			reOrdered.push_back(station);
			station = station->getNextStation();
		}
		m_activeLine = reOrdered;
	}
	bool LineManager::run(std::ostream& os)
	{
		static size_t count = 0u;

		os << "Line Manager Iteration: " << ++count << std::endl;

		if (!g_pending.empty())
		{
			*m_activeLine.front() += std::move(g_pending.front());
			g_pending.pop_front();
		}

		for (auto& i : m_activeLine)
			i->fill(os);

		for (auto& i : m_activeLine)
			i->attemptToMoveOrder();

		return (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder);
	}
	void LineManager::display(std::ostream& os) const
	{
		for (auto& i : m_activeLine)
			i->display(os);
	}
}