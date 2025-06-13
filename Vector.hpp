#ifndef SIMPLE_VECTOR_HPP
#define SIMPLE_VECTOR_HPP

#include <cassert>
#include <cstddef>
#include <iostream>

class Vector {
private:
    std::size_t mSize{0};
    double *mData{nullptr};
public:
    // constructors and destructor
    explicit Vector(std::size_t size);
    Vector(const Vector &other);
    Vector &operator=(const Vector &other);
    ~Vector();

    std::size_t size() const { return mSize; }

    // element access (0-based and 1-based)
    double &operator[](std::size_t idx);
    const double &operator[](std::size_t idx) const;
    double &operator()(std::size_t idx);
    const double &operator()(std::size_t idx) const;


    // arithmetic operators
    Vector operator+(const Vector &rhs) const;
    Vector operator-(const Vector &rhs) const;
    Vector operator-() const; // unary minus
    Vector operator*(double s) const; // scale

    Vector &operator+=(const Vector &rhs);
    Vector &operator-=(const Vector &rhs);
    Vector &operator*=(double s);

    double dot(const Vector &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Vector &v);
    friend Vector operator*(double s, const Vector &v);
};

#endif 