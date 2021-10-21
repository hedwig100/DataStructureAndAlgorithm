#include <cassert> 
#include <stdio.h>
#include "simplex.hpp" 

void test1() {
    int n = 2; 
    int m = 3; 
    std::vector<std::vector<double>> A(m,std::vector<double>(n)); 
    std::vector<double> b(m),c(n); 

    A = {
        {1,1},
        {2,0},
        {2,1} 
    }; 

    b = {4,5,7}; 

    c = {3,2}; 

    Dictionary dic(A,b,c,MaxCoefficient);
    OptimalSolution sol = dic.solve(); 
    printf("sol = %d\n",sol);
    assert(sol == Exist);
    auto answer = dic.answer();
    printf("ans ["); 
    for (int i = 0;i < n;i++) {
        printf("%lf ",answer[i]); 
    }
    printf("]\n");
    assert(answer[0] == 2.5 && answer[1] == 1.5); 
}

void test2() {
    int n = 2; 
    int m = 3; 
    std::vector<std::vector<double>> A(m,std::vector<double>(n)); 
    std::vector<double> b(m),c(n); 

    A = {
        {60,40},
        {20,30},
        {20,10} 
    }; 

    b = {3800,2100,1200}; 

    c = {400,300}; 

    Dictionary dic(A,b,c,MaxCoefficient);
    OptimalSolution sol = dic.solve(); 
    printf("sol = %d\n",sol);
    assert(sol == Exist);
    auto answer = dic.answer();
    printf("ans ["); 
    for (int i = 0;i < n;i++) {
        printf("%lf ",answer[i]); 
    }
    printf("]\n");
    assert(answer[0] == 30 && answer[1] == 50); 
}


void test3() {
    int n = 2; 
    int m = 3; 
    std::vector<std::vector<double>> A(m,std::vector<double>(n)); 
    std::vector<double> b(m),c(n); 

    A = {
        {-2,1},
        {1,-1},
        {-1,1} 
    }; 

    b = {1,2,3}; 

    c = {3,2}; 

    Dictionary dic(A,b,c,Bland);
    OptimalSolution sol = dic.solve(); 
    printf("sol = %d\n",sol);
    assert(sol == Unbounded); 
}

int main() {
    test1();
    test2(); 
    test3();
    return 0;
}