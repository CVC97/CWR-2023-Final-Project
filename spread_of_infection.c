#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "cvc_numerics.h"
#include "cvc_rng.h"


// generate uniforms using static Mersenne-Twister MT19937 to reduce parameters
double random_uniform(void) {
    static gsl_rng* generator;
    if (!generator) {
        generator = gsl_rng_alloc(gsl_rng_mt19937);
    }
    return gsl_rng_uniform(generator);
}


// print out a given quadratic grid of sidelength 'length'
void print_grid(int *grid, int length) {
    printf("\n+++ print grid +++\n\n");
    for (int row_i = 0; row_i < length; row_i++) {
        for (int column_j = 0; column_j < length; column_j++) {
            int *node = &grid[row_i*length + column_j];
            if (*node == -1) {
                printf("V");
            } else {
                printf("%d", *node);
            }
        }
        printf("\n");
    }
    printf("\n+++ end of print +++\n");
    return;
}


// initialize the given 'grid' of 'length' (L+2) with integers 0 (susceptible S), 1 (infected I), 2 (recovered R) and -1 (vaccinated V)
void grid_init(int *grid, int length, double *probabilities) {
    double p4 = probabilities[3];                                               // caching the probability of someone being initialized as V                                      

    // iterating through the grid ignoring the borders
    for (int row_i = 1; row_i < length-1; row_i++) {
        for (int column_j = 1; column_j < length-1; column_j++) {
            if (random_uniform() < p4) {                                        // person is initialized as V for random_uniform < 'p4'
                grid[row_i*length + column_j] = -1;
            } else {                                                            // person initialized as S, I or R with equal probabilities 
                grid[row_i*length + column_j] = (int) (random_uniform() * 3);
            }
        }
    }
    return;
}


// updates a single node with given postion according to the 'probabilities'
void update_node(int *grid, int length, int row_i, int column_j, double *probabilities) {
    // caching the turnover-propabilities from the double-array for later use
    double p1 = probabilities[0];
    double p2 = probabilities[1];
    double p3 = probabilities[2];

    int *node = &grid[row_i*length + column_j];                                     // caching the pointer on the selceted 'node' to change the grid in-place
    switch (*node) {                                                                // select for the state the selected person/node is in

        // person is in state vaccinated V and will remain there
        case -1:
            break;

        // person is susceptible S and gets infected I with p1 for (at least) one infected neighbor
        case 0:
            int north_node_state = grid[(row_i+1)*length + column_j];
            int south_node_state = grid[(row_i-1)*length + column_j];                                                 
            int east_node_state = grid[row_i*length + (column_j-1)];
            int west_node_state = grid[row_i*length + (column_j+1)];

            if ((north_node_state == 1 || south_node_state == 1 || east_node_state == 1 || west_node_state == 1) && random_uniform() < p1) {
                *node = 1;
            }
            break;

        // person is infected I and turns recovered R with p2
        case 1:                                   
            if (random_uniform() < p2) {
                *node = 2;
            }
            break;

        // person is recovered R and return susceptible S with p3 
        case 2:
            if (random_uniform() < p3) {
                *node = 0;
            }
    }
    return;
}


// update the 'grid' with squared 'length' according to the 'probibilities' (all grid-points in order)
void grid_update_linear(int *grid, int length, double *probabilities) {
    for (int row_i = 1; row_i < length-1; row_i++) {
        for (int column_j = 1; column_j < length-1; column_j++) {
            update_node(grid, length, row_i, column_j, probabilities);
        }
    }
    return;
}


// update the 'grid' with squared 'length' according to the 'probibilities' (L^2 grid-points randomly chosen)
void grid_update_stochastic(int *grid, int length, double *probabilities) {
    for (int i = 0; i < (length-2) * (length-2); i++) {
        int row_i = ((int) (random_uniform() * (length-2))) + 1;
        int column_j = ((int) (random_uniform() * (length-2))) + 1;
        update_node(grid, length, row_i, column_j, probabilities);
    }
    return;
}


// ratio infected to uninfected for the given 'grid' of 'length' 
double ratio_infected(int *grid, int length) {
    double sum_infected = 0;
    for (int row_i = 1; row_i < length-1; row_i++) {
        for (int column_j = 1; column_j < length-1; column_j++) {
            int *node = &grid[row_i*length + column_j];
            if (*node == 1) {
                sum_infected++;
            }
        }
    }
    return sum_infected / cvc_npow((double) (length-2), 2);
} 


int main(void) {

// +++ Aufgabe 1 +++

    double probability_array[4];                                                // array with the probabilities pi 
    int L;                                                                      // integer sidelegth 'L' of the squared grid of people

    // input of the probablities 'pi' and the sidelength 'L' of the quadratic grid and saving the probabilities in the corresponding array
    printf("Enter p1 (susceptible -> infected): ");
    scanf("%lg", &probability_array[0]);                                        // probability 'p1' of a susceptible person getting infected (given an infected neighbor)
    printf("Enter p2 (infected -> recovered): ");
    scanf("%lg", &probability_array[1]);                                        // probability 'p2' of an infected person turning recovered 
    printf("Enter p3 (recovered -> susceptible): ");
    scanf("%lg", &probability_array[2]);                                        // probability 'p3' of a recovered person returning susceptible
    probability_array[3] = 0;                                                   // no vaccinated people V
    printf("Enter size of grid L: ");
    scanf("%d", &L);                                                            // integer sidelegth 'L' of the squared grid of people

    // allocating zeroed memory for the quadratic grid L^2 including non-participating borders and operating on the grid
    int *infectious_grid = (int*) calloc((L+2)*(L+2), sizeof(int));
    grid_init(infectious_grid, L+2, probability_array);
    print_grid(infectious_grid, L+2);
    printf("\nPress 'ENTER' to update grid for the new timestep. Type 's' to chose L^2 nodes randomly (default), 'l' to update all nodes one after another, 'q' to quit and confim with 'ENTER': ");

    // update grid manually for one timestep each according to the instructions
    char grid_updater = 's', c;                                                 // saves the recent valid input and initializes input variable c
    while ((c = getchar()) != EOF) {
        printf("Latest valid entry: %c.", grid_updater);
        if (c == 's') {                                                         // turning latest valid input to 's', meaning L^2 nodes are randomly chosen
            grid_updater = 's';
        } else if (c == 'l') {                                                  // turning latest valid input to 'l', meaning all nodes are updated sequentially
            grid_updater = 'l';
        } else if (c == 'q') {                                                  // latest valid input 'q', 'ENTER' will end the manual operation and continue 
            grid_updater = 'q';
        } else if (c == '\n') {                                                 // confirm input with 'ENTER' and act accordingly to the previously last valid input
            if (grid_updater == 's') {
                grid_update_stochastic(infectious_grid, L+2, probability_array);
                print_grid(infectious_grid, L+2);
            } else if (grid_updater == 'l') {
                grid_update_linear(infectious_grid, L+2, probability_array);
                print_grid(infectious_grid, L+2);
            } else if (grid_updater == 'q') {
                printf("\n");
                break;
            }
        }
    }



// +++ Aufgabe 2 +++ 



// +++ Aufgabe 3 +++ 

    // double p1 = 0.5;                                                            // probability 'p1' of a susceptible person getting infected (given an infected neighbor)
    // double p2 = 0.5;                                                            // probability 'p2' of an infected person turning recovered 
    // double p3 = 0.5;                                                            // probability 'p3' of a recovered person returning susceptible
    // double p4 = 0;                                                              // likelyhood 'p4' of a person appearing vaccinated and completely immunized, thus not participating in the spread at all
    // int L = 8;                                                                  // integer sidelegth 'L' of the squared grid of people
    // double probability_array[4] = {p1, p2, p3, p4};

    free(infectious_grid);                                                      // freeing the memory used for the modelling grid
    return 0;
}