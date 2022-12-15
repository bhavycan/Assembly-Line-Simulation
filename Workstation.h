#ifndef SDDS_WORK_STATION_H
#define SDDS_WORK_STATION_H
#include <deque>
#include"Station.h"
#include "CustomerOrder.h"
namespace sdds
{
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation{ nullptr };
	public:
		Workstation(const std::string& str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;
	};
}
#endif // !SDDS_WORK_STATION_H
