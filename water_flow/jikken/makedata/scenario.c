#include <stdio.h>
#include <stdlib.h>
#include "file.h"

#define LEN 10000
//#define CLASS 3
//#define TERM 5
////#define CNUM 27 // CLASS^TERM

//int LEN = 10000;
//int CLASS = 3;
//int TERM = 5;

//double windClass[10] = {2.5, 6.0, 8.0, 20.0};
//double windClass[10] = {2.5, 6.0, 8.0, 20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

int readData(FILE* fp_data, float *data){
  float val;
  int i = 0;

  while(fscanf(fp_data, "%f", &val) != EOF){
	  data[i++] = val;
  }

  return i;
}

int getClassNum(float val, int CLASS, double *windClass){
  int i;
  if(val < windClass[0]) { return 9; }
  for(i = 1; i < CLASS + 1; i++){
    if(val < windClass[i]) { return i - 1; }
  }
  return 9;
}

double getPowerVal(int i, int CLASS, double* windClass){
  double a1 = 0.4 * 0.5 * 1.225 * 3217.0 * 0.8 * 21.0 / 1000.0 * 2.0;
  double a2;

  //printf("i = %d\n", i);
  i = (i + CLASS - 1) % CLASS;

  //  if(i == 0) { a2 = windClass[0]; }
  //  else if (i < CLASS - 1) { a2 = (windClass[i - 1] + windClass[i]) / 2.0; }
  //  else { a2 = windClass[CLASS - 1]; }
  //  printf("i: %d\n", i);
  a2 = (windClass[i] + windClass[i + 1]) / 2.0;
  //  printf("windClass[i] = %f\n", windClass[i]);
  //  printf("windClass[i+1] = %f\n", windClass[i+1]);
  //  printf("a2 = %f\n", a2);

  return a1 * a2 * a2 * a2;
}

int getResultNum(int *a, int CLASS, int TERM){
  int i, r = 0;
  for(i = 0; i < TERM; i++){
    if(a[-i] == 9) { return -1; }
    r = r * CLASS + a[-i]; // -i is OK!
  }
  return r;
}

void readParameters(int c, char *v[], int* CLASS, int *TERM, double* windClass)
{
  int i, n = 0;

  CLASS[0] = 3;
  TERM[0] = 5;
  windClass[0] = 2.5; windClass[1] = 6.0; windClass[2] = 8.0; windClass[3] = 20.0; windClass[4] = 0.0;
  windClass[5] = 0.0; windClass[6] = 0.0; windClass[7] = 0.0; windClass[8] = 0.00; windClass[9] = 0.0;

  for(i = 1; i < c; i++){
    //    if(strcmp(v[i],"-L") == 0)   {LEN   = atoi(v[++i]);  continue;}
    if(strcmp(v[i],"-C") == 0)   {CLASS[0] = atoi(v[++i]);  continue;}
    if(strcmp(v[i],"-T") == 0)   {TERM[0]  = atoi(v[++i]);  continue;}

    if(strcmp(v[i],"-v") == 0){
      windClass[n++] = atof(v[++i]);
      if(n > CLASS[0] + 1){
	fprintf(stderr, "val# is larger than -C. Exit.");
	exit(1);
      }
      continue;
    }
    
    i++;
  }
  
  return;
}

int main(int argc, char **argv){

  FILE *fp_data, *mydata;

  int classNum[LEN];
  int class[LEN];
  int prev[LEN];
  int idx[LEN];
  //  int idx[TERM + 1];
  float data[LEN];
  float prod[LEN];

  int CLASS;
  int TERM;
  double windClass[10] = {2.5, 6.0, 8.0, 20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  int head, i, j, k, n, r, efectNum = 0;
  double p;
  char output[256];

  readParameters(argc, argv, &CLASS, &TERM, windClass);

  fp_data = FILEOPEN("./mutsu_2010.txt", "r");
  n = readData(fp_data, data);
  //printf("%d\n", n);
  fclose(fp_data);

  idx[0] = 0;
  for(i = k = 1; i <= TERM; i++){
    k *= CLASS;
    idx[i] = idx[i - 1] + k;
    //printf("idx %d = %d\n", i, idx[i]);
  }

  for(i = 0; i < LEN; i++){
	  classNum[i] = 0;
	  prod[i] = 0.0;
	  prev[i] = 0;
  }

  for(i = 0; i < n; i++){
	  class[i] = getClassNum(data[i], CLASS, windClass);
  }

  for(i = TERM - 1; i < n; i++){
    r = getResultNum(&class[i], CLASS, TERM);
    if(r >= 0){
      efectNum++;
      classNum[r]++;
    }
    //printf("%d: %d\n", i, r);
  }

  //  for(i = 0; i < CNUM; i++){
  //    printf("Class %d: %f\n", i, (float)classNum[i] / (n - TERM + 1) );
  //  }

  // final term
  p = 0.0;
  for(i = 0; i < idx[TERM] - idx[TERM - 1]; i++){
    //prod[i + idx[TERM - 1]] = (double)classNum[i] / (n - TERM + 1);
    prod[i + idx[TERM - 1]] = (double)classNum[i] / efectNum;
    //printf("class %d: %f\n", i + idx[TERM - 1], prod[i + idx[TERM - 1]]);
    p += prod[i + idx[TERM - 1]];
  }
  //printf("p = %f\n", p);

  // another term
  for(i = TERM - 1; i > 0; i--){
    head = idx[i];
    p = 0.0;
    for(j = 0; j < idx[i] - idx[i - 1]; j++){
      for(k = 0; k < CLASS; k++){
	prev[head + 1] = j + idx[i - 1] + 1;
	prod[j + idx[i - 1]] += prod[head++];
      }
      //printf("class %d: %f\n", j + idx[i - 1], prod[j + idx[i - 1]]);
      p += prod[j + idx[i - 1]];
    }
    //printf("p = %f\n", p);
  }

  //printf("hello!\n");
  //fflush(stdout);
  sprintf(output, "Class_%d_Term_%d_data.dat", CLASS, TERM);
  //sprintf(output, "Class_%d_Term_%d_data.dat", 100, 100);

  mydata = FILEOPEN(output, "w");

  // set T
  fprintf(mydata, "set T :=");
  for(i = 0; i <= TERM; i++) { fprintf(mydata, " %d", i); }
  fprintf(mydata, ";\n");

  // set S
  fprintf(mydata, "set S :=");
  for(i = 0; i <= idx[TERM]; i++) { fprintf(mydata, " %d", i); }
  fprintf(mydata, ";\n");

  // Tnum
  fprintf(mydata, "param Tnum := %d;\n", TERM);

  // c
  fprintf(mydata, "param c :");
  for(i = 0; i <= idx[TERM]; i++) { fprintf(mydata, " %d", i); }
  fprintf(mydata, " :=\n");
  fprintf(mydata, "0    1");
  for(i = 1; i <= idx[TERM]; i++){ fprintf(mydata, " 0"); }
  fprintf(mydata, "\n");
  for(i = 1; i <= TERM; i++){
    fprintf(mydata, "%d   ", i);
    for(j = 0; j <= idx[TERM]; j++){
      fprintf(mydata, " %d", (idx[i - 1] < j && j <= idx[i]) ? 1 : 0);
    }
    fprintf(mydata, "\n");
  }
  fprintf(mydata, ";\n");

  // ps
  fprintf(mydata, "param ps := \n");
  for(i = 0; i <= idx[TERM]; i++) { fprintf(mydata, "%d %d\n", i, prev[i]); }
  fprintf(mydata, ";\n");

  // prod
  fprintf(mydata, "param prod: ");
  for(i = 0; i <= idx[TERM]; i++) { fprintf(mydata, " %d", i); }
  fprintf(mydata, " :=\n");
  fprintf(mydata, "0    1");
  for(i = 1; i <= idx[TERM]; i++){ fprintf(mydata, " 0"); }
  fprintf(mydata, "\n");
  for(i = 1; i <= TERM; i++){
    fprintf(mydata, "%d   ", i);
    for(j = 0; j <= idx[TERM]; j++){
      fprintf(mydata, " %f", (idx[i - 1] < j && j <= idx[i]) ? prod[j - 1] : 0);
    }
    fprintf(mydata, "\n");
  }
  fprintf(mydata, ";\n");
  
  // v
  fprintf(mydata, "param v: ");
  for(i = 0; i <= idx[TERM]; i++) { fprintf(mydata, " %d", i); }
  fprintf(mydata, " :=\n");
  fprintf(mydata, "0    0");
  for(i = 1; i <= idx[TERM]; i++){ fprintf(mydata, " 0"); }
  fprintf(mydata, "\n");
  for(i = 1; i <= TERM; i++){
    fprintf(mydata, "%d   ", i);
    for(j = 0; j <= idx[TERM]; j++){
      fprintf(mydata, " %f", (idx[i - 1] < j && j <= idx[i]) ? getPowerVal(j % CLASS, CLASS, windClass) : 0);
    }
    fprintf(mydata, "\n");
  }
  fprintf(mydata, ";\n");

  fclose(mydata);

  // another file: M1, M2, price, C, cpd, allow_prod_1, _2, allow_vl, _vu
  
  return 0;
}
