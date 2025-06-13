#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
#include "LinearSystem.hpp"

static std::vector<std::string> split(const std::string &s, char delim=',') {
    std::vector<std::string> tok; std::stringstream ss(s); std::string x;
    while (std::getline(ss, x, delim)) tok.push_back(x);
    return tok;
}

int main() {
    std::ifstream fin("machine.data");
    if (!fin) {
        std::cerr << "machine.data not found. Download it and place next to executable.\n";
        return 1;
    }

    std::vector<Vector> rows; std::vector<double> y;
    std::string line;
    while (std::getline(fin, line)) {
        auto t = split(line, ','); if (t.size() < 10) continue;
        Vector v(6);
        for (int i = 0; i < 6; ++i) v[i] = std::stod(t[2 + i]); // cols 3-8
        rows.push_back(v);
        y.push_back(std::stod(t[8])); // PRP
    }

    std::size_t N = rows.size();
    std::size_t trainN = N * 8 / 10;
    std::vector<std::size_t> idx(N); for (std::size_t i = 0; i < N; ++i) idx[i] = i;
    std::mt19937 rng(42); std::shuffle(idx.begin(), idx.end(), rng);

    Matrix Xtr(trainN, 6); Vector ytr(trainN);
    Matrix Xte(N - trainN, 6); Vector yte(N - trainN);

    for (std::size_t i = 0; i < trainN; ++i) {
        const auto &r = rows[idx[i]];
        for (std::size_t j = 1; j <= 6; ++j) Xtr(i + 1, j) = r[j - 1];
        ytr[i] = y[idx[i]];
    }
    for (std::size_t i = trainN; i < N; ++i) {
        const auto &r = rows[idx[i]];
        for (std::size_t j = 1; j <= 6; ++j) Xte(i - trainN + 1, j) = r[j - 1];
        yte[i - trainN] = y[idx[i]];
    }

    Vector beta = Xtr.pseudoInverse() * ytr;
    std::cout << "beta = " << beta << "\n";

    // Calculate Train RMSE
    Vector pred_train = Xtr * beta;
    double mse_train = 0.0;
    for (std::size_t i = 0; i < pred_train.size(); ++i) {
        double d = pred_train[i] - ytr[i]; mse_train += d * d;
    }
    double rmse_train = std::sqrt(mse_train / pred_train.size());
    std::cout << "Train RMSE = " << rmse_train << "\n";

    // Calculate Test RMSE
    Vector pred = Xte * beta;
    double mse = 0.0;
    for (std::size_t i = 0; i < pred.size(); ++i) {
        double d = pred[i] - yte[i]; mse += d * d;
    }
    double rmse = std::sqrt(mse / pred.size());
    std::cout << "Test RMSE = " << rmse << "\n";
    return 0;
} 