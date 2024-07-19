#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>

namespace sdds {
class Utilities {

public:
  Utilities();

  void setFieldWidth(size_t newWidth);
  size_t getFieldWidth() const;
  std::string extractToken(const std::string &str, size_t &next_pos,
                           bool &more);
  static void setDelimiter(char newDelimiter);
  static char getDelimiter();
  std::string trim(const std::string &str);

private:
  size_t m_widthField;
  static char m_delimiter;
};

} // namespace sdds

#endif // !UTILITIES_H
