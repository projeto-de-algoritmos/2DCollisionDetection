#ifndef _VECTOR2D_HPP_
#define _VECTOR2D_HPP_

class Vector2D
{
public:
    Vector2D(double x = 0.0, double y = 0.0);
    Vector2D(const Vector2D & v);
    Vector2D(const Vector2D && v);

    double x() const noexcept;
    double y() const noexcept;
    double x(double t_x) noexcept;
    double y(double t_y) noexcept;

    double magnitude() const noexcept;
    double innerProduct(const Vector2D & v) const noexcept;

    Vector2D & operator=(const Vector2D & v) noexcept;
    Vector2D & operator=(const Vector2D && v) noexcept;

    Vector2D operator*(double k) const noexcept;

    Vector2D operator+(const Vector2D & v) const noexcept;
    Vector2D operator+(const Vector2D && v) const noexcept;

private:
    double _x;
    double _y;

protected:

};

#endif