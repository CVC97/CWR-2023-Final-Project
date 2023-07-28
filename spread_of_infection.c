#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "cvc_numerics.h"
#include "cvc_rng.h"


// generate uniforms using static Mersenne-Twister MT19937 to reduce parameters
double random_uniform(void) {
    static gsl_rng* generator = NULL;                                               // initializing the static rng variable
    if (generator == NULL) {                                                        // initializing MT19937 as rng at the first function call 
        generator = gsl_rng_alloc(gsl_rng_mt19937);
        gsl_rng_set(generator, time(NULL));
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
    double p4 = probabilities[3];                                                   // caching the probability of someone being initialized as V                                      

    // iterating through the grid ignoring the borders
    for (int row_i = 1; row_i < length-1; row_i++) {
        for (int column_j = 1; column_j < length-1; column_j++) {
            if (random_uniform() < p4) {                                            // person is initialized as V for random_uniform < 'p4'
                grid[row_i*length + column_j] = -1;
            } else {                                                                // person initialized as S, I or R with equal probabilities 
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
    return sum_infected / ((length-2) * (length-2));
} 


// average ratio infected to uninfected over 'T' simulation steps for given 'grid', 'length' and 'probabilities'
double average_ratio_infected(int *grid, int length, int T, double *probabilities) {
    double sum_ratio = ratio_infected(grid, length);
    for (int i = 0; i < T; i++) {
        grid_update_stochastic(grid, length, probabilities);
        sum_ratio += ratio_infected(grid, length);
    }
    return sum_ratio / T;
}


int main(void) {

// +++ Aufgabe 1: model for the spread of infectious diseases +++
// {

//     double probability_array[4];                                                // array with the probabilities pi 
//     int L;                                                                      // integer sidelegth 'L' of the squared grid of people

//     // input of the probablities 'pi' and the sidelength 'L' of the quadratic grid and saving the probabilities in the corresponding array
//     printf("Enter p1 (susceptible -> infected): ");
//     scanf("%lg", &probability_array[0]);                                        // probability 'p1' of a susceptible person getting infected (given an infected neighbor)
//     printf("Enter p2 (infected -> recovered): ");
//     scanf("%lg", &probability_array[1]);                                        // probability 'p2' of an infected person turning recovered 
//     printf("Enter p3 (recovered -> susceptible): ");
//     scanf("%lg", &probability_array[2]);                                        // probability 'p3' of a recovered person returning susceptible
//     probability_array[3] = 0;                                                   // no vaccinated people V
//     printf("Enter size of grid L: ");
//     scanf("%d", &L);                                                            // integer sidelegth 'L' of the squared grid of people

//     // allocating zeroed memory for the quadratic grid L^2 including non-participating borders and operating on the grid
//     int *infectious_grid = (int*) calloc((L+2)*(L+2), sizeof(int));
//     if (infectious_grid == NULL) {                                              // checking for memory availablity
//         printf("ERROR! Memory is not available, please add more RAM.");
//         return 1;
//     }
//     grid_init(infectious_grid, L+2, probability_array);
//     print_grid(infectious_grid, L+2);
//     printf("\nPress 'ENTER' to update grid for the new timestep. Enter 'q' to quit and continue.");
//     while (getchar() != '\n');

//     // update grid manually for one timestep
//     char c;                                                                     // input variable c
//     while ((c = getchar()) != EOF ) {
//         if (c == '\n') {                                                        // confirm input with 'ENTER' and act accordingly to the previously last valid input
//             grid_update_linear(infectious_grid, L+2, probability_array);
//             print_grid(infectious_grid, L+2);
//         } else if (c == 'q') {                                                  // quit and continue with further code
//             break;
//         }
//     }
//     free(infectious_grid);

// }
// +++ Aufgabe 2: time-averaged infection rate depending on the turnover rate 'p1' from susceptible to infected +++ 
// {

//     int T = 1000;                                                               // number 'T' of simulation steps

//     // setting up the files a, b and c for the various combinations of p2 and p3 with their first row p1 values and 00 as dummies for the top left csv entries
//     FILE* average_ratio_file_a = fopen("soi_data/soi_average_ratio_infected_over_p1_a.csv", "w");
//     FILE* average_ratio_file_b = fopen("soi_data/soi_average_ratio_infected_over_p1_b.csv", "w");
//     FILE* average_ratio_file_c = fopen("soi_data/soi_average_ratio_infected_over_p1_c.csv", "w");
//     fprintf(average_ratio_file_a, "00");
//     fprintf(average_ratio_file_b, "00");
//     fprintf(average_ratio_file_c, "00");
//     for (double p1 = 0; p1 <= 1; p1 += 0.02) {
//         fprintf(average_ratio_file_a, ", %g", p1);
//         fprintf(average_ratio_file_b, ", %g", p1);
//         fprintf(average_ratio_file_c, ", %g", p1);
//     }

//     // iteration over 'L' (32, 64, 196) to receive the time-averaged ratio of infected people in the grid depending on 'p1' for each 'L' and different combinations of p2 and p3 
//     for (int L = 32; L <= 96; L += 32) {
//         printf("A2: calculating L = %d ...\n", L);                              // progress bar for A2

//         // setting up the rows with each 'L' in the files
//         fprintf(average_ratio_file_a, "\n%d", L);
//         fprintf(average_ratio_file_b, "\n%d", L);
//         fprintf(average_ratio_file_c, "\n%d", L);

//         // allocating memory for grid a, b and c
//         int *infectious_grid_a = (int*) calloc((L+2)*(L+2), sizeof(int));
//         int *infectious_grid_b = (int*) calloc((L+2)*(L+2), sizeof(int));
//         int *infectious_grid_c = (int*) calloc((L+2)*(L+2), sizeof(int));
//         if (infectious_grid_a == NULL || infectious_grid_b == NULL || infectious_grid_c == NULL) {
//             printf("ERROR! Memory is not available, please add more RAM.");
//             return 1;
//         }

//         // iteration over 'p1' for the main dependency
//         for (double p1 = 0; p1 <= 1; p1 += 0.02) {
//             double probability_array_a[4] = {p1, 0.3, 0.3, 0};                  // probability array for a: 'p2' = 0.3 and 'p3' = 0.3
//             double probability_array_b[4] = {p1, 0.6, 0.3, 0};                  // probability array for b: 'p2' = 0.6 and 'p3' = 0.3
//             double probability_array_c[4] = {p1, 0.3, 0.6, 0};                  // probability array for c: 'p2' = 0.3 and 'p3' = 0.6

//             // initializing the grids a, b and c 
//             grid_init(infectious_grid_a, L+2, probability_array_a);
//             grid_init(infectious_grid_b, L+2, probability_array_b);
//             grid_init(infectious_grid_c, L+2, probability_array_c);

//             // caching the time-averaged ratio for later output in file form
//             double avg_ratio_a = average_ratio_infected(infectious_grid_a, L+2, T, probability_array_a);
//             double avg_ratio_b = average_ratio_infected(infectious_grid_b, L+2, T, probability_array_b);
//             double avg_ratio_c = average_ratio_infected(infectious_grid_c, L+2, T, probability_array_c);

//             // writing the time-averaged ratios for each 'p1' in each of the files a, b and c
//             fprintf(average_ratio_file_a, ", %g", avg_ratio_a);
//             fprintf(average_ratio_file_b, ", %g", avg_ratio_b);
//             fprintf(average_ratio_file_c, ", %g", avg_ratio_c);
//         }
//         free(infectious_grid_a);
//         free(infectious_grid_b);
//         free(infectious_grid_c);
//     }
//     fclose(average_ratio_file_a);
//     fclose(average_ratio_file_b);
//     fclose(average_ratio_file_c);

// }
// +++ Aufgabe 3: time-average of the infection rate depending on the rate of vaccinated, non-reactive people in the model 'p4' +++ 
// {

//     int T = 1000;                                                               // number 'T' of simulation steps

//     // setting up the file for the time-averaged infection rate with respect to time over 'p4' with its first line
//     FILE* average_ratio_file_v = fopen("soi_data/soi_average_ratio_infected_over_p4_v.csv", "w");
//     fprintf(average_ratio_file_v, "00");                                        // using dummy 00 to fill the top left entry of the csv
//     for (double p4 = 0; p4 <= 1; p4 += 0.02) {
//         fprintf(average_ratio_file_v, ", %g", p4);
//     }

//     // iteration over 'L' (32, 64, 96) to receive the average ratio of infected people for variable rates of vaccinated people 'p4'
//     for (int L = 32; L <= 96; L += 32) {
//         printf("A3: calculating L = %d ...\n", L);                              // progress bar for A3
//         fprintf(average_ratio_file_v, "\n%d", L);                               // setting up each row with its respective 'L' in the first column
//         int *infectious_grid_v = (int*) calloc((L+2)*(L+2), sizeof(int));       // allocating memory for the respective grid containing vaccinated individuals

//         // iteration over 'p4' as the main dependency
//         for (double p4 = 0; p4 <= 1; p4 += 0.02) {
//             double probability_array_v[4] = {0.5, 0.5, 0.5, p4};                // probability array with 'p1' = 'p2' = 'p3' = 0.5 and variable 'p4'
//             grid_init(infectious_grid_v, L+2, probability_array_v);             // initializing the vaccinated grid with its respective probability array
//             double avg_ratio_v = average_ratio_infected(infectious_grid_v, L+2, T, probability_array_v);
//             fprintf(average_ratio_file_v, ", %g", avg_ratio_v);                 // transfering the ratios into the data file
//         }
//         free(infectious_grid_v);
//     }
//     fclose(average_ratio_file_v);

// }
// +++ Time Analysis: time development of the infection rate over N samples +++
{

    int L = 64;                                                                 // grid length
    int T = 1000;                                                               // number 'T' of simulation steps
    int N = 20;                                                                 // number of analyzed samples 'N'
    double probability_array_t64[4] = {0.5, 0.5, 0.5, 0};                       // probabilities used for the time development

    // setting up the file for the 'N' infection rates over 'T+1' time steps (including the initial state)
    FILE* ratio_over_time_file = fopen("soi_data/soi_ratio_over_time.csv", "w");
    fprintf(ratio_over_time_file, "0");
    for (int t = 0; t <= T; t++) {
        fprintf(ratio_over_time_file, ", %d", t);
    }

    // caching the ratios for each sample to later calculate mean and standard deviation (array structure: 'N' samples in outer, 'T' timesteps in inner dimension)
    double *ratio_over_time_array = (double*) malloc(N * (T+1) * sizeof(double));
    if (ratio_over_time_array == NULL) {                                        // checking for memory availablity
        printf("ERROR! Memory is not available, please add more RAM.");
        return 1;
    }
    double (*ratio_over_time_column_pointer)[T+1];                              // pointer to access each virtual column individually using the virtual row length 'T+1'

    // allocating zeroed memory for the quadratic grid L^2 including non-participating borders
    int *infectious_grid_t64 = (int*) calloc((L+2)*(L+2), sizeof(int));
    if (infectious_grid_t64 == NULL) {                                          // checking for memory availablity
        printf("ERROR! Memory is not available, please add more RAM.");
        return 1;
    }

    // iterating over the 'N' samples
    for (int n = 0; n < N; n++) {
        grid_init(infectious_grid_t64, L+2, probability_array_t64);
        double ratio_t64 = ratio_infected(infectious_grid_t64, L+2);            // caching the initial ratio for transfer into array and file
        fprintf(ratio_over_time_file, "\n%d, %g", n, ratio_t64);                // adding sample number 'n' and initial infection ratio to column one and two of the data file
        ratio_over_time_array[n*N] = ratio_t64;                                 // adding initial infection rate of sample 'n' in the first column 

        // iterating over 'T' timesteps updating grid, array and data file accordingly
        for (int t = 1; t < T+1; t++) {
            grid_update_stochastic(infectious_grid_t64, L+2, probability_array_t64);
            ratio_t64 = ratio_infected(infectious_grid_t64, L+2);               // caching the current ratio for transfer into array and file
            fprintf(ratio_over_time_file, ", %g", ratio_t64);                   // adding the current infection ratio to the data file
            ratio_over_time_array[n*N + t] = ratio_t64;
        }
    }

    // calculating mean and adding it to the file for each timestep
    fprintf(ratio_over_time_file, "\n00");                                      // first column of the mean row filled with dummy 00
    for (int t = 0; t < T+1; t++) {
        ratio_over_time_column_pointer = (double (*)[T + 1]) &ratio_over_time_array[T+1];           // setting up the column pointer for each column / timestep
        double mean_ratio_t64 = cvc_mean(ratio_over_time_column_pointer, N);    // call of the cvc-function to calculate the mean for each column using the appropriate column pointer
        fprintf(ratio_over_time_file, ", %g", mean_ratio_t64);                  // adding the mean for each timestep to the respective file row
    }

    // calculating standard deviation sigma and adding it to the file for each timestep
    fprintf(ratio_over_time_file, "\n01");                                      // first column of the sigma row filled with dummy 01
    for (int t = 0; t < T+1; t++) {
        ratio_over_time_column_pointer = (double (*)[T + 1]) &ratio_over_time_array[T+1];           // setting up the column pointer for each column / timestep
        double sigma_ratio_t64 = cvc_sigma(ratio_over_time_column_pointer, N);  // call of the cvc-function to calculate the standard deviation for each column
        fprintf(ratio_over_time_file, ", %g", sigma_ratio_t64);                 // adding the standard deviation for each timestep to the respective file row
    }

    // freeing memory and closing files
    free(ratio_over_time_array);
    free(infectious_grid_t64);
    fclose(ratio_over_time_file);

}
// +++ Supplementary Data Generation: time development of the grid +++
{

    int T = 1000;

}
    return 0;
}