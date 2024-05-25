#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>
#include <functional>
#include <limits>
#include "number_format.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc != 2)
  {
    std::cerr << "Wrong CLA's number\n";
    return 1;
  }
  std::string format_arg(argv[1]);
  numformat_t used_numformat = NUMBER;
  if (format_arg.substr(0, 12) == "--numformat=")
  {
    std::map< std::string, numformat_t > format;
    format["NUMBER"] = NUMBER;
    format["PROPORTION"] = PROPORTION;
    format["FRACTIONAL"] = FRACTIONAL;
    format["PERCENTAGE"] = PERCENTAGE;
    try
    {
      used_numformat = format.at(format_arg.substr(12));
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "Wrong number format\n";
      return 2;
    }
    std::cout << NumberFormat{ 1, 25, used_numformat } << "\n";
  }
  else
  {
    std::cerr << "Wrong CLA to identify numformat\n";
    return 3;
  }
  std::fstream file("~/input.txt");
  using command_func = std::function< void(std::istream &, std::ostream &) >;
  std::map< std::string, command_func > command;
  {
    using namespace std::placeholders;
  }
  std::string command_name;
  std::cin >> command_name;
  while (!std::cin.eof())
  {
    try
    {
      command.at(command_name)(std::cin, std::cout);
    }
    catch (const std::exception & e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cin >> command_name;
  }
  file.close();
  return 0;
}
