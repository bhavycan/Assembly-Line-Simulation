#include <iostream>
#include <string>
#include "Utilities.h"
#include "Station.h"

namespace sdds
{
	char Utilities::m_delimiter{};

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token{};
		std::size_t position = str.find(getDelimiter(), next_pos);

		if (position == next_pos)
		{
			more = false;
			throw std::string("Not found!");
		}
		else if (position != std::string::npos)
		{
			token = str.substr(next_pos, position - next_pos);
			next_pos = token.find_first_not_of(" ");
			token.erase(token.begin(), token.begin() + next_pos);
			size_t end = token.find_last_not_of(" ");
			token.erase(end + 1);
			m_widthField = std::max(m_widthField, token.length());
			next_pos = position + 1;
			more = true;
		}
		else if (position == std::string::npos)
		{
			token = str.substr(next_pos, position - next_pos);
			next_pos = token.find_first_not_of(" ");
			token.erase(token.begin(), token.begin() + next_pos);
			size_t end = token.find_last_not_of(" ");
			token.erase(end + 1);
			m_widthField = std::max(m_widthField, token.length());
			next_pos = position + 1;
			more = false;
		}

		return token;

	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}