#include <stdio.h>
#include <vector>
#include <cmath> 

typedef enum {
    Exist,
    NoExist,
    Unbounded,
    Continue,
} OptimalSolution;

typedef enum {
    MaxCoefficient,
    // MaxGain, 
    Bland
} PivotSelection; 

struct Dictionary {
    int n; // number of variables
    int m; // number of constraint
    double ans; 
    std::vector<std::vector<double>> A;
    std::vector<double> b; // size m
    std::vector<double> c; // size n
    std::vector<int> nonbasis_index;  
    std::vector<int> basis_index;  
    PivotSelection pivot_selection; 
    bool verbose;

    Dictionary(std::vector<std::vector<double>> A, std::vector<double> b, std::vector<double> c,PivotSelection pivot_selection,bool verbose); 
    void print_state(void); 
    int pick_nonbasis_pivot(void); 
    int pick_basis_pivot(int nonbasis_pivot); 
    void pivot_operation(int nonbasis_pivot,int basis_pivot); 
    void add_artificial_variable(int basis_pivot); 
    void delete_artificial_variable(); 
    void construct_c(std::vector<double> before_c); 
    OptimalSolution pivot_step(); 
    OptimalSolution find_feasible(); 
    OptimalSolution solve(); 
    std::vector<double> answer(); 
};