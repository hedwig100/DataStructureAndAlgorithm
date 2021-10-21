#include "simplex.hpp"

Dictionary::Dictionary(
    std::vector<std::vector<double>> A, 
    std::vector<double> b,
    std::vector<double> c,
    PivotSelection pivot_selection
    ) :A(A),b(b),c(c),pivot_selection(pivot_selection) {
    n = (int)c.size(); 
    m = (int)b.size(); 
    nonbasis_index.resize(n); 
    basis_index.resize(m); 
    
    for (int i = 0;i < n;i++) nonbasis_index[i] = i; 
    for (int i = 0;i < m;i++) basis_index[i] = i + n;
    ans = 0.0;
}

void Dictionary::print_state(void) {
    printf("maximize: %lf",ans); 
    for (int i = 0;i < n;i++) {
        printf(" + %lfx_%d",c[i],nonbasis_index[i]+1); 
    }
    printf("\n"); 

    printf("s.t. ");
    for (int i = 0;i < m;i++) {
        if (i == 0) printf("x%d = %lf",basis_index[i]+1,b[i]); 
        else printf("     x%d = %lf",basis_index[i]+1,b[i]); 
        for (int j = 0;j < n;j++) {
            printf(" - %lfx%d",A[i][j],nonbasis_index[j]+1); 
        }
        printf("\n"); 
    }
}

int Dictionary::pick_nonbasis_pivot(void) {
    int nonbasis_pivot = -1;
    for (int i = 0;i < n;i++) {
        if (c[i] > 0) {
            nonbasis_pivot = i;
            if (pivot_selection == Bland) break;
            else if (pivot_selection == MaxCoefficient && c[i] > c[nonbasis_pivot]) {
                nonbasis_pivot = i; 
            }  
        }
    }
    return nonbasis_pivot; 
}

int Dictionary::pick_basis_pivot(int nonbasis_pivot) {
    int basis_pivot = -1;
    double min_ratio = -1;
    for (int i = 0;i < m;i++) {
        if (A[i][nonbasis_pivot] > 0) {
            if (basis_pivot < 0 || min_ratio > b[i]/A[i][nonbasis_pivot]) {
                basis_pivot = i; 
                min_ratio = b[i]/A[i][nonbasis_pivot];
            }
        }
    }
    return basis_pivot; 
}

void Dictionary::pivot_operation(int nonbasis_pivot,int basis_pivot) {
    double a; 

    // basis_pivot constraint 
    a = A[basis_pivot][nonbasis_pivot];
    b[basis_pivot] /= a; 
    for (int i = 0;i < n;i++) {
        if (i == nonbasis_pivot) continue; 
        A[basis_pivot][i] /= a; 
    }
    A[basis_pivot][nonbasis_pivot] = 1/a; 

    // substitution to other equation
    for (int i = 0;i < m;i++) {
        if (i == basis_pivot) continue;
        a = A[i][nonbasis_pivot]; 
        b[i] -= A[i][nonbasis_pivot]*b[basis_pivot]; 
        for (int j = 0;j < n;j++) {
            if (j != nonbasis_pivot) {
                A[i][j] -= A[basis_pivot][j]*a; 
            } else {
                A[i][j] = -A[basis_pivot][j]*a;
            }
        }
    }

    // object function 
    ans += b[basis_pivot]*c[nonbasis_pivot]; 
    a = c[nonbasis_pivot]; 
    for (int j = 0;j < n;j++) {
        if (j != nonbasis_pivot) {
            c[j] -= A[basis_pivot][j]*a; 
        } else {
            c[j] = -A[basis_pivot][j]*a; 
        }
    }
    
    std::swap(basis_index[basis_pivot],nonbasis_index[nonbasis_pivot]);
}

OptimalSolution Dictionary::pivot_step() {
    int nonbasis_pivot = pick_nonbasis_pivot(); 
    if (nonbasis_pivot < 0) {
        return Exist; // optimal solution
    }
    int basis_pivot = pick_basis_pivot(nonbasis_pivot);
    if (basis_pivot < 0) {
        return Unbounded; // unbounded
    }
    pivot_operation(nonbasis_pivot,basis_pivot); 
    return Continue; 
}

OptimalSolution Dictionary::solve() {
    OptimalSolution solution; 
    int step = 0;
    while (true) {
        printf("\nstep %d\n",++step);
        print_state(); 
        OptimalSolution tmp_solution = pivot_step(); 
        if (tmp_solution == Exist) {
            solution = Exist; 
            break; 
        } else if (tmp_solution == Unbounded) {
            solution = Unbounded;
            break; 
        } else if (tmp_solution == Continue) {
            continue; 
        }
    }
    return solution; 
}

std::vector<double> Dictionary::answer() {
    std::vector<double> ans(n,0); 
    for (int i = 0;i < m;i++) {
        if (basis_index[i] < n) {
            ans[basis_index[i]] = b[i];
        }
    } 
    return ans;
}