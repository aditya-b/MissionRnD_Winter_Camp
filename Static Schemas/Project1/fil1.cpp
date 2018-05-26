#include<stdio.h>
#include<stdlib.h>
char* getavg(int m1, int m2, int m3, int m4)
{
	char * arr = (char*)malloc(sizeof(char*));
	sprintf(arr, "%d", (m1 + m2 + m3 + m4) / 4);
	return arr;
}
char* getcgpa(int m1, int m2, int m3, int m4)
{
	int a[4];
	float cgpa=0;
	int i;
	char *cg = (char*)malloc(sizeof(char*));
	a[0] = m1; a[1] = m2; a[2] = m3; a[3] = m4;
	for (i = 0; i < 4; i++)
	{
		if (a[i] <= 100 && a[i] >= 90)
			cgpa += 4;
		else if (a[i] >= 85 && a[i] <= 89)
			cgpa += 3.76;
		else if (a[i] >= 80 && a[i] <= 84)
			cgpa += 3.5;
		else if (a[i] >= 75 && a[i] <= 79)
			cgpa += 3.33;
		else if (a[i] >= 70 && a[i] <= 74)
			cgpa += 3;
		else if (a[i] >= 65 && a[i] <= 69)
			cgpa += 2.76;
		else if (a[i] >= 60 && a[i] <= 64)
			cgpa += 3.5;
		else
			cgpa += 3;
	}
	sprintf(cg, "%.2f", cgpa / 4);
	return cg;
}
int matn()
{
	FILE *fp,*fp2,*fp3;
	char ch;
	fp = fopen("D:/Winter Camp/studentmarkslist.csv", "r");
	fp2 = fopen("D:/Winter Camp/studentsmarklistwithavg.csv", "w");
	fp3 = fopen("D:/Winter Camp/listjoin.csv", "w");
	if (fp != NULL)
	{
		int flag = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0, d, avg;
		do
		{
			ch = fgetc(fp);
			while (ch != ','&&ch!=EOF)
			{
				if(ch!='\n')
					fputc(ch,fp2);
				d = ch;
				if (d > 47 && d < 58)
				{
					switch (flag % 6)
					{
					case 2:  m1 = m1 * 10 + (d - 48); break;
					case 3: m2 = m2 * 10 + (d - 48); break;
					case 4: m3 = m3 * 10 + (d - 48); break;
					case 5: m4 = m4 * 10 + (d - 48); break;
					}
				}
				if (ch == '\n'||ch==EOF)
				{
					if (flag == 5)
						fputs(",Avg,CGPA\n", fp2);
					else
					{
						fputc(',', fp2);
						fputs(getavg(m1,m2,m3,m4), fp2);
						fputc(',', fp2);
						fputs(getcgpa(m1, m2, m3, m4), fp2);
						fputc('\n', fp2);
					}
					m1 = 0; m2 = 0; m3 = 0; m4 = 0;
					flag++;
				}
				ch = fgetc(fp);
			}
			flag++;
			if (ch != '\n'&&ch != EOF)
				fputc(',',fp2);

		} while (ch != EOF);
		fputc(',', fp2);
		fputs(getavg(m1,m2,m3,m4), fp2);
		fputc(',', fp2);
		fputs(getcgpa(m1, m2, m3, m4), fp2);
		fclose(fp);
		fclose(fp2);
	}
	return 1;
}
