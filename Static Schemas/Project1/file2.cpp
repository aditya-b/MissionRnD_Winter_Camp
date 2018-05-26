#include<stdio.h>
#include<string.h>
#include<malloc.h>
char* substring(char *string, int start)
{
	char *str = (char*)malloc(sizeof(char)*100);
	int x = 0;
	while (string[start]!='\n'&&string[start]!=EOF)
	{
		str[x++] = string[start++];
	}
	str[x++] = '\0';
	return str;
}
int man()
{
	FILE *fp1, *fp2, *fp3;
	int n = 0, x = 0;
	char roll1[4], roll2[4];
	roll1[0] = '\0';
	roll2[0] = '\0';
	char line1[120],line2[120];
	fp1 = fopen("D:/Winter Camp/studentsmarklistwithavg.csv", "r");
	fp2 = fopen("D:/Winter Camp/studentinfolist.csv", "r");
	fp3 = fopen("D:/Winter Camp/listjoin.csv", "w");
	fgets(line1, 120, fp1);
	line1[strlen(line1) - 1] = ',';
	fputs(line1, fp3);
	fgets(line2, 120, fp2);
	x = 0;
	while (line2[x++] != ',');
	fputs(substring(line2, x), fp3);
	fputc('\n', fp3);
	x = 0;
	while (n<200)
	{
		fgets(line1, 120, fp1);
		line1[strlen(line1) - 1] = '\0';
		//printf("(%s)\n", line1);
		fputs(line1, fp3);
		fgets(line2, 120, fp2);
		printf("%s", line1);
		while (line1[x]!=',')
			roll1[x] = line1[x++];
		roll1[x] = '\0'; 
		//printf("[%s %s]\n", roll1, roll2);
		while (strcmp(roll1, roll2)!=0)
		{
			x = 0;
			fgets(line2, 120, fp2);
			while (line2[x]!=',')
				roll2[x] = line2[x++];
			roll2[x] = '\0';
		}
		fputs(substring(line2,x),fp3);
		fseek(fp2, 0, SEEK_SET);
		x = 0;
		n++;
	}
}