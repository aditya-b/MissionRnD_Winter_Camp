#include<stdio.h>
#include<string.h>
#include<malloc.h>
/*
void query(struct file1 *files1, char *required, int *maxrows, char *condition)
{
	char op[4], val[10];
	int flag[8], i = 0, x;
	x = 0;
	for (i = 0; i < 8; i++)
		flag[i] = 0;
	while ((condition[i] > 64 && condition[i] < 91) || (condition[i]>96 && condition[i] < 123) || (condition[i] >= 48 && condition[i] <= 57))
		i++;
	printf("%c", condition[i]);
	while (condition[i] < 48 || condition[i]>57)
		op[x++] = condition[i++];
	op[x] = '\0';
	x = 0;
	while (condition[i] != '\0')
		val[x++] = condition[i++];
	val[x] = '\0';
	if (!strcmp(required, "*"))
	{
		printf("RollNo\tName\t\tM1\tM2\tM3\tM4\tAvg\tCGPA\n");
		if (condition == NULL)
		{
			for (i = 0; i < *maxrows; i++)
				printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
		}
		else
		{
			if (strstr(condition, "avg"))
			{
				if (!strcmp(op, "="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].avg) == strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].avg) <= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].avg) < strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].avg) > strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].avg) >= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else
				{
					printf("Invalid Operator found!\n");
					return;
				}
			}
			else if (strstr(condition, "rollno"))
			{
				if (!strcmp(op, "="))
				{
					for (i = 0; i < *maxrows; i++)
					{
						if (i + 1 == strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
					}
				}
				else if (!strcmp(op, "<="))
				{
					for (i = 0; i < *maxrows; i++)
					{
						if (i + 1 <= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
					}
				}
				else if (!strcmp(op, "<"))
				{
					for (i = 0; i < *maxrows; i++)
					{
						if (i + 1 < strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
					}
				}
				else if (!strcmp(op, ">"))
				{
					for (i = 0; i < *maxrows; i++)
					{
						if (i + 1 > strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
					}
				}
				else if (!strcmp(op, ">="))
				{
					for (i = 0; i < *maxrows; i++)
					{
						if (i + 1 >= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
					}
				}
				else
				{
					printf("Invalid Operator found!\n");
					return;
				}
			}
			else if (strstr(condition, "m1"))
			{
				if (!strcmp(op, "="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m1) == strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m1) <= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m1) < strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m1) > strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m1) >= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else
				{
					printf("Invalid Operator found!\n");
					return;
				}
			}
			else if (strstr(condition, "m2"))
			{
				if (!strcmp(op, "="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m2) == strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m2) <= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m2) < strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m2) > strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m2) >= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else
				{
					printf("Invalid Operator found!\n");
					return;
				}
			}
			else if (strstr(condition, "m3"))
			{
				if (!strcmp(op, "="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m3) == strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m3) <= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m3) < strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m3) > strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m3) >= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else
				{
					printf("Invalid Operator found!\n");
					return;
				}
			}
			else if (strstr(condition, "m4"))
			{
				if (!strcmp(op, "="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m4) == strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m4) <= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m4) < strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m4) > strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strtonum(files1[i].m4) >= strtonum(val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else
				{
					printf("Invalid Operator found!\n");
					return;
				}
			}
			else if (strstr(condition, "cgpa"))
			{
				if (!strcmp(op, "="))
				{
					for (i = 0; i < *maxrows; i++)
						if (!strcmp(files1[i].cgpa, val))
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strcmp(files1[i].cgpa, val) <= 0)
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, "<"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strcmp(files1[i].cgpa, val) < 0)
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">"))
				{
					for (i = 0; i < *maxrows; i++)
						if (strcmp(files1[i].cgpa, val) > 0)
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else if (!strcmp(op, ">="))
				{
					for (i = 0; i < *maxrows; i++)
						if (strcmp(files1[i].cgpa, val) >= 0)
							printf("%d\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n", i + 1, (files1[i].name), files1[i].m1, files1[i].m2, files1[i].m3, files1[i].m4, files1[i].avg, files1[i].cgpa);
				}
				else
				{
					printf("Invalid Operator found!\n");
					return;
				}
			}
		}
	}
	else
	{
		int j;
		x = 0;
		i = 0;
		for (i = 0; i < 8; i++)
			flag[i] = 0;
		i = 0;
		char reqd[15];
		if (strstr(required, "rollno"))
		{
			printf("rollno\t");
			flag[0] = 1;
		}
		if (strstr(required, "name"))
		{
			printf("name\t");
			flag[1] = 1;
		}
		if (strstr(required, "m1"))
		{
			printf("m1\t");
			flag[2] = 1;
		}
		if (strstr(required, "m2"))
		{
			printf("m2\t");
			flag[3] = 1;
		}
		if (strstr(required, "m3"))
		{
			printf("m3\t");
			flag[4] = 1;
		}
		if (strstr(required, "m4"))
		{
			printf("m4\t");
			flag[5] = 1;
		}
		if (strstr(required, "avg"))
		{
			printf("avg\t");
			flag[6] = 1;
		}
		if (strstr(required, "cgpa"))
		{
			printf("cgpa\t");
			flag[7] = 1;
		}
		printf("\n");

		i = 0;
		x = 0;
		printf("%s %s", op, val);
		while (x < *maxrows)
		{
			if (flag[0])
				printf("%d\t", x + 1);
			if (flag[1])
				printf("%s\t", files1[x].name);
			if (flag[2])
				printf("%s\t", files1[x].m1);
			if (flag[3])
				printf("%s\t", files1[x].m2);
			if (flag[4])
				printf("%s\t", files1[x].m3);
			if (flag[5])
				printf("%s\t", files1[x].m4);
			if (flag[6])
				printf("%s\t", files1[x].avg);
			if (flag[7])
				printf("%s\t", files1[x].cgpa);
			printf("\n");
			x++;
		}
	}
	printf("Query Successful!\n");
	}*/