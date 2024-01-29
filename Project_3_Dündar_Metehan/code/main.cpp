// HPC Class: Example of explicit matrix-free scheme for solving Heat Equation.
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

//Solves ∂s/∂t = αΔs ... this is not an HPC approach!
// Compile and run : g++ main.cpp; ./a.out

// TODO
// 1) What happens as you increase tau ?
// 2) See Courant-Friedrichs-Lewy (CFL) condition in https://people.math.ethz.ch/~grsam/SS21/NAII/resources/slides/ODE-Lecture6.pdf

#include <iostream>
#include <vector>

 int nx = 20;          // number of spatial grid points in x direction
 int ny = 20;          // number of spatial grid points in y direction
 double h = 0.01;      // spatial step size in x and y direction
 double tau = 0.0001;  // time step size
 double alpha = 0.1;   // thermal diffusivity
 int T = 500;          // number of time steps

/**
 * @brief Set the intial condtion (hotspt) and bound conditions (zero)
 * 
 * @param S Solution grid.
 */
void initialize(std::vector<std::vector<double>>& S) {
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            S[i][j] = 0.0;
            
            // Initial condition: set a hot spot in the center
            if (i > 1 && i < 5 && j > 1 && j < 5) {
                S[i][j] = 1.0;
            }
        }
    }
}

/**
 * @brief Updates the solution with the updated valued.
 * 
 * @param S Solution grid.
 */
void update(std::vector<std::vector<double>>& S) {
    
    std::vector<std::vector<double>> S_new(nx, std::vector<double>(ny));

    for (int i = 1; i < nx - 1; ++i) {
        for (int j = 1; j < ny - 1; ++j) {
            double temp = (- 4*S[i][j] + S[i+1][j] + S[i-1][j]  + S[i][j+1] + S[i][j-1]) / (h*h);
            S_new[i][j] = S[i][j] + alpha * tau * temp;
        }
    }

    S = S_new;
}

/**
 * @brief Convert real number range of [0,1] to ASCII
 * 
 * @param val Number of converted 
 * @return char ASCII charcater
 */
char ascii(double val) {
    if (val > 0.99) return '@';
    if (val > 0.8) return '#';
    if (val > 0.6) return '*';
    if (val > 0.4) return '+';
    if (val > 0.2) return ':';
    if (val > 1e-12) return '.';
    if (val < 1e-12) return 'O';
    return '?';
}

/**
 * @brief Prints the solution grid to the terminal
 * 
 * @param S Solution grid.
 * @param print_ascii Flag to print numerical values or ASCII representation.
 */
void print(std::vector<std::vector<double>>& S, bool print_ascii = true) {
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            if(print_ascii){
                std::cout << ascii(S[i][j]) << " ";
            }else{
                std::cout << S[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<double>> S(nx, std::vector<double>(ny));
    initialize(S);

    std::cout<<"###################"<<std::endl;
    std::cout<<"#Initial Condition#"<<std::endl;
    std::cout<<"###################"<<std::endl;
    print(S);
    std::cout<<"##############"<<std::endl;

    for (int t = 1; t < T; ++t) {
        
        update(S);
        
        // Print to scree, wait for key, than clear screen
        print(S);
        std::cout<< "Iter="<<t<<std::endl;
        std::cin.get();
        std::cout << "\033[H\033[2J\033[3J" ;
    }

    return 0;
}
