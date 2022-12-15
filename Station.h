#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
namespace sdds
{
    class Station
    {
        int m_id;
        std::string m_name{};
        std::string m_desc{};
        size_t m_serialNum{};
        size_t m_stockNum{};
        static size_t m_widthField;
        static size_t id_generator;
    public:
        Station(const std::string& station);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}
#endif // !SDDS_STATION_H
