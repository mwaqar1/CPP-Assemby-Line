#include "Station.h"
#include "Utilities.h"
#include <iomanip>
#include <string>

namespace sdds {

size_t Station::m_widthField{};
size_t Station::id_generator{};

Station::Station(const std::string &str) {
  m_id = ++Station::id_generator;
  Utilities util;
  size_t next_pos = 0;
  bool more = true;
  m_itemName = util.extractToken(str, next_pos, more);
  m_serialNo = stoi(util.extractToken(str, next_pos, more));
  m_stockCount = stoi(util.extractToken(str, next_pos, more));
  Station::m_widthField = Station::m_widthField > util.getFieldWidth()
                              ? Station::m_widthField
                              : util.getFieldWidth();

  m_description = util.extractToken(str, next_pos, more);
}

const std::string &Station::getItemName() const { return m_itemName; }

size_t Station::getNextSerialNumber() { return m_serialNo++; }

size_t Station::getQuantity() const { return m_stockCount; }

void Station::updateQuantity() {
  if (m_stockCount > 0) {
    m_stockCount--;
  }
}

void Station::display(std::ostream &os, bool full) const {
  os << std::setw(3) << std::right << std::setfill('0') << m_id << " | "
     << std::setfill(' ') << std::setw(m_widthField) << std::left << m_itemName
     << " | " << std::setfill('0') << std::setw(6) << std::right << m_serialNo
     << " | ";
  if (full) {
    os << std::setfill(' ') << std::right << std::setw(4) << m_stockCount
       << " | " << m_description;
  }
  os << std::endl;
}

} // namespace sdds
