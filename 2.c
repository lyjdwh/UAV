#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include <dir.h>
void main ()
{	FILE *fmap;
	char path[40];
	strcat(path,"account\\");
	strcat(path,"lyjdwh");
	mkdir(path);
	strcat(path,"\\map.dat");
	fmap=fopen(path,"wt");
	printf("%s",path);
	fclose(fmap);
	
}