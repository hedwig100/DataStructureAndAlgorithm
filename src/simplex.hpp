#include <vector>
#include <stdio.h>

typedef enum {
    Exist,
    NoExist,
    Unbounded,
    Continue,
} OptimalSolution;


struct Dictionary {
    int n; // number of variables
    int m; // number of constraint
    double ans; 
    std::vector<std::vector<double>> A;
    std::vector<double> b; // size m
    std::vector<double> c; // size n
    std::vector<int> nonbasis_index;  
    std::vector<int> basis_index;  

    Dictionary(std::vector<std::vector<double>> A, std::vector<double> b, std::vector<double> c); 
    void print_state(void); 
    int pick_nonbasis_pivot(void); 
    int pick_basis_pivot(int nonbasis_pivot); 
    void pivot_operation(int nonbasis_pivot,int basis_pivot); 
    OptimalSolution pivot_step(); 
    OptimalSolution solve(); 
    std::vector<double> answer(); 
};