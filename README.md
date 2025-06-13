# TinyProject1: Linear Optimization

[cite_start]A C++ program that implements linear regression to predict computer performance based on hardware specifications[cite: 7]. [cite_start]The model predicts Published Relative Performance (PRP) using six hardware features: MYCT, MMIN, MMAX, CACH, CHMIN, and CHMAX[cite: 7, 8].

## How to Use

### Prerequisites
* [cite_start]A C++17 compatible compiler (e.g., `g++`)[cite: 46].
* [cite_start]The `make` utility[cite: 46].

### Compile
Navigate to the project directory and run:
```bash
make
```
[cite_start]This compiles the source files and creates an executable named `simple_demo`[cite: 46].

### Execute
To run the program, use the following command. [cite_start]The `machine.data` file must be in the same directory[cite: 48].
```bash
./simple_demo
```

### Expected Output
```
beta = [-0.0328068, 0.0145806, 0.00387422, 0.706114, -1.17751, 1.59151]
Train RMSE = 70.509
Test RMSE = 44.208
```

### Clean
To remove all compiled files:
```bash
make clean
```
