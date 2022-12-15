#include <iomanip>
#include <string>
#include <algorithm>
#include "CustomerOrder.h"
#include"Utilities.h"

namespace sdds
{
    size_t CustomerOrder::m_widthField = 0;
    CustomerOrder::CustomerOrder() {}
    CustomerOrder::CustomerOrder(const std::string& str)
    {
        Utilities ut;
        size_t p = 0;
        bool more = false;
        std::string temp;

        m_name = ut.extractToken(str, p, more);
        m_product = ut.extractToken(str, p, more);

        temp = str.substr(p, str.length() - p);
        m_cntItem = (std::count(temp.begin(), temp.end(), ut.getDelimiter())) + 1;

        m_lstItem = new Item * [m_cntItem];
        for (size_t i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(ut.extractToken(str, p, more));
        }
        m_widthField = (m_widthField < ut.getFieldWidth()) ? ut.getFieldWidth() : m_widthField;
    }
    CustomerOrder::CustomerOrder(const CustomerOrder& src)
    {
        throw std::string("Cannot make copy!");
    }
    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
    {
        *this = std::move(src);
    }
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
    {
        if (this != &src)
        {
            if (m_lstItem) {
                for (size_t i = 0; i < m_cntItem; i++) {
                    delete m_lstItem[i];
                }
                delete[] m_lstItem;
            }

            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;
            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }
        return *this;
    }
    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }
    bool CustomerOrder::isOrderFilled() const
    {
        bool isOrderFilled = true;
        for (size_t i = 0; i < m_cntItem && isOrderFilled; i++) {
            isOrderFilled = m_lstItem[i]->m_isFilled;
        }
        return isOrderFilled;
    }
    bool CustomerOrder::isItemFilled(const std::string& itemName) const
    {
        bool isItemFilled = true;
        for (size_t i = 0; i < m_cntItem && isItemFilled; i++) {
            if (m_lstItem[i]->m_itemName == itemName)
                isItemFilled = m_lstItem[i]->m_isFilled;
        }
        return isItemFilled;
    }
    void CustomerOrder::fillItem(Station& station, std::ostream& os)
    {
        bool flag = true;
        for (size_t i = 0; i < m_cntItem && flag; i++)
        {
            if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled)
            {
                flag = false;
                if (station.getQuantity() > 0)
                {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", ";
                    os << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
                else
                {
                    os << "Unable to fill " << m_name << ", ";
                    os << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }
    void CustomerOrder::display(std::ostream& os) const
    {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << std::left << std::setw(m_widthField + 2) << std::setfill(' ') << m_lstItem[i]->m_itemName;
            os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}