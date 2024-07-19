#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include "Station.h"
#include "Utilities.h"
#include <iostream>

namespace sdds {

struct Item {
  std::string m_itemName;
  size_t m_serialNumber{0};
  bool m_isFilled{false};
  Item(const std::string &src) : m_itemName(src){};
};

class CustomerOrder {
public:
  CustomerOrder();
  CustomerOrder(const std::string &);
  CustomerOrder(CustomerOrder &&) noexcept;
  CustomerOrder(const CustomerOrder &) {
    throw "No copy allowed for Customer Orders!";
  }
  CustomerOrder &operator=(CustomerOrder &&) noexcept;
  CustomerOrder &operator=(const CustomerOrder &) = delete;
  ~CustomerOrder();

  bool isOrderFilled() const;
  bool isItemFilled(const std::string &itemName) const;
  void fillItem(Station &station, std::ostream &os);
  void display(std::ostream &os) const;

private:
  std::string m_name;
  std::string m_product;
  size_t m_cntItem;
  Item **m_listItem;
  void destruct();
  static size_t m_widthField;
};

} // namespace sdds

#endif // !CUSTOMERORDER_H
