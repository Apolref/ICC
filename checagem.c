#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXNOME 128
#define MAXPOST 128

void checagem(){
  FILE *file1;
  if ((file1 = fopen("Ades", "r"))==0){
      file1 = fopen("Ades", "w");
      fprintf(file1, "1\nAdenilso\nAdes\n0\n0\n");
  }
  fclose(file1);

  FILE *file2;
  if ((file2 = fopen("Usuarios", "r"))==0){
      file2 = fopen("Usuarios", "w");
      fprintf(file2, "2\nUsuarios\nAdes\n");
  }
  fclose(file2);
}