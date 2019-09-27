#include "vector.h"

using namespace std;

// Overload the assignment (=) operator to assign Vector types
Vector &Vector::operator = (const Vector &obj)
{
    /// check for self-assignment
    if (this == &obj) {
        return *this;
    }

    /// make assignments
    x = obj.x;
    y = obj.y;
    z = obj.z;

    /// return reference to itself
    return *this;
}

// Assign the Vector to the zero vector
void Vector::Zero()
{
    x = 0;
    y = 0;
    z = 0;
}

// Overload the equality (==) operator to compare Vector types
bool Vector::operator == (const Vector &obj) const
{
    return (x - obj.x < 0.0001) && (y - obj.y < 0.0001) && (z - obj.z < 0.0001);
}

// Negate the vector
Vector Vector::operator -() const
{
    return Vector(-x, -y, -z);
}

// Overload the addition (+) operator to add vectors
Vector Vector::operator +(const Vector &obj) const
{
    return Vector(x + obj.x, y + obj.y, z + obj.z);
}

// Overload the subtraction (-) operator to subtract vectors
Vector Vector::operator -(const Vector &obj) const
{
    return Vector(x - obj.x, y - obj.x, z- obj.x);
}

// Overload the multiplication (*) operator to perform scalar multiplication on vectors
Vector Vector::operator *(float obj) const
{
    return Vector(x * obj, y * obj, z * obj);
}

// Overload the division (/) operator to perform division by scalar
Vector Vector::operator /(float obj) const
{
    return Vector(x / obj, y / obj, z / obj);
}

// Normal a given vector
void Vector::Normalize()
{
    float magnitude = Vector(x, y, z).VectorMag();

    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

// Overload the multiplication (*) operator for dot product calculations
float Vector::operator *(const Vector &obj) const
{
    return (x * obj.x) + (y * obj.y) + (z * obj.z);
}

// Compute the cross product of two given vectors
Vector Vector::CrossProduct(const Vector &obj)
{
    return Vector(y*obj.z - obj.y*z, obj.x*z - x*obj.x,x*obj.y - obj.x*y);
}

// Calculates the magnitude of a given vector
float Vector::VectorMag()
{
    return sqrt(x*x + y*y + z*z);
}

// Overload the output (<<) operator for output to standard display (friend function)
std::ostream& operator<< (std::ostream&, const Vector &obj)
{
    return cout << obj.x << "x + " << obj.y << "y + " << obj.z << "z" << endl;
}
