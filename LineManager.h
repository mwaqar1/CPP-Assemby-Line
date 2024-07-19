#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include "Workstation.h"
#include <vector>

namespace sdds {
class LineManager {
public:
  LineManager() = default;
  LineManager(const std::string &file,
              const std::vector<Workstation *> &stations);
  LineManager(LineManager &&) = default;
  LineManager(const LineManager &) = default;
  LineManager &operator=(LineManager &&) = default;
  LineManager &operator=(const LineManager &) = default;
  ~LineManager() = default;

  void reorderStations();
  bool run(std::ostream &os);
  void display(std::ostream &os) const;

private:
  std::vector<Workstation *> m_activeLine;
  size_t m_cntCustomerOrder;
  Workstation *m_firstStation;
};

} // namespace sdds

#endif // !LINEMANAGER_H
