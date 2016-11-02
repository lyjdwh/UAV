#include <stdio.h>

void main()
{
  FILE *fp;
  //fp=fopen("account\\lyjdwh.dat","w");
 // fclose(fp);
  fp=fopen("account\\lyjdwh.dat","a+");
  fseek(fp,0,2);
 // fputs("food",fp);
 fprintf(fp,"%s\t","good");
}