#ifndef INCLUDE_PLEASE_TABLE_H_
#define INCLUDE_PLEASE_TABLE_H_
#include <vector>

#include "color.h"
#include "style.h"
#include "task.h"
#include "term.h"
#include "text.h"

namespace please {
class Table {
 private:
  /// Defines row type
  struct RowType {
    std::string left;
    std::string intersect;
    std::string right;
  };

  /// Defines table symbol rows (top, middle, bottom etc)
  struct OutlineSymbol {
    std::string horizontal;
    std::string vertical;
    RowType top;
    RowType middle;
    RowType bottom;
  };

  struct OutlineStyle {
    Style header_vertical;
    Style content_vertical;
    Style top;
    Style middle;
    Style bottom;
  };

 public:
  typedef std::vector<Text> Headers;
  typedef std::vector<std::vector<Text>> Rows;
  typedef std::vector<std::size_t> Widths;

  /// Initialize a new Table
  /// \param headers Stringlist of the tables headers
  Table(std::vector<Text> headers);

  /// Sets the distance from the text to the cell border
  /// \param n Spaces between the text and the cell border
  void SetPadding(unsigned int n);

  /// Sets the symbol of the table, default is 0
  /// n = 0 : Basic table symbol
  /// n = 1 : Single lined table symbol
  /// n = 2 : Double lined table symbol
  /// n = 3 : Invisivle table lines symbol
  /// \param n The table symbol number
  void SetLineSymbol(unsigned int n);

  /// Sets style of horizontal symbol.
  void SetLineStyle(OutlineStyle style);

  /// Sorts the table rows based on the first column
  /// \param ascending Should table be sorted ascending or descending
  /// \return True if sorting was successful, otherwise false
  bool Sort(bool ascending);

  /// Adds a new row to the table
  /// \param row A list of strings to add as row
  /// \return True if the value was added successfully, otherwise false
  bool AddRow(std::vector<Text> row);

  /// Removes a row from the table by the row index
  /// \param index The index of the row that should be removed
  /// \return True if the row was removed successfully, otherwise false
  bool RemoveRow(unsigned int index);

  /// Update an existing table cell with new data
  /// \param row The index of the row that needs to be updated
  /// \param header The index of the column that needs to be updated
  /// \param data The new data that should be assigned to teh cell
  void UpdateRow(unsigned int row, unsigned int header, std::string data);

  /// Update a header with new text
  /// \param header Index of the header that should be updated
  /// \param text The new teext of the new header
  void UpdateHeader(unsigned int header, std::string text);

  /// Operator of the AddRow() function
  /// \param row A list of strings to add as row
  /// \return this
  Table &operator+=(std::vector<Text> row);

  /// Operator of the RemoveRow() function
  /// \param rowIndex The index of the row that should be removed
  /// \return this
  Table &operator-=(uint32_t rowIndex);

 private:
  /// Holds all header strings of the table
  Headers headers;

  /// Holds all rows of the table
  Rows rows;

  /// Holds the size of widest string of each column of the table
  Widths widths;

  /// Basic symbol - works on all systems, used as default symbol
  OutlineSymbol BasicSymbol = {
      "-", "|", {"+", "+", "+"}, {"+", "+", "+"}, {"+", "+", "+"}};

  /// Single lined symbol - requires speecial character support
  OutlineSymbol SingleLineSymbol = {
      "━", "┃", {"┏", "┳", "┓"}, {"┣", "╋", "┫"}, {"┗", "┻", "┛"}};

  /// Single double symbol - requires speecial character support
  OutlineSymbol DoubleLineSymbol = {
      "═", "║", {"╔", "╦", "╗"}, {"╠", "╬", "╣"}, {"╚", "╩", "╝"}};

  /// No visible table outlines - works on all systems
  OutlineSymbol InvisibleSymbol = {
      " ", " ", {" ", " ", " "}, {" ", " ", " "}, {" ", " ", " "}};

  /// Current table symbol
  OutlineSymbol symbol = BasicSymbol;

  /// Current table style
  OutlineStyle style = {
      Style().fg(Foreground::From(Color::CYAN)),
      Style().fg(Foreground::From(Color::RED)),
      Style().fg(Foreground::From(Color::BRIGHT_RED)),
      Style().fg(Foreground::From(Color::BRIGHT_RED)),
      Style().fg(Foreground::From(Color::RED)),
  };

  /// Space character constant
  const std::string SPACE_CHARACTER = " ";

  /// The distance between the cell text and the cell border
  unsigned int padding = 1;

  /// Returns a formatted horizontal separation line for the table
  /// \param rowType The type of the row (top, middle, bottom)
  /// \param style The style of the row (top, middle, bottom)
  /// \return The formatted row string
  std::string GetLine(RowType rowType, Style style) const;

  /// Returns a formatted header string
  /// \param headers The Headers-object that holds the header strings
  /// \return The formatted header string
  std::string GetHeaders(Headers headers) const;

  /// Returns a formmatted row string
  /// \param rows The Rows-object that holds all rows of the table
  /// \return A formatted string of all rows in the table
  std::string GetRows(Rows rows) const;

  /// Writes the entire table with all its contents in the output stream
  /// This can be used to display the table using the std::cout function
  /// \param out The output stream the table should be written to
  /// \param table The Table-object
  /// \return Output stream with the formatted table string
  friend std::ostream &operator<<(std::ostream &out, const Table &table);
};

/// Repeats a given string n times
/// \param other The string to repeat
/// \param repeats The amount the string should be repeated
/// \return The repeated string
std::string operator*(const std::string &other, int repeats);
}  // namespace please
#endif  // !INCLUDE_PLEASE_TABLE_H_