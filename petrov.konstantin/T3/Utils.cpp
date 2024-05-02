#include "Utils.hpp"
#include <math.h>
#include "Geometry.hpp"

double petrov::AccPolygonAreaPart::operator()(double area, const Point& p2, const Point& p3)
{
  area += std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}

double petrov::AccPolygonAreaEO(double area, const Polygon& polygon, bool isEven)
{
  if (isEven == (polygon.points.size() % 2 == 0))
  {
    area += getArea(polygon);
  }
  return area;
}