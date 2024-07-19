#include "LineManager.h"
#include "Utilities.h"
#include <algorithm>
#include <fstream>

namespace sdds {

LineManager::LineManager(const std::string &file,
                         const std::vector<Workstation *> &stations) {
  std::ifstream fileBuf(file);
  if (fileBuf) {
    std::string workstationName, lineInFile;
    auto findName = [&](const Workstation *ws) -> bool {
      return workstationName == ws->getItemName();
    };
    while (getline(fileBuf, lineInFile)) {
      Utilities utilities{};
      if (utilities.getDelimiter() != '|') {
        utilities.setDelimiter('|');
      }
      size_t next_pos{};
      bool more = true;
      workstationName = utilities.extractToken(lineInFile, next_pos, more);
      auto i = std::find_if(stations.begin(), stations.end(), findName);
      if (i == stations.end()) {
        throw "Station " + workstationName + " not found";
      }
      m_activeLine.push_back(*i);
      if (more) {
        workstationName = utilities.extractToken(lineInFile, next_pos, more);
        auto j = std::find_if(stations.begin(), stations.end(), findName);
        if (j == stations.end()) {
          throw "Station " + workstationName + " not found";
        }
        (**i).setNextStation(*j);
      } else {
        (**i).setNextStation();
      }
    }
    fileBuf.close();
    m_cntCustomerOrder = g_pending.size();

    auto first = std::find_if_not(
        m_activeLine.begin(), m_activeLine.end(), [=](Workstation *w) -> bool {
          auto c = std::count_if(
              m_activeLine.begin(), m_activeLine.end(),
              [=](Workstation *m) -> bool { return m->getNextStation() == w; });
          return c > 0;
        });

    if (first == m_activeLine.end()) {
      throw "No stations are in the active line";
    }
    m_firstStation = *first;
  } else {
    throw "Unable to open file: " + file;
  }
}

void LineManager::reorderStations() {
  Workstation *temp = m_firstStation;
  std::vector<Workstation *> newWorkStation;
  while (temp) {
    newWorkStation.push_back(temp);
    temp = temp->getNextStation();
  }
  m_activeLine = newWorkStation;
}

bool LineManager::run(std::ostream &os) {
  static size_t counter = 0;
  ++counter;
  os << "Line Manager Iteration: " << counter << std::endl;
  if (g_pending.size()) {
    *m_firstStation += std::move(g_pending.front());
    g_pending.pop_front();
  }
  for (Workstation *workstation : m_activeLine) {
    workstation->fill(os);
  }
  for (Workstation *workstation : m_activeLine) {
    workstation->attemptToMoveOrder();
  }
  return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
}

void LineManager::display(std::ostream &os) const {
  for (Workstation *ws : m_activeLine) {
    ws->display(os);
  }
}
} // namespace sdds
