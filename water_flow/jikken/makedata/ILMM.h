/*------------------------------------------------------------*/
/*    ILMM.h
/*
/*      Hiroshige DAN
/*         Department of Applied Mathematics and Physics,
/*         Graduate School of Infomatics,
/*         Kyoto University, Kyoto, Japan.
/*      December, 2000.
/*------------------------------------------------------------*/
/* This file is a header file for ILMM.c and
/* contains parameters, functions and so on.
/* User may change some of parameters.
/*------------------------------------------------------------*/


# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "my_time.c"

# define I_MAX (N * M * 100)

double my_time(void);

void readparameters(int, char **);
void malc(void);
void *malloc_e( size_t size ); 

double function_G(int, double *);
double part_diff(int, int);
void Jacobian();
void making_JG_T_G();
double product_Na(int, double *);
double product_Ma(int, double *);
double product_aNMa(double *);
double function_for_CG(int);
int search_direction();
double function_G_norm(double *);
double armijo_rule(double, double);
void head_release();
void search_direction_check();

double *JG_T_G;
double *d;
double *x;
double mu;
int N, M, P, I;
double eta, tau, delta, zeta, kappa;

struct element{
  int k_th;
  double value;
  struct element *next;
};

struct element *head_N;
struct element *head_M;

/* Parameter and initial point */
/*↓ Please change below as you like ↓*/
double alpha = 0.6;
double beta = 0.7;
double rho = 0.5;
double gamma_1 = 0.8;
double p = 2.0;
double epsilon = 1.0e-8; /* Stop condition */
/*↑ As far as here ↑*/

/* End of file */
