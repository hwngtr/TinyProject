#include "LinearSystem.hpp"
#include <cmath>

LinearSystem::LinearSystem(const Matrix &A, const Vector &b) : mA(A), mb(b) {
    assert(A.rows() == A.cols());
    assert(A.rows() == b.size());
}

Vector LinearSystem::Solve() const {
    std::size_t n = mA.rows();
    Matrix M = mA; 
    Vector x = mb; 
    // forward elimination
    for (std::size_t k = 1; k <= n; ++k) {
        double pivot = M(k,k);
        assert(pivot != 0.0);
        for (std::size_t j = k; j <= n; ++j) M(k,j) /= pivot;
        x(k) /= pivot;
        for (std::size_t i = k+1; i <= n; ++i) {
            double factor = M(i,k);
            for (std::size_t j = k; j <= n; ++j) M(i,j) -= factor * M(k,j);
            x(i) -= factor * x(k);
        }
    }
    // back substitution
    Vector sol(n);
    for (int i = static_cast<int>(n); i >= 1; --i) {
        double sum = 0.0;
        for (std::size_t j = i+1; j <= n; ++j) sum += M(i,j) * sol[j-1];
        sol[i-1] = x(i) - sum;
    }
    return sol;
}

PosSymLinSystem::PosSymLinSystem(const Matrix &A, const Vector &b) : LinearSystem(A, b) {
    // check symmetry
    for (std::size_t i = 1; i <= mA.rows(); ++i)
        for (std::size_t j = i + 1; j <= mA.cols(); ++j)
            assert(std::abs(mA(i, j) - mA(j, i)) < 1e-12);
}

Vector PosSymLinSystem::Solve() const {
    std::size_t n = mA.rows();
    Vector x(n); // initial zero
    Vector r = mb; // since x=0
    Vector p = r;
    double rsold = r.dot(r);
    for (std::size_t iter = 0; iter < n * 2; ++iter) { // max 2n iterations
        Vector Ap = mA * p;
        double alpha = rsold / p.dot(Ap);
        x += p * alpha;
        r -= Ap * alpha;
        double rsnew = r.dot(r);
        if (std::sqrt(rsnew) < 1e-10) break;
        p = r + p * (rsnew / rsold);
        rsold = rsnew;
    }
    return x;
} 