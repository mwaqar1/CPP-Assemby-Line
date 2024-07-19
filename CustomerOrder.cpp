#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <utility>

namespace sdds {
size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() : m_cntItem{}, m_listItem{} {}

CustomerOrder::CustomerOrder(const std::string &str) : CustomerOrder() {
  Utilities utilities{};
  size_t next_pos = 0;
  bool more = true;
  m_name = utilities.extractToken(str, next_pos, more);
  m_product = utilities.extractToken(str, next_pos, more);
  size_t itemCount{};
  m_listItem = new Item *[itemCount + 1];
  while (more) {
    if (m_cntItem >= itemCount) {
      itemCount++;
      Item **temp = new Item *[itemCount + 1];
      for (size_t i = 0; i < m_cntItem; i++) {
        temp[i] = m_listItem[i];
      }
      delete[] m_listItem;
      m_listItem = temp;
    }

    m_listItem[m_cntItem] =
        new Item(utilities.extractToken(str, next_pos, more));
    m_cntItem++;
  }
  if (m_widthField < utilities.getFieldWidth()) {
    m_widthField = utilities.getFieldWidth();
  }
}

CustomerOrder::CustomerOrder(CustomerOrder &&C) noexcept : CustomerOrder() {
  *this = std::move(C);
}

CustomerOrder &CustomerOrder::operator=(CustomerOrder &&C) noexcept {
  if (this != &C) {
    delete[] m_listItem;
    m_name = std::move(C.m_name);
    m_product = std::move(C.m_product);
    m_cntItem = C.m_cntItem;
    m_listItem = C.m_listItem;
    C.m_listItem = nullptr;
    C.m_cntItem = 0;
  }
  return *this;
}

CustomerOrder::~CustomerOrder() {
  for (size_t i = 0; i < m_cntItem; i++) {
    delete m_listItem[i];
  }
  delete[] m_listItem;
}

bool CustomerOrder::isItemFilled(const std::string &itemName) const {
  bool isFilled = true;
  bool earlyReturn = true;

  // if string doesn't exist in it, return true.
  for (size_t i = 0; i < m_cntItem && earlyReturn; i++) {
    if (m_listItem[i]->m_itemName == itemName) {
      earlyReturn = false;
    }
  }
  if (!earlyReturn) {
    for (size_t i = 0; i < m_cntItem && isFilled; i++) {
      if (!m_listItem[i]->m_isFilled && m_listItem[i]->m_itemName == itemName) {
        isFilled = false;
      }
    }
  }

  return isFilled;
}
void CustomerOrder::fillItem(Station &station, std::ostream &os) {
  bool itemFilled = false;

  if (!isItemFilled(station.getItemName())) {
    for (size_t i = 0; i < m_cntItem && !itemFilled; i++) {
      std::string itemName = m_listItem[i]->m_itemName;
      if (!m_listItem[i]->m_isFilled && station.getItemName() == itemName) {
        os << std::setw(4) << std::setfill(' ') << " ";
        if (station.getQuantity()) {
          m_listItem[i]->m_isFilled = itemFilled = true;
          m_listItem[i]->m_serialNumber = station.getNextSerialNumber();
          os << "Filled ";
          station.updateQuantity();
        } else {
          os << "Unable to fill ";
        }
        os << m_name << ", " << m_product << " [" << itemName << "]"
           << std::endl;
      }
    }
  }
}

void CustomerOrder::display(std::ostream &os) const {
  os << m_name << " - " << m_product << std::endl;
  for (size_t i = 0; i < m_cntItem; i++) {
    os << "[" << std::setw(6) << std::right << std::setfill('0')
       << m_listItem[i]->m_serialNumber << "] " << std::setw(m_widthField)
       << std::left << std::setfill(' ') << m_listItem[i]->m_itemName << " - ";
    if (!m_listItem[i]->m_isFilled) {
      os << "TO BE ";
    }
    os << "FILLED" << std::endl;
  }
}

bool CustomerOrder::isOrderFilled() const {
  bool isFilled = true;
  for (std::size_t i = 0; i < m_cntItem && isFilled; i++) {
    isFilled = m_listItem[i]->m_isFilled;
  }
  return isFilled;
}

} // namespace sdds
