# TinyProject1 

### Description
* **Project**: A linear regression model to predict computer performance based on hardware specifications. 
* **Target Variable**: Published Relative Performance (PRP). 
* **Features**: MYCT, MMIN, MMAX, CACH, CHMIN, and CHMAX. 

### Prerequisites
* C++17 compatible compiler (e.g., `g++`). 
* `make` utility. 

### How to Use

1.  **Compile**
    ```bash
    make
    ```
    * This compiles all source files into an executable named `simple_demo`. 

2.  **Execute**
    ```bash
    ./simple_demo
    ```
    * Note: The `machine.data` file must be present in the same directory. 

3.  **Clean**
    ```bash
    make clean
    ```
    * This removes compiled object files and the executable. 

### Expected Output

beta = [-0.0328068, 0.0145806, 0.00387422, 0.706114, -1.17751, 1.59151] //
Train RMSE = 70.509 // 
Test RMSE = 44.208 
