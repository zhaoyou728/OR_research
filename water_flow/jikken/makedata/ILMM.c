/*------------------------------------------------------------*/
/*    ILMM.c
/*
/*      Hiroshige DAN
/*         Department of Applied Mathematics and Physics,
/*         Graduate School of Infomatics,
/*         Kyoto University, Kyoto, Japan.
/*      December, 2000.
/*------------------------------------------------------------*/
/* This program solves G(x)=0
/* using inexact Levenberg-Marquardt method. 
/*  Compile          :  % gcc -lm -O3 ILMM.c
/*  Usage(example)   :  % a.out -P 1 -I 0 -N 10 -M 5
/*     P: problem #, I: initial point, N and M: dimension
/*     P: 1, 2  -- Instance for my paper
/*------------------------------------------------------------*/


#include "ILMM.h"


double function_G(int j, double x[N])
{
  switch (P){
  case 1:
	return sqrt(j + 1.0) * (x[j] - j - 1.0);
	break;
  case 2:
	return sqrt(j + 1.0) * (x[j] + x[(N/2) + j] - j - 1.0);
	break;
  case 3:
	return x[j] * x[j] - j - 1.0;
	break;
  case 4:
	return pow((x[j] + x[(N/2) + j]), 2.0) - j - 1.0;
	break;
  case 5:
	return exp(x[j] - 1.0);
	break;
	/* Other Problems */
	/* case 11:
	if((j % 2)==0)
	  return x[j] - j - 1.0;
	else
	  return (x[j - 1] - j - 1.0) * (x[j] - j - 1.0);
	break;
  case 12:
	if((j % 2)==0)
	  return sqrt(j + 1.0) * (x[j] + x[(N/2) + j] - j - 1.0);
	else
	  return sqrt(j + 1.0)
		* (x[j - 1] + x[(N/2) + j - 1] - j - 1.0)
		* (x[j] + x[(N/2) + j] - j - 1.0);
	break;
  case 13:
	if(j == 0)
	  return (x[0] - 1.0);
	else
	  return sqrt(j + 1.0)
		* ((x[j - 1] - j - 1.0) * (x[j] - j - 1.0));
	break;
  case 14:
	if(j == 0)
	  return (x[0] + x[(N/2)] - 1.0);
	else
	  return sqrt(j + 1.0)
		* (x[j - 1] + x[(N/2) + j - 1] - j - 1.0)
		* (x[j] + x[(N/2) + j] - j - 1.0);
	break;
  case 15:
	if((j % 2)==0)
	  return sqrt(j + 1.0) * (x[j] + x[(N/2) + j] - j - 1.0);
	else
	  return sqrt(j + 1.0)
		* (x[j - 1] + x[(N/2) - j - 1])
		* (x[j] + x[(N/2) - j] - j - 1.0);
	break;
  case 16:
	if((j % 2)==0)
	  return sqrt((double)(j + 1.0)) * (x[j] - j - 1.0);
	else
	  return sqrt((double)(j + 1.0))
		* (x[j - 1] * x[j] - j - 2.0);
	break;
  case 17:
	if((j % 2)==0)
	  return sqrt((double)(j + 1.0)) * (x[j] - j - 1.0);
	else
	  return sqrt((double)(j + 1.0))
		* ((x[j - 1] - j - 1.0) * (x[j] - j - 1.0))
		+ (x[j - 1] - j - 2.0);
	break;
  case 18:
	if((j % 2)==0)
	  return sqrt((double)(j + 1.0)) * (x[j] - j - 1.0);
	else
	  return sqrt((double)(j + 1.0))
		* pow((x[j - 1] - j - 1.0), 2.0) * (x[j] - j - 1.0);
	break;
  case 19:
	if (j == 0)
	  return x[0] - 1.0;
	else
	  return sqrt(j + 1.0) * (x[j - 1] * x[j - 1] + x[j] - 2.0);
	break;
  case 20:
	if ((j % 2) == 0)
	  return x[j] + x[j + 1] - 2.0;
	else
	  return x[j - 1] * x[j - 1] + x[j] + x[j] - 2.0;
	break;
  case 21:
	if (j == 0)
	  return x[0] - 1.0;
	else
	  return x[j - 1] * x[j - 1] - x[j];
	break;*/
  }
}


/* Caluculation of partial diffrential of G at x */
double part_diff(int i, int j)
{
  switch(P){
  case 1:
	if(i == j)
	  return sqrt(j + 1.0);
	else
	  return 0.0;
	break;
  case 2:
	if ((i == j) || ((i - j) == (N/2)))
	  return sqrt(j + 1.0);
	else
	  return (0.0);
	break;
  case 3:
	if (i == j)
	  return 2.0 * x[j];
	else 
	  return 0.0;
	break;
  case 4:
	if ((i == j) || (i - (N/2) == j))
	  return 2.0 * (x[j] + x[(N/2) + j]);
	else
	  return 0.0;
	break;
  case 5:
	if(i == j)
	  return exp(x[j] - 1.0);
	else
	  return 0.0;
	break;
	/* Other Problems */
	/* case 11:
	if((i == j) && ((j % 2) == 0))
	  return sqrt((double)(j + 1.0));
	else if((i == j) && ((j % 2) == 1))
	  return sqrt((double)(j + 1.0)) * (x[j - 1] - j - 1.0);
	else if((i == (j - 1)) && ((j % 2) == 1))
	  return sqrt((double)(j + 1.0)) * (x[j] - j - 1.0) + 1;
	else return (0.0);	
	break;
  case 12:
	if((i == j) && ((j % 2) == 0))
	  return
		1.0;
	else if((i == j) && ((j % 2) == 1))
	  return x[j - 1] - j - 1.0;
	else if((i == (j - 1)) && ((j % 2) == 1))
	  return x[j] - j - 1.0;
	else return (0.0);	
	break;
  case 13:
	if((i == j) && ((j % 2) == 0))
	  return sqrt(j + 1.0) * x[(N/2) + j];
	else if(((i - j) == (N/2)) && ((j % 2) == 0))
	  return sqrt(j + 1.0) * x[j];
	else if(((i == j) || ((i - j) == (N/2))) && ((j % 2) == 1))
	  return sqrt(j + 1.0) * (x[j - 1] + x[(N/2) + j - 1] - j - 1.0);
	else if((((i - 1) == j) || ((i - 1 -j) == (N/2))) && ((j % 2) == 1))
	  return sqrt(j + 1.0) * (x[j] + x[(N/2) + j] - j - 1.0);
	else return (0.0);	
	break;
  case 14:
	if ((i == 0) && (j == 0))
	  return (1.0);
	else if(i == j)
	  return sqrt(j + 1.0) * (x[j - 1] - j - 1.0);
	else if ((i - 1) == j)
	  return sqrt(j + 1.0) * (x[j] - j - 1.0);
	else return (0.0);
	break;
  case 15:
	if ((i == 0) && (j == 0))
	  return (x[(N/2)]);
	else if ( (i == (N/2)) && (j == 0) )
	  return (x[0]);
	else if ( (i == j) || ((i - j) == (N/2)) )
	  return sqrt(j + 1.0) * (x[j - 1] + x[(N/2) - j - 1] - j - 1.0);
	else if ( ((i - 1) == j) || (((i - 1) - j) == (N/2)) )
	  return sqrt(j + 1.0) * (x[j] + x[(N/2) - j] - j - 1.0);
	else return (0.0);
	break;
  case 16:
	if((i == j) && ((j % 2) == 0))
	  return sqrt(j + 1.0) * x[(N/2) + j];
	else if(((i - j) == (N/2)) && ((j % 2) == 0))
	  return sqrt(j + 1.0) * x[j];
	else if(((i == j) || ((i - j) == (N/2))) && ((j % 2) == 1))
	  return sqrt(j + 1.0) * (x[j - 1] + x[(N/2) - j - 1]);
	else if((((i - 1) == j) || ((i - 1 -j) == (N/2))) && ((j % 2) == 1))
	  return sqrt(j + 1.0) * (x[j] + x[(N/2) - j] - j - 1.0);
	else return (0.0);	
	break;
  case 17:
	if((i == j) && ((j % 2) == 0))
	  return sqrt((double)(j + 1.0));
	else if((i == j) && ((j % 2) == 1))
	  return sqrt((double)(j + 1.0)) * x[j - 1];
	else if((i == (j - 1)) && ((j % 2) == 1))
	  return sqrt((double)(j + 1.0)) * x[j];
	else return (0.0);	
	break;
  case 18:
	if((i == j) && ((j % 2) == 0))
	  return sqrt((double)(j + 1.0));
	else if((i == j) && ((j % 2) == 1))
	  return sqrt((double)(j + 1.0)) * pow((x[j - 1] - j - 1.0), 2.0);
	else if((i == (j - 1)) && ((j % 2) == 1))
	  return sqrt((double)(j + 1.0)) * (x[j] - j - 1.0)
		* (x[j - 1] - j - 1.0) * 2.0;
	else return (0.0);	
	break;
  case 19:
	if ((i == 0) && (j == 0))
	  return 1.0;
	else if (i == j - 1)
	  return sqrt(j + 1.0) * 2.0 * x[j - 1];
	else if (i == j)
	  return sqrt(j + 1.0);
	else
	  return 0.0;
	break;
  case 20:
	if (((j % 2) == 0) && ((i == j) || (i - 1 == j)))
	  return 1.0;
	else if (((j % 2) == 1) && (i == j))
	  return 2.0 * x[j];
	else if (((j % 2) == 1) && (i == j - 1))
	  return 2.0 * x[j - 1];
	else 
	  return 0.0;
	break;
  case 21:
	if((i == 0) && (j == 0))
	  return 1.0;
	else if (i == j - 1)
	  return 2.0 * x[j - 1];
	else if (i == j)
	  return -1.0;
	else
	  return 0.0;
	break;*/
  }
}


void Jacobian()
{
  int i, j;

  double tmp_v;
  struct element *tmp_N_p;
  struct element *tmp_M_p;

  for(j = 0; j < M; j++)
	head_M[j].next = NULL;

  for(i = 0; i < N; i++){
	tmp_N_p = &head_N[i];
	for(j = 0; j < M; j++){
	  tmp_v = part_diff(i, j);
	  if (fabs(tmp_v) >= 1.0e-20){
		/* head_N */
		tmp_N_p->next = (struct element *) malloc_e (sizeof (struct element));
		tmp_N_p->next->k_th = j;
		tmp_N_p->next->value = tmp_v;
		tmp_N_p = tmp_N_p->next;
		/* head_M */
		for(tmp_M_p = &head_M[j]; ;	tmp_M_p = tmp_M_p->next)
		  if(tmp_M_p->next == NULL)
			break;
		tmp_M_p->next = (struct element *) malloc_e (sizeof (struct element));
		tmp_M_p->next->k_th = i;
		tmp_M_p->next->value = tmp_v;
		tmp_M_p->next->next = NULL;
	  }
	}
	tmp_N_p->next = NULL;
  }
}


void making_JG_T_G()
{
  int i, j;
  double tmp[M];
  struct element *tmp_p_i;

  for(j = 0; j < M; j++)
	tmp[j] = function_G(j, x);

  for(i = 0; i < N; i++){
	JG_T_G[i] = 0.0;
	tmp_p_i = head_N[i].next;
	while(tmp_p_i != NULL){
	  JG_T_G[i] = JG_T_G[i] + (tmp_p_i->value) * tmp[tmp_p_i->k_th];
	  tmp_p_i = tmp_p_i->next;
	}
	/* printf("JG_T_G[%d] = %2.5e\n", i, JG_T_G[i]); */
  }
}


double product_Na(int i, double a[])
{
  double tmp_v = 0.0;
  struct element *tmp_p;

  for(tmp_p = head_N[i].next; tmp_p != NULL; tmp_p = tmp_p->next)
	tmp_v = tmp_v + (tmp_p->value) * a[tmp_p->k_th];
  
  return (tmp_v);
}


double product_Ma(int j, double a[])
{
  double tmp_v = 0.0;
  struct element *tmp_p;

  for(tmp_p = head_M[j].next; tmp_p != NULL; tmp_p = tmp_p->next)
	tmp_v = tmp_v + (tmp_p->value) * a[tmp_p->k_th];
  
  return (tmp_v);
}


double product_aNMa(double a[])
{
  int j;
  double tmp1 = 0.0;

  for(j = 0; j < M; j++)
	tmp1 = tmp1 + pow(product_Ma(j, a), 2.0);

  return (tmp1);
}


/* Caluculation of search direction */
int search_direction()
{
  int i, j, k = 0, count = 0;
  double v_k, v_k_1, step1, step2, tmp1, tmp2, tmp3, tmp4, nu,
	r_k_norm = 0.0, JG_T_G_norm = 0.0;
  double d_k[N], d_k_1[N], tmp_a_1[M], tmp_a_2[N];
  
  /* Initialize */

  for(i = 0; i < N; i++){
	d[i] = 1.0;  /* Initialize search direction */
	JG_T_G_norm = JG_T_G_norm + JG_T_G[i] * JG_T_G[i];
  }

  JG_T_G_norm = sqrt(JG_T_G_norm);
  nu = pow(function_G_norm(x), tau);

  for(j = 0; j < M; j++)
	tmp_a_1[j] = product_Ma(j, d);
  for(i = 0; i < N; i++){
	tmp_a_2[i] = product_Na(i, tmp_a_1);
	tmp_a_2[i] = tmp_a_2[i] + mu * d[i] + JG_T_G[i];
  }
  
  tmp4 = 0.0;
  for(i = 0; i < N; i++)
	tmp4 = tmp4 + pow(tmp_a_2[i], 2.0);
  tmp4 = sqrt(tmp4);

  /* Iteration  */
  for(k = 0; ((tmp4 > (eta * JG_T_G_norm))
			  || (tmp4 > (nu * pow(JG_T_G_norm, delta)))
			  || (tmp4 > (kappa * sqrt((double)N)))); k++){

	/* Restart */
	if(k == N){
	  k = 0;
	  count++;
	  printf("Restart %d\n", count);
	}

	if(count >= 10)
	  break;
	
	/* Initialize for this iteration */
	if(k != 0){
	  v_k_1 = v_k;
	  for(i = 0; i < N; i++)
		d_k_1[i] = d_k[i];
	}
	
	/* Search direction */
	if(k == 0){
	  v_k = 0.0;
	  for(i = 0; i < N; i++){
		d_k[i] = - tmp_a_2[i];
		v_k = v_k + pow(d_k[i], 2.0);
	  }
	}
	else{
	  v_k = 0.0;
	  for(i = 0; i < N; i++)
		v_k = v_k + pow(tmp_a_2[i], 2.0);
	  step1 = (v_k / v_k_1);
	  for(i = 0; i < N; i++)
		d_k[i] = - tmp_a_2[i] + step1 * d_k_1[i];
	}
	
	/* Generate next iteration point */
	tmp1 = 0.0;
	tmp2 = 0.0;
	for(i = 0; i < N; i++){
	  tmp1 = tmp1 + d_k[i] * tmp_a_2[i];
	  tmp2 = tmp2 + pow(d_k[i], 2.0);
	}
	step2 = - (tmp1 / (product_aNMa(d_k) + mu * tmp2));

	for(i = 0; i < N; i++)
	  d[i] = d[i] + step2 * d_k[i];

	/* Check stop condition */
	for(j = 0; j < M; j++)
	  tmp_a_1[j] = product_Ma(j, d);
	for(i = 0; i < N; i++){
	  tmp_a_2[i] = product_Na(i, tmp_a_1);
	  tmp_a_2[i] = tmp_a_2[i] + mu * d[i] + JG_T_G[i];
	}

	tmp4 = 0.0;
	for(i = 0; i < N; i++)
	  tmp4 = tmp4 + pow(tmp_a_2[i], 2.0);
	tmp4 = sqrt(tmp4);
  }

  if(count == 10)
	return -1;
  else
	return k + count * N;
  
}


/* Caluculation of norm of function G at x */
double function_G_norm(double a[])
{
  int j;
  double tmp_v = 0.0;
  
  for(j = 0; j < M; j++)
	tmp_v = tmp_v + pow(function_G(j, a), 2.0);

  return(sqrt(tmp_v));
}


/* Caluculation of step size */
double armijo_rule(double tmp_v_1, double tmp_v_2)
{
  int i;
  double phi_x, tmp_v, tmp_v_3, nabla_phi_x_T_d = 0.0, m = 0.0;
  double tmp_a[N];

  phi_x = 0.5 * pow(tmp_v_2, 2.0);
  for(i = 0; i < N; i++)
	nabla_phi_x_T_d = nabla_phi_x_T_d + JG_T_G[i] * d[i];
  
  tmp_v = 0.5 * pow(tmp_v_1, 2.0) - phi_x - alpha * nabla_phi_x_T_d;

  while(tmp_v > 0.0){
	m = m + 1.0;
	for(i = 0; i < N; i++)
	  tmp_a[i] = x[i] + pow(beta, m) * d[i];
	tmp_v_3 = 0.5 * pow(function_G_norm(tmp_a), 2.0);
	tmp_v = tmp_v_3 - phi_x - alpha * pow(beta, m) * nabla_phi_x_T_d;
  }

  return(pow(beta, m));
}


/* Releasing memory */
void head_release()
{
  int i, j;
  struct element *tmp_p_now, *tmp_p_next;

  for(i = 0; i < N; i++){
	tmp_p_now = head_N[i].next;
	while(tmp_p_now != NULL){
	  tmp_p_next = tmp_p_now->next;
	  free(tmp_p_now);
	  tmp_p_now = tmp_p_next;
	}
  }

  for(j = 0; j < M; j++){
	tmp_p_now = head_M[j].next;
	while(tmp_p_now != NULL){
	  tmp_p_next = tmp_p_now->next;
	  free(tmp_p_now);
	  tmp_p_now = tmp_p_next;
	}
  }
}


void search_direction_check()
{
  int i;
  double tmp_v = 0.0, nabla_phi_x_T_d = 0.0;
  
  for(i = 0; i < N; i++)
	nabla_phi_x_T_d = nabla_phi_x_T_d + JG_T_G[i] * d[i];

  for(i = 0; i < N; i++)
	tmp_v = tmp_v + d[i] * d[i];
  
  if(nabla_phi_x_T_d > (- rho * pow(tmp_v, (p / 2.0))))
	for(i = 0; i < N; i++)
	  d[i] = - JG_T_G[i];
}


void readparameters(int c, char *v[])
{
  int i;

  /* Set default value */
  P = 1;
  I = 1;
  N = 100;
  M = 50;
  eta = 0.8;
  tau = 2.0;
  delta = 1.0;
  zeta = 0.001;
  kappa = 0.001;
  

  for(i = 1; i < c; i++){
	if(strcmp(v[i],"-P") == 0)   {P     = atoi(v[++i]);  continue;}
	if(strcmp(v[i],"-I") == 0)   {I     = atoi(v[++i]);  continue;}
    if(strcmp(v[i],"-N") == 0)   {N     = atoi(v[++i]);  continue;}
    if(strcmp(v[i],"-M") == 0)   {M     = atoi(v[++i]);  continue;}
    if(strcmp(v[i],"-E") == 0)   {eta   = atof(v[++i]);  continue;}
    if(strcmp(v[i],"-T") == 0)   {tau   = atof(v[++i]);  continue;}
    if(strcmp(v[i],"-D") == 0)   {delta = atof(v[++i]);  continue;}
    if(strcmp(v[i],"-Z") == 0)   {zeta  = atof(v[++i]);  continue;}
    if(strcmp(v[i],"-K") == 0)   {kappa = atof(v[++i]);  continue;}
    i++;
  }

}


void malc (void) {
  int i;

  JG_T_G     = (double *)  malloc_e ( N * sizeof (double));
  d          = (double *)  malloc_e ( N * sizeof (double));
  x          = (double *)  malloc_e ( N * sizeof (double));
  head_N     = (struct element *) malloc_e (N * sizeof (struct element));
  head_M     = (struct element *) malloc_e (M * sizeof (struct element));

}


void *malloc_e( size_t size ) {
  void *s;
  if ( (s=malloc(size)) == NULL ) {
    fprintf( stderr, "malloc : Not enough memory.\n" );
    fprintf( stderr, " -> Try setting cslub to -1.\n" );
    fprintf( stderr, "    If it fails, then try memeff = 1.\n" );
    exit( EXIT_FAILURE );
  }
  return s;
}


/* Main */
main(int argc, char **argv)
{
  int i, j, k, count = 0;
  double tmp_v_1, tmp_v_2, tmp_v_3, step_size, start, finish, check = 0.0;
  double *tmp_a;

  /* Initialize */
  start = my_time();

  readparameters(argc, argv);
  tmp_a = (double *) malloc_e (N * sizeof(double));
  malc();

  switch (I){
  case 1:
	for(i = 0; i < N; i++)
	  x[i] = (double)(N/2);
	break;
  case 2:
	for(i = 0; i < N; i++)
	  x[i] = (double)N;
	break;
  case 3:
	for(i = 0; i < N; i++)
	  x[i] = (double)(-N/2);
	break;
  case 4:
	for(i = 0; i < N; i++)
	  x[i] = (double)(-N);
	break;
  case 11:
	for(i = 0; i < N; i++)
	  x[i] = 0.0;
	break;
  case 12:
	for(i = 0; i < N; i++)
	  x[i] = (double)(N - i);
	break;
  case 13:
	for(i = 0; i < N; i++)
	  x[i] = 1.0;
	break;
  case 14:
	for(i = 0; i < N; i++)
	  x[i] = 2.0;
	break;
  }
  tmp_v_3 = function_G_norm(x);
  printf("norm = %2.5e\n", tmp_v_3);
  mu = pow(tmp_v_3, delta);
  if (mu >= zeta)
	mu = zeta;
  /* printf("tau = %2.5e\n", tau);
  printf("eta = %2.5e\n", eta);
  printf("delta = %2.5e\n", delta); */

  /* Iteration */
  while((tmp_v_3 >= epsilon * sqrt((double)N)) && (count < 200)){
	count++;
	Jacobian();
	making_JG_T_G();
	check = check + (double)search_direction();
	
	if(check == -1.0)
	  break;

	/* Caluculation of step size and renewing x */
	for(i = 0; i < N; i++)
	  tmp_a[i] = x[i] + d[i];

	tmp_v_1 = function_G_norm(tmp_a);
	tmp_v_2 = function_G_norm(x);

	if(tmp_v_1 <= (gamma_1 * tmp_v_2)){
	  for(i = 0; i < N; i++)
		x[i] = tmp_a[i];
	}
	else{
	  search_direction_check();
	  step_size = armijo_rule(tmp_v_1, tmp_v_2);
	  if (step_size <= 1.0e-8)
		printf("WARNING: Step size is smaller than 1.0e-8.\n");
	  for(i = 0; i < N; i++)
		x[i] = x[i] + step_size * d[i];
	}
	
	/* Release memory which has not been needed */
	head_release();

	/* Renewing mu */
	tmp_v_3 = function_G_norm(x);
	printf("norm = %2.5e\n", tmp_v_3);
	mu = pow(tmp_v_3, delta);
	if (mu >= zeta)
	  mu = zeta;
  }

  finish = my_time();

  /* Print answer */
  if(tmp_v_3 < epsilon * sqrt((double)N)){
	/* for(i = 0; i < N; i++)
	  printf("ans[%d] = %2.5e\n", i, x[i]); */
	printf("Iteration %d times.\n", count);
	printf("CG iteration %6.0f times.\n", check);
	/* printf("Value of mu is %2.5e.\n", mu); */
  }
  else if (check == 1){
	printf("The number of iteration exceeds 200 (default value).\n");
	/*tmp_v_1 = 0.0;
	for(i = 0; i < N; i++)
	  tmp_v_1 = tmp_v_1 + d[i] * d[i];
	printf("tmp_v_1 = %2.5e\n", tmp_v_1);*/
	if(step_size < 1.0e-10){
	  printf("Perhaps present iteration point is\n");
	  printf(" a stationary point of merit function.\n");
	  printf("Please change initial point and retry.\n");
	}
  }
  else{
	printf("Restart of CG occured 10 times.\n");
	printf("Calculation stop.\n");
  }
  printf("CPU time = %2.5e\n", finish - start);
}

/* End of file */
