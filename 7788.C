#include <string.h>
#include <stdio.h>

void main()
{
	char letter[14]={'\0'};
	char letter1[14]={'\0'};
		strcpy(letter1,"letter\\\a.bmp");
	strcpy(letter,"letter\\\\\\.bmp");
	letter[8]='a';
	printf("%s\n",letter);
	printf("%s\n","\\.");
    printf("%s\n",letter1);

}