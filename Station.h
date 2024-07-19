#ifndef STATION_H
#define STATION_H

#include <ostream>
#include <string>

namespace sdds {
class Station {
public:
  Station(const std::string &);

  const std::string &getItemName() const;
  size_t getNextSerialNumber();
  size_t getQuantity() const;
  void updateQuantity();
  void display(std::ostream &, bool) const;

private:
  ssize_t m_id;
  std::string m_itemName;
  std::string m_description;
  size_t m_serialNo;
  size_t m_stockCount;

  static size_t m_widthField;
  static size_t id_generator;
};
} // namespace sdds

#endif // !STATION_H
