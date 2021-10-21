#include <cassert> 
#include <cmath> 
#include <stdio.h>
#include "simplex.hpp" 

const float EPS = 1e-10;
bool near(float x,float y) {
    return std::abs(x - y) < EPS; 
}
bool near(std::vector<double> x,std::vector<double> y) {
    bool ans = true; 
    for (int i = 0;i < (int)x.size();i++) {
        ans &= near(x[i],y[i]); 
    }
    return ans; 
}

void test1() {
    int n = 2; 
    int m = 3; 
    std::vector<std::vector<double>> A(m,std::vector<double>(n)); 
    std::vector<double> b(m),c(n),ans(n); 

    A = {
        {1,1},
        {2,0},
        {2,1} 
    }; 

    b = {4,5,7}; 

    c = {3,2}; 

    ans = {2.5,1.5}; 

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
    assert(near(answer,ans)); 
}

void test2() {
    int n = 2; 
    int m = 3; 
    std::vector<std::vector<double>> A(m,std::vector<double>(n)); 
    std::vector<double> b(m),c(n),ans(n); 

    A = {
        {60,40},
        {20,30},
        {20,10} 
    }; 

    b = {3800,2100,1200}; 

    c = {400,300}; 

    ans = {30,50}; 

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
    assert(near(answer,ans)); 
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

void test4() {
    int n = 2; 
    int m = 4; 
    std::vector<std::vector<double>> A(m,std::vector<double>(n)); 
    std::vector<double> b(m),c(n),ans(n); 

    A = {
        {2,3},
        {-5,9},
        {5,-9},
        {6,-3},
    }; 

    b = {6,15,-15,-3}; 

    c = {-6,6};

    ans = {0,(double)5/3}; 

    Dictionary dic(A,b,c,Bland);
    OptimalSolution sol = dic.find_feasible(); 
    assert(sol == Exist); 
    sol = dic.solve(); 
    printf("sol = %d\n",sol);
    assert(sol == Exist);
    auto answer = dic.answer(); 
    printf("ans ["); 
    for (int i = 0;i < n;i++) {
        printf("%lf ",answer[i]); 
    }
    printf("]\n");
    assert(near(ans,answer));
}

void test5() {
    int n = 3; 
    int m = 4; 
    std::vector<std::vector<double>> A(m,std::vector<double>(n)); 
    std::vector<double> b(m),c(n),ans(n); 

    A = {
        {-1,1,1},
        {2,1,-1},
        {-2,-1,1},
        {-1,-2,1},
    }; 

    b = {2,8,-8,-1}; 

    c = {1,3,5};

    ans = {8,1,9}; 

    Dictionary dic(A,b,c,Bland);
    OptimalSolution sol = dic.find_feasible(); 
    assert(sol == Exist); 
    sol = dic.solve(); 
    printf("sol = %d\n",sol);
    assert(sol == Exist);
    auto answer = dic.answer(); 
    printf("ans ["); 
    for (int i = 0;i < n;i++) {
        printf("%lf ",answer[i]); 
    }
    printf("]\n");
    assert(near(ans,answer));
}

int main() {
    test1();
    test2(); 
    test3();
    test4(); 
    test5();
    return 0;
}