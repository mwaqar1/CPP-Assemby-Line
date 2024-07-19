#ifndef WORKSTATION_H
#define WORKSTATION_H

#include "CustomerOrder.h"
#include "Station.h"
#include <deque>
#include <string>

extern std::deque<sdds::CustomerOrder> g_pending;
extern std::deque<sdds::CustomerOrder> g_completed;
extern std::deque<sdds::CustomerOrder> g_incomplete;

namespace sdds {

class Workstation : public Station {
public:
  Workstation(const std::string str);

  void fill(std::ostream &os);
  bool attemptToMoveOrder();
  void setNextStation(Workstation *station = nullptr);
  Workstation *getNextStation() const;
  void display(std::ostream &os) const;
  Workstation &operator+=(CustomerOrder &&newOrder);

private:
  std::deque<CustomerOrder> m_orders;
  Workstation *m_pNextStation;
};

} // namespace sdds

#endif // !SDDS_WORKSTATION_H
