#include "include/table.h"

#include <algorithm>

namespace please {
Table::Table(std::vector<Text> headers) : headers{headers} {
  for (auto &column : headers) {
    widths.push_back(column.text().length());
  }
}

void Table::SetPadding(unsigned int n) { padding = n; }

void Table::SetLineSymbol(unsigned int n) {
  switch (n) {
    case 0:
      symbol = BasicSymbol;
      break;
    case 1:
      symbol = SingleLineSymbol;
      break;
    case 2:
      symbol = DoubleLineSymbol;
      break;
    case 3:
      symbol = InvisibleSymbol;
      break;
    default:
      symbol = BasicSymbol;
      break;
  }
}

void Table::SetLineStyle(OutlineStyle line_style) { style = line_style; }

bool Table::AddRow(std::vector<Text> row) {
  if (row.size() > widths.size()) {
    throw std::invalid_argument{
        "Appended row size must be same as header size"};
  }

  auto r = std::vector<Text>{row};
  rows.push_back(r);
  for (unsigned int i = 0; i < r.size(); ++i) {
    widths[i] = std::max(r[i].text().length(), widths[i]);
  }
  return true;
}

bool Table::RemoveRow(unsigned int index) {
  if (index > rows.size()) return false;

  rows.erase(rows.begin() + index);
  return true;
}

Table &Table::operator+=(std::vector<Text> row) {
  if (row.size() > widths.size()) {
    throw std::invalid_argument{
        "Appended row size must be same as header size"};
  }

  AddRow(row);
  return *this;
}

Table &Table::operator-=(const uint32_t rowIndex) {
  if (rows.size() < rowIndex)
    throw std::out_of_range{"Row index out of range."};

  RemoveRow(rowIndex);
  return *this;
}

std::string Table::GetLine(RowType rowType, Style rowStyle) const {
  std::stringstream line;
  line << Text().text(rowType.left).style(rowStyle);
  for (unsigned int i = 0; i < widths.size(); ++i) {
    for (unsigned int j = 0; j < (widths[i] + padding + padding); ++j) {
      line << Text().text(symbol.horizontal).style(rowStyle);
    }
    line << (i == widths.size() - 1
                 ? Text().text(rowType.right).style(rowStyle)
                 : Text().text(rowType.intersect).style(rowStyle));
  }
  return line.str() + "\n";
}

std::string Table::GetHeaders(Headers headers) const {
  std::stringstream line;
  line << Text().text(symbol.vertical).style(style.vertical);
  for (unsigned int i = 0; i < headers.size(); ++i) {
    Text text = headers[i];
    line << SPACE_CHARACTER * padding << text
         << SPACE_CHARACTER * (widths[i] - text.text().length())
         << SPACE_CHARACTER * padding
         << Text().text(symbol.vertical).style(style.vertical);
  }
  line << "\n";
  return line.str();
}

std::string Table::GetRows(Rows rows) const {
  std::stringstream line;
  for (auto &row : rows) {
    line << Text().text(symbol.vertical).style(style.vertical);
    for (unsigned int j = 0; j < row.size(); ++j) {
      Text text = row[j];
      line << SPACE_CHARACTER * padding << text
           << SPACE_CHARACTER * (widths[j] - text.text().length())
           << SPACE_CHARACTER * padding
           << Text().text(symbol.vertical).style(style.vertical);
    }
    line << "\n";
  }

  return line.str();
}

std::ostream &operator<<(std::ostream &out, const Table &table) {
  out << table.GetLine(table.symbol.top, table.style.top);
  out << table.GetHeaders(table.headers);
  out << table.GetLine(table.symbol.middle, table.style.middle);
  out << table.GetRows(table.rows);
  out << table.GetLine(table.symbol.bottom, table.style.bottom);
  return out;
}

bool Table::Sort(bool ascending) {
  if (ascending)
    std::sort(rows.begin(), rows.end(),
              [](std::vector<Text> a, std::vector<Text> b) {
                return a[0].text() > b[0].text();
              });
  else
    std::sort(rows.begin(), rows.end(),
              [](std::vector<Text> a, std::vector<Text> b) {
                return b[0].text() > a[0].text();
              });
  return true;
}

void Table::UpdateRow(unsigned int row, unsigned int header, std::string data) {
  if (row > rows.size() - 1) throw std::out_of_range{"Row index out of range."};
  if (header > headers.size() - 1)
    throw std::out_of_range{"Header index out of range."};

  rows[row][header] = data;
}

void Table::UpdateHeader(unsigned int header, std::string text) {
  if (header > headers.size())
    throw std::out_of_range{"Header index out of range."};

  headers[header] = text;
}

std::string operator*(const std::string &other, int repeats) {
  std::string ret;
  ret.reserve(other.size() * repeats);
  for (; repeats; --repeats) ret.append(other);
  return ret;
}
}  // namespace please