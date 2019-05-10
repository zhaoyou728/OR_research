#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void readParameters(int c, char *v[], float* MARGIN, float* RATIO)
{
  int i;

  MARGIN[0] = 0.1;
  RATIO[0] = 0.3;

  for(i = 1; i < c; i++){
    if(strcmp(v[i],"-M") == 0)   {MARGIN[0] = atof(v[++i]);  continue;}
    if(strcmp(v[i],"-R") == 0)   {RATIO[0]  = atof(v[++i]);  continue;}
    i++;
  }

  return;
}

int main(int argc, char **argv)
{
  FILE *mydata;
  float MARGIN = 0.1, RATIO = 0.3;
  float ratedCapa = 31500.0;
  char output[256];

  readParameters(argc, argv, &MARGIN, &RATIO);

  sprintf(output, "Margin_%.2f_Ratio_%.2f.dat", MARGIN, RATIO);
  mydata = FILEOPEN(output, "w");

  // big-M
  fprintf(mydata, "param M1 := 1000000;\n");
  fprintf(mydata, "param M2 := 1000000;\n");

  // cpd, C
  fprintf(mydata, "param cpd := %.3f;\n", ratedCapa * RATIO);
  fprintf(mydata, "param C := %.3f;\n", ratedCapa * RATIO * 0.04);

  // STE
  fprintf(mydata, "param STE_init := %.3f;\n", ratedCapa * RATIO * 0.5);

  // margin
  fprintf(mydata, "param margin := %.3f;\n", MARGIN);

  fclose(mydata);
  
  return 0;
}
