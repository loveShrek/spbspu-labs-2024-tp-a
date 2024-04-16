#include "binType.hpp"

#include <stack>

#include "delimeter.hpp"
#include "streamGuard.hpp"

bool rebdev::BinTypeIO::operator==(const BinTypeIO & bin) const noexcept
{
  return data == bin.data;
}

bool rebdev::BinTypeIO::operator<(const BinTypeIO & bin) const noexcept
{
  return data < bin.data;
}

std::istream & rebdev::operator>>(std::istream & in, BinTypeIO && bin)
{
  std::istream::sentry sentryGuard(in);
  if (!sentryGuard)
  {
    return in;
  }

  unsigned long long dataCopy = bin.data;
  bin.data = 0;

  StreamGuard guard(in);

  in >> Delimeter{'0'} >> Delimeter{'b'};

  in >> std::noskipws;

  char numNow = 0;
  std::stack< char > reverseStr;

  in >> numNow;
  while ((numNow == '0') || (numNow == '1'))
  {
    try
    {
      reverseStr.push(numNow);
    }
    catch (...)
    {
      bin.data = dataCopy;
      throw;
    }

    in >> numNow;
  }

  unsigned long long pow = 1;
  size_t size = reverseStr.size();

  for (size_t i = 0; i < size; ++i)
  {
    bin.data += (reverseStr.top() - '0') * pow;
    pow *= 2;
    try
    {
      reverseStr.pop();
    }
    catch (...)
    {
      bin.data = dataCopy;
      throw;
    }
  }

  return in;
}

std::ostream & rebdev::operator<<(std::ostream & out, BinTypeIO && bin)
{
  std::ostream::sentry sentryGuard(out);
  if (!sentryGuard)
  {
    return out;
  }

  StreamGuard guard(out);

  out << "0b";

  std::stack< char > reverseBin;

  unsigned long long num = bin.data;

  for (size_t i = 0; (num > 0); ++i)
  {
    reverseBin.push(('0' + (num % 2)));
    num /= 2;
  }

  out << '0';

  size_t size = reverseBin.size();
  for (size_t i = 0; i < size; ++i)
  {
    out << reverseBin.top();
    reverseBin.pop();
  }

  return out;
}
