#include "Utilities.h"
#include <algorithm>

namespace sdds {
char Utilities::m_delimiter{};

void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }

size_t Utilities::getFieldWidth() const { return m_widthField; }

Utilities::Utilities() : m_widthField{1} {};

std::string Utilities::trim(const std::string &str) {
  auto first = std::find_if_not(str.begin(), str.end(),
                                [](ssize_t c) { return std::isspace(c); });

  auto last = std::find_if_not(str.rbegin(), str.rend(),
                               [](ssize_t c) { return std::isspace(c); });

  return std::string(first, last.base());
}

std::string Utilities::extractToken(const std::string &str, size_t &next_pos,
                                    bool &more) {
  std::string token;
  if (str[next_pos] == m_delimiter) {
    more = false;
    throw "Delimiter found";
  }
  size_t index = str.find(m_delimiter, next_pos);

  token = index == std::string::npos ? (more = false, str.substr(next_pos))
                                     : str.substr(next_pos, index - next_pos);

  next_pos = index + 1;
  m_widthField = m_widthField > token.length() ? m_widthField : token.length();
  return trim(token);
}

void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }

char Utilities::getDelimiter() { return m_delimiter; }

} // namespace sdds
