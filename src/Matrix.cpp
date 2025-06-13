#include "Matrix.hpp"
#include <algorithm>
#include <cmath>

// Private helpers
void Matrix::allocate(std::size_t r, std::size_t c) {
    mRows = r;
    mCols = c;
    mData = new double*[mRows];
    for (std::size_t i = 0; i < mRows; ++i) mData[i] = new double[mCols]();
}

void Matrix::deallocate() {
    if (mData) {
        for (std::size_t i = 0; i < mRows; ++i) delete[] mData[i];
        delete[] mData;
        mData = nullptr;
    }
    mRows = mCols = 0;
}

// Constructors / destructor 
Matrix::Matrix(std::size_t r, std::size_t c) {
    assert(r > 0 && c > 0);
    allocate(r, c);
}

Matrix::Matrix(const Matrix &other) {
    allocate(other.mRows, other.mCols);
    for (std::size_t i = 0; i < mRows; ++i)
        std::copy(other.mData[i], other.mData[i] + mCols, mData[i]);
}

Matrix &Matrix::operator=(const Matrix &other) {
    if (this == &other) return *this;
    deallocate();
    allocate(other.mRows, other.mCols);
    for (std::size_t i = 0; i < mRows; ++i)
        std::copy(other.mData[i], other.mData[i] + mCols, mData[i]);
    return *this;
}

Matrix::~Matrix() { deallocate(); }

// Element access 
double &Matrix::operator()(std::size_t i, std::size_t j) {
    assert(i > 0 && i <= mRows && j > 0 && j <= mCols);
    return mData[i - 1][j - 1];
}

const double &Matrix::operator()(std::size_t i, std::size_t j) const {
    assert(i > 0 && i <= mRows && j > 0 && j <= mCols);
    return mData[i - 1][j - 1];
}

// Arithmetic operators 
Matrix Matrix::operator+(const Matrix &rhs) const {
    assert(mRows == rhs.mRows && mCols == rhs.mCols);
    Matrix res(mRows, mCols);
    for (std::size_t i = 0; i < mRows; ++i)
        for (std::size_t j = 0; j < mCols; ++j)
            res.mData[i][j] = mData[i][j] + rhs.mData[i][j];
    return res;
}

Matrix Matrix::operator-(const Matrix &rhs) const {
    assert(mRows == rhs.mRows && mCols == rhs.mCols);
    Matrix res(mRows, mCols);
    for (std::size_t i = 0; i < mRows; ++i)
        for (std::size_t j = 0; j < mCols; ++j)
            res.mData[i][j] = mData[i][j] - rhs.mData[i][j];
    return res;
}

Matrix Matrix::operator*(double s) const {
    Matrix res(mRows, mCols);
    for (std::size_t i = 0; i < mRows; ++i)
        for (std::size_t j = 0; j < mCols; ++j)
            res.mData[i][j] = mData[i][j] * s;
    return res;
}

Matrix operator*(double s, const Matrix &M) { return M * s; }

Matrix Matrix::operator*(const Matrix &rhs) const {
    assert(mCols == rhs.mRows);
    Matrix res(mRows, rhs.mCols);
    for (std::size_t i = 0; i < mRows; ++i) {
        for (std::size_t k = 0; k < mCols; ++k) {
            double aik = mData[i][k];
            for (std::size_t j = 0; j < rhs.mCols; ++j) {
                res.mData[i][j] += aik * rhs.mData[k][j];
            }
        }
    }
    return res;
}

Vector Matrix::operator*(const Vector &v) const {
    assert(mCols == v.size());
    Vector res(mRows);
    for (std::size_t i = 0; i < mRows; ++i) {
        double sum = 0.0;
        for (std::size_t j = 0; j < mCols; ++j) sum += mData[i][j] * v[j];
        res[i] = sum;
    }
    return res;
}

Matrix &Matrix::operator+=(const Matrix &rhs) {
    assert(mRows == rhs.mRows && mCols == rhs.mCols);
    for (std::size_t i = 0; i < mRows; ++i)
        for (std::size_t j = 0; j < mCols; ++j)
            mData[i][j] += rhs.mData[i][j];
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &rhs) {
    assert(mRows == rhs.mRows && mCols == rhs.mCols);
    for (std::size_t i = 0; i < mRows; ++i)
        for (std::size_t j = 0; j < mCols; ++j)
            mData[i][j] -= rhs.mData[i][j];
    return *this;
}

Matrix &Matrix::operator*=(double s) {
    for (std::size_t i = 0; i < mRows; ++i)
        for (std::size_t j = 0; j < mCols; ++j)
            mData[i][j] *= s;
    return *this;
}

// Determinant via Gaussian elimination 
static double det_gauss(Matrix A) {
    assert(A.rows() == A.cols());
    std::size_t n = A.rows();
    double det = 1.0;
    for (std::size_t k = 1; k <= n; ++k) {
        // pivot row index
        std::size_t pivot = k;
        double maxval = std::abs(A(k, k));
        for (std::size_t i = k + 1; i <= n; ++i) {
            if (std::abs(A(i, k)) > maxval) { maxval = std::abs(A(i, k)); pivot = i; }
        }
        if (maxval == 0.0) return 0.0; // singular
        if (pivot != k) {
            for (std::size_t j = 1; j <= n; ++j) std::swap(A(k, j), A(pivot, j));
            det = -det;
        }
        det *= A(k, k);
        double akk = A(k, k);
        for (std::size_t i = k + 1; i <= n; ++i) {
            double factor = A(i, k) / akk;
            for (std::size_t j = k; j <= n; ++j) {
                A(i, j) -= factor * A(k, j);
            }
        }
    }
    return det;
}

double Matrix::determinant() const {
    assert(mRows == mCols);
    return det_gauss(*this);
}

Matrix Matrix::transpose() const {
    Matrix T(mCols, mRows);
    for (std::size_t i = 0; i < mRows; ++i)
        for (std::size_t j = 0; j < mCols; ++j)
            T.mData[j][i] = mData[i][j];
    return T;
}

// Inverse via Gauss–Jordan elimination
Matrix Matrix::inverse() const {
    assert(mRows == mCols);
    std::size_t n = mRows;
    Matrix aug(n, 2 * n);
    // build [A | I]
    for (std::size_t i = 1; i <= n; ++i) {
        for (std::size_t j = 1; j <= n; ++j) aug(i, j) = (*this)(i, j);
        for (std::size_t j = n + 1; j <= 2 * n; ++j) aug(i, j) = (i == (j - n)) ? 1.0 : 0.0;
    }
    // elimination
    for (std::size_t k = 1; k <= n; ++k) {
        // pivoting (partial)
        std::size_t pivot = k;
        double maxval = std::abs(aug(k, k));
        for (std::size_t i = k + 1; i <= n; ++i) {
            if (std::abs(aug(i, k)) > maxval) { maxval = std::abs(aug(i, k)); pivot = i; }
        }
        assert(maxval != 0.0);
        if (pivot != k) {
            for (std::size_t j = 1; j <= 2 * n; ++j) std::swap(aug(k, j), aug(pivot, j));
        }
        double pivotVal = aug(k, k);
        for (std::size_t j = 1; j <= 2 * n; ++j) aug(k, j) /= pivotVal;
        for (std::size_t i = 1; i <= n; ++i) {
            if (i == k) continue;
            double factor = aug(i, k);
            for (std::size_t j = 1; j <= 2 * n; ++j) aug(i, j) -= factor * aug(k, j);
        }
    }
    // extract inverse
    Matrix inv(n, n);
    for (std::size_t i = 1; i <= n; ++i)
        for (std::size_t j = 1; j <= n; ++j)
            inv(i, j) = aug(i, j + n);
    return inv;
}

Matrix Matrix::pseudoInverse(double lambda) const {
    Matrix At = transpose();
    Matrix AtA = At * (*this);
    if (lambda != 0.0) {
        for (std::size_t i = 1; i <= AtA.rows(); ++i) AtA(i, i) += lambda;
    }
    Matrix invAtA = AtA.inverse();
    return invAtA * At;
} 