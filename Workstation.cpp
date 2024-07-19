#include "Workstation.h"

std::deque<sdds::CustomerOrder> g_pending;
std::deque<sdds::CustomerOrder> g_completed;
std::deque<sdds::CustomerOrder> g_incomplete;

namespace sdds {
Workstation::Workstation(const std::string str)
    : Station(str), m_pNextStation{} {}

void Workstation::fill(std::ostream &os) {
  if (m_orders.size()) {
    m_orders.front().fillItem(*this, os);
  }
}

bool Workstation::attemptToMoveOrder() {
  bool moved = false;
  if (!m_orders.empty()) {
    CustomerOrder &currentCustomerOrder = m_orders.front();
    if (getQuantity() == 0) {
      if (m_pNextStation) {
        *m_pNextStation += std::move(currentCustomerOrder);
      } else {
        g_incomplete.push_back(std::move(currentCustomerOrder));
      }
      m_orders.pop_front();
      moved = true;
    } else if (currentCustomerOrder.isItemFilled(getItemName())) {
      if (m_pNextStation) {
        *m_pNextStation += std::move(currentCustomerOrder);
      } else {
        if (currentCustomerOrder.isOrderFilled()) {
          g_completed.push_back(std::move(currentCustomerOrder));
        } else {
          g_incomplete.push_back(std::move(currentCustomerOrder));
        }
      }
      m_orders.pop_front();
      moved = true;
    }
  }
  return moved;
}

void Workstation::setNextStation(Workstation *station) {
  m_pNextStation = station;
}

Workstation *Workstation::getNextStation() const { return m_pNextStation; }

void Workstation::display(std::ostream &os) const {
  os << getItemName() << " --> ";
  if (m_pNextStation) {
    os << m_pNextStation->getItemName();
  } else {
    os << "End of Line";
  }
  os << std::endl;
}

Workstation &Workstation::operator+=(CustomerOrder &&newOrder) {
  m_orders.push_back(std::move(newOrder));
  return *this;
}

} // namespace sdds
