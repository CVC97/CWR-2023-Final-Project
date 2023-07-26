#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "cvc_numerics.h"
#include "cvc_rng.h"


double p1;                  // probability 'p1' of a susceptible person getting infected (given an infected neighbor)
double p2;                  // probability 'p2' of an infected person turning recovered 
double p3;                  // probability 'p3' of a recovered person returning susceptible
double p4;                  // likelyhood 'p4' of a person appearing vaccinated and completely immunized, thus not participating in the spread at all
int L;                      // integer sidelegth 'L' of the squared grid of people


// initialize the given 'grid' of length 'L' with people accoording to the 'probibilities'
void grid_init(int *grid, int L, void *probabilities) {

    return;
}


// update the 'grid' with squared length 'L' according to the 'probibilities' (all grid-points in order)
void grid_update_linear(int *grid, int L, void *probabilities) {

    return;
}


// update the 'grid' with squared length 'L' according to the 'probibilities' (L^2 grid-points randomly chosen)
void grid_update_stochastic(int *grid, int L, void *probabilities) {

    return;
}


// ratio infected to uninfected for the given 'grid' of length 'L' 
double ratio_infected(int *grid, int L) {
    double ratio = 0;
    return ratio;
} 


int main(void) {

    // input of the probablities 'pi' and the sidelength 'L' of the quadratic grid

    // allocating memory for the quadratic grid L^2

    return 0;
}