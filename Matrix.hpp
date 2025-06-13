#ifndef SIMPLE_MATRIX_HPP
#define SIMPLE_MATRIX_HPP

#include <cassert>
#include <cstddef>
#include "Vector.hpp"

class Matrix {
private:
    std::size_t mRows{0}, mCols{0};
    double **mData{nullptr};
    void allocate(std::size_t r, std::size_t c);
    void deallocate();
public:
    Matrix(std::size_t r, std::size_t c);           // size constructor
    Matrix(const Matrix &other);                    // copy constructor
    Matrix &operator=(const Matrix &other);         // copy assignment
    ~Matrix();

    std::size_t rows() const { return mRows; }
    std::size_t cols() const { return mCols; }

    double &operator()(std::size_t i, std::size_t j);
    const double &operator()(std::size_t i, std::size_t j) const;

    // arithmetic operators
    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;
    Matrix operator*(double s) const;
    Matrix operator*(const Matrix &rhs) const;
    Vector operator*(const Vector &v) const;

    Matrix &operator+=(const Matrix &rhs);
    Matrix &operator-=(const Matrix &rhs);
    Matrix &operator*=(double s);

    // linear algebra helpers
    double determinant() const;
    Matrix inverse() const;
    Matrix transpose() const;
    Matrix pseudoInverse(double lambda = 0.0) const;

    friend Matrix operator*(double s, const Matrix &M);
};

#endif // SIMPLE_MATRIX_HPP 