#ifndef SIMPLE_LINEARSYSTEM_HPP
#define SIMPLE_LINEARSYSTEM_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

class LinearSystem {
protected:
    Matrix mA;
    Vector mb;
private:
public:
    LinearSystem(const Matrix &A, const Vector &b);
    virtual Vector Solve() const; // Gaussian elimination with pivoting
};

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix &A, const Vector &b);
    Vector Solve() const override; // Conjugate Gradient
};

#endif 