#include "Workstation.h"

namespace sdds
{
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};


	Workstation::Workstation(const std::string& str) : Station(str) {}

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
			m_orders.front().fillItem(*this, os);
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool Ordermoved = false;
		if (!m_orders.empty())
		{
			if (m_orders.front().isItemFilled(Station::getItemName()) || Station::getQuantity() <= 0)
			{
				Ordermoved = true;
				if (m_pNextStation)
				{
					*m_pNextStation += std::move(m_orders.front());
				}
				else
				{
					(m_orders.front().isOrderFilled()) ? g_completed.push_back(std::move(m_orders.front())) : g_incomplete.push_back(std::move(m_orders.front()));
				}
				m_orders.pop_front();
			}
		}
		return Ordermoved;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		if (m_pNextStation)
			os << getItemName() << " --> " << getNextStation()->getItemName() << std::endl;
		else
			os << getItemName() << " --> End of Line" << "\n";
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

}