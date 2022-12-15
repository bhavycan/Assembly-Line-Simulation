#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& station)
	{
		Utilities ut;
		bool more = false;
		size_t position = 0;

		m_id = ++id_generator;
		m_name = ut.extractToken(station, position, more);
		m_serialNum = stoi(ut.extractToken(station, position, more));
		m_stockNum = stoi(ut.extractToken(station, position, more));
		(m_widthField < ut.getFieldWidth()) ? m_widthField = ut.getFieldWidth() : 1;
		m_desc = ut.extractToken(station, position, more);
	}
	const std::string& Station::getItemName() const
	{
		return m_name;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_serialNum++;
	}
	size_t Station::getQuantity() const
	{
		return m_stockNum;
	}
	void Station::updateQuantity()
	{
		if (m_stockNum > 0)
			m_stockNum--;
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setw(3) << std::setfill('0') << std::right << m_id << " | ";
		os << std::setw(m_widthField + 1) << std::setfill(' ') << std::left << m_name << " | ";
		os << std::setw(6) << std::setfill('0') << std::right << m_serialNum << " | ";

		if (full)
		{
			os << std::setfill(' ') << std::right << std::setw(4) << m_stockNum << " | ";
			os << m_desc;
		}
		os << std::endl;
	}
}