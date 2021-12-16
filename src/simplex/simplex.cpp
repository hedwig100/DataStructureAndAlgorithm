#include "simplex.hpp"

const double EPS = 1e-6; 

Dictionary::Dictionary(
    std::vector<std::vector<double>> A, 
    std::vector<double> b,
    std::vector<double> c,
    PivotSelection pivot_selection,
    bool verbose
    ) :A(A),b(b),c(c),pivot_selection(pivot_selection),verbose(verbose) {
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
        printf(" %c %lfx_%d",(c[i] > 0 ? '+' : '-'),std::abs(c[i]),nonbasis_index[i]+1); 
    }
    printf("\n"); 

    printf("s.t. ");
    for (int i = 0;i < m;i++) {
        if (i == 0) printf("x%d = %lf",basis_index[i]+1,b[i]); 
        else printf("     x%d = %lf",basis_index[i]+1,b[i]); 
        for (int j = 0;j < n;j++) {
            printf(" %c %lfx%d",(A[i][j] > 0 ? '-' : '+'),std::abs(A[i][j]),nonbasis_index[j]+1); 
        }
        printf("\n"); 
    }
}

int Dictionary::pick_nonbasis_pivot(void) {
    int nonbasis_pivot = -1;
    for (int i = 0;i < n;i++) {
        if (c[i] > EPS) {
            if (nonbasis_pivot < 0) {
                nonbasis_pivot = i;
            } else if (pivot_selection == Bland && nonbasis_index[i] < nonbasis_index[nonbasis_pivot]) {
                nonbasis_pivot = i; 
            } else if (pivot_selection == MaxCoefficient && c[i] > c[nonbasis_pivot]) {
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
        if (A[i][nonbasis_pivot] > EPS) {
            if (basis_pivot < 0 || min_ratio > b[i]/A[i][nonbasis_pivot]) {
                basis_pivot = i; 
                min_ratio = b[i]/A[i][nonbasis_pivot];
            } else if (min_ratio*A[i][nonbasis_pivot] == b[i] && basis_index[i] < basis_index[basis_pivot]) {
                basis_pivot = i; 
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
        b[i] -= b[basis_pivot]*a; 
        for (int j = 0;j < n;j++) {
            if (j == nonbasis_pivot) continue;
            A[i][j] -= A[basis_pivot][j]*a;
        }
        A[i][nonbasis_pivot] = -A[basis_pivot][nonbasis_pivot]*a;
    }

    // object function 
    a = c[nonbasis_pivot]; 
    ans += b[basis_pivot]*a; 
    for (int j = 0;j < n;j++) {
        if (j == nonbasis_pivot) continue; 
        c[j] -= A[basis_pivot][j]*a; 
    }
    c[nonbasis_pivot] = -A[basis_pivot][nonbasis_pivot]*a; 
    
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

void Dictionary::add_artificial_variable(int basis_pivot) {
    for (int i = 0;i < m;i++) {
        A[i].push_back(-1.0); 
    } 

    for (int i = 0;i < n;i++) {
        c[i] = 0.0;
    }
    c.push_back(-1.0); 

    n++;
    nonbasis_index.push_back(n+m-1);

    // first step to get a feasible dictionary 
    if (verbose) {
        printf("\nInitial state\n");
        print_state(); 
    }
    pivot_operation(n-1,basis_pivot); 
}

void Dictionary::delete_artificial_variable() {
    int artificial_pivot = -1;
    for (int i = 0;i < m;i++) {
        if (basis_index[i] == n+m-1) {
            artificial_pivot = i; 
            break; 
        }
    }
    if (artificial_pivot >= 0) {
        pivot_operation(n-1,artificial_pivot); 
    } else {
        for (int i = 0;i < n;i++) {
            if (nonbasis_index[i] == n+m-1) {
                artificial_pivot = i;
                break; 
            }
        }
        for (int i = 0;i < m;i++) {
            std::swap(A[i][artificial_pivot],A[i][n-1]); 
        }
        std::swap(nonbasis_index[artificial_pivot],nonbasis_index[n-1]); 
    }

    for (int i = 0;i < m;i++) {
        A[i].pop_back(); 
    }
    c.pop_back();
    nonbasis_index.pop_back(); 
    n--;
}

void Dictionary::construct_c(std::vector<double> before_c) {
    for (int i = 0;i < n;i++) {
        c[i] = 0.0;
    }
    ans = 0.0; 

    for (int i = 0;i < n;i++) {
        if (nonbasis_index[i] < n) {
            c[i] = before_c[nonbasis_index[i]]; 
        }
    }

    for (int i = 0;i < m;i++) {
        if (basis_index[i] < n) {
            for (int j = 0;j < n;j++) {
                c[j] -= before_c[basis_index[i]]*A[i][j]; 
            }
            ans += before_c[basis_index[i]]*b[i]; 
        }
    }
}

OptimalSolution Dictionary::find_feasible() {
    // check if dict now is feasible dict or not 
    double max_minus = 0.0; 
    int basis_pivot = -1;
    for (int i = 0;i < m;i++) {
        if (b[i] < max_minus) {
            max_minus = b[i]; 
            basis_pivot = i;
        }
    }
    if (basis_pivot < 0) {
        return Exist; // all b[i] >= 0,already feasible 
    }

    std::vector<double> before_c = c;
    add_artificial_variable(basis_pivot); 
    OptimalSolution sol = solve(); 
    if (sol != Exist || ans < -EPS) {
        return NoExist;
    }
    delete_artificial_variable(); 
    construct_c(before_c); 
    return Exist; 
}

OptimalSolution Dictionary::solve() {
    OptimalSolution solution; 
    int step = 0;
    while (true) {
        if (verbose) {
            printf("\nstep %d\n",++step);
            print_state(); 
        }
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