#include "Vector2D.hpp"
#include <cmath>

Vector2D::Vector2D(double x, double y):
_x(x),
_y(y)
{

}

Vector2D::Vector2D(const Vector2D & v):
_x(v.x()),
_y(v.y())
{

}

Vector2D::Vector2D(const Vector2D && v):
_x(v.x()),
_y(v.y())
{

}

double Vector2D::x() const noexcept
{
    return _x;
}

double Vector2D::y() const noexcept
{
    return _y;
}

double Vector2D::x(double t_x) noexcept
{
    return _x = t_x;
}

double Vector2D::y(double t_y) noexcept
{
    return _y = t_y;
}

double Vector2D::magnitude() const noexcept
{
    return sqrt(x() * x() + y() * y());
}

double Vector2D::innerProduct(const Vector2D & v) const noexcept
{
    return x() * v.x() + y() * v.y();
}

Vector2D & Vector2D::operator=(const Vector2D & v) noexcept
{
    x(v.x());
    y(v.y());
    return *this;
}

Vector2D & Vector2D::operator=(const Vector2D && v) noexcept
{
    x(v.x());
    y(v.y());
    return *this;
}

Vector2D Vector2D::operator*(double k) const noexcept
{
    return Vector2D(x() * k, y() * k);
}

Vector2D Vector2D::operator+(const Vector2D & v) const noexcept
{
    return Vector2D(x() + v.x(), y() + v.y());
}

Vector2D Vector2D::operator+(const Vector2D && v) const noexcept
{
    return Vector2D(x() + v.x(), y() + v.y());
}
