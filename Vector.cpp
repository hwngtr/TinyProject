#include "Vector.hpp"
#include <algorithm>

Vector::Vector(std::size_t size) : mSize(size) {
    assert(size > 0);
    mData = new double[mSize]();
}

Vector::Vector(const Vector &other) : Vector(other.mSize) {
    std::copy(other.mData, other.mData + mSize, mData);
}

Vector &Vector::operator=(const Vector &other) {
    if (this == &other) return *this;
    if (mSize != other.mSize) {
        delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
    }
    std::copy(other.mData, other.mData + mSize, mData);
    return *this;
}

Vector::~Vector() { delete[] mData; }

double &Vector::operator[](std::size_t idx) {
    assert(idx < mSize);
    return mData[idx];
}

const double &Vector::operator[](std::size_t idx) const {
    assert(idx < mSize);
    return mData[idx];
}

double &Vector::operator()(std::size_t idx) {
    assert(idx > 0 && idx <= mSize);
    return mData[idx - 1];
}

const double &Vector::operator()(std::size_t idx) const {
    assert(idx > 0 && idx <= mSize);
    return mData[idx - 1];
}

std::ostream &operator<<(std::ostream &os, const Vector &v) {
    os << "[";
    for (std::size_t i = 0; i < v.mSize; ++i) {
        os << v.mData[i];
        if (i + 1 < v.mSize) os << ", ";
    }
    os << "]";
    return os;
}

Vector Vector::operator+(const Vector &rhs) const {
    assert(mSize == rhs.mSize);
    Vector res(mSize);
    for (std::size_t i = 0; i < mSize; ++i) res.mData[i] = mData[i] + rhs.mData[i];
    return res;
}

Vector Vector::operator-(const Vector &rhs) const {
    assert(mSize == rhs.mSize);
    Vector res(mSize);
    for (std::size_t i = 0; i < mSize; ++i) res.mData[i] = mData[i] - rhs.mData[i];
    return res;
}

Vector Vector::operator-() const {
    Vector res(mSize);
    for (std::size_t i = 0; i < mSize; ++i) res.mData[i] = -mData[i];
    return res;
}

Vector Vector::operator*(double s) const {
    Vector res(mSize);
    for (std::size_t i = 0; i < mSize; ++i) res.mData[i] = mData[i] * s;
    return res;
}

Vector &Vector::operator+=(const Vector &rhs) {
    assert(mSize == rhs.mSize);
    for (std::size_t i = 0; i < mSize; ++i) mData[i] += rhs.mData[i];
    return *this;
}

Vector &Vector::operator-=(const Vector &rhs) {
    assert(mSize == rhs.mSize);
    for (std::size_t i = 0; i < mSize; ++i) mData[i] -= rhs.mData[i];
    return *this;
}

Vector &Vector::operator*=(double s) {
    for (std::size_t i = 0; i < mSize; ++i) mData[i] *= s;
    return *this;
}

double Vector::dot(const Vector &rhs) const {
    assert(mSize == rhs.mSize);
    double sum = 0.0;
    for (std::size_t i = 0; i < mSize; ++i) sum += mData[i] * rhs.mData[i];
    return sum;
}

Vector operator*(double s, const Vector &v) {
    return v * s;
} 