/*DB ENGINE for pre-defined schemas:
Schema-1: RollNo,Name,M1,M2,M3,M4,Avg,CGPA
Schema-2: RollNo,Phone,Address,City,Pincode
Schema-3: Join of above two schemas

Query Formats:
import filename.csv s1 -- imports file for schema 1 (replace 1 with required schema number)
flush filename.csv s2 -- flushes into file for schema 2
select is of user's choice

NOTE: Column names are case-sensitive
*/


#include<stdio.h>
#include<malloc.h>
#include<string.h>
/*Structure for SCHEMA-1*/
struct file1
{
	char name[20];
	char m1[4];
	char m2[4];
	char m3[4];
	char m4[4];
	char avg[4];
	char cgpa[6];
};
/*Structure for SCHEMA-2*/
struct file2
{
	char phone[20];
	char address[100];
	char city[20];
	char pincode[10];
};
/*Structure for SCHEMA-3*/
struct joint
{
	char name[20];
	char m1[4];
	char m2[4];
	char m3[4];
	char m4[4];
	char avg[4];
	char cgpa[6];
	char phone[20];
	char address[100];
	char city[20];
	char pincode[10];
};
/*Function to convert string to number*/
int strtonum(char *str)
{
	int n = 0, i = 0;
	while (str[i] != '\0')
		n = n * 10 + (str[i++] - 48);
	return n;
}
/*Function to import Schema-1*/
struct file1* import1(struct file1 *files1,char *filename,int *maxrows1)
{
	int n = 0, i = 0, j = 0, x = 0, flag = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0, avg = 0, cgpa = 0, d, r=0,max;
	FILE *fp;
	char roll[4], name[20];
	struct file1 *f;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Invalid File Name!");
		return files1;
	}
	char *line = (char*)malloc(sizeof(char) * 100);
	while (fgets(line, 100, fp))
		n++;
	n--;
	if (files1 != NULL)
		max = n + *maxrows1;
	else
		max = n;
	fseek(fp, 0, SEEK_SET);
	if (files1 == NULL)
		f = (struct file1*)malloc(sizeof(struct file1)*(n));
	else
	{
		files1 = (struct file1*)realloc(files1, max*sizeof(struct file1));
		f = files1;
	}
	fgets(line, 100, fp);
	if (files1!=NULL)
	i = 0;
	while (i+*maxrows1 < max)
	{
		fgets(line, 100, fp);
		x = 0;
		while (line[x] != ',')
			roll[x] = line[x++];
		flag++;
		roll[x] = '\0';
		x++;
		r = strtonum(roll) - 1;
		while (line[x] != '\n'&&line[x] != EOF)
		{
			j = 0;
			switch (flag % 8)
			{
			case 1:	while (line[x] != ',')
				f[r].name[j++] = line[x++];
				f[r].name[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 2:while (line[x] != ',')
				f[r].m1[j++] = line[x++];
				f[r].m1[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 3:while (line[x] != ',')
				f[r].m2[j++] = line[x++];
				f[r].m2[j] = '\0';
				flag++;
				x++;
				j = 0;
				break;
			case 4:while (line[x] != ',')
				f[r].m3[j++] = line[x++];
				f[r].m3[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 5:while (line[x] != ',')
				f[r].m4[j++] = line[x++];
				f[r].m4[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 6:while (line[x] != ',')
				f[r].avg[j++] = line[x++];
				f[r].avg[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 7:while (line[x] != ','&&line[x] != '\n')
				f[r].cgpa[j++] = line[x++];
				f[r].cgpa[j] = '\0';
				j = 0;
				flag++;
				break;
			}
		}
		//printf("%d %s %s %s %s %s %s %s\n", *maxrows1, f[r].name, f[r].m1, f[r].m2, f[r].m3, f[r].m4, f[r].avg, f[r].cgpa);
		i++;
	}
	*maxrows1 = max;
	return f;
}
/*Function to import Schema-2*/
struct file2* import2(struct file2 *files2,char *filename,int *maxrows2)
{
	int n = 0, i = 0, j = 0, x = 0, flag = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0, avg = 0, cgpa = 0, d, r,max; 
	FILE *fp2;
	struct file2 *students;
	fp2 = fopen(filename, "r");
	if (fp2 == NULL)
	{
		printf("Invalid File Name!");
		return files2;
	}
	i = 0;
	char roll[4];
	char *line = (char*)malloc(sizeof(char) * 100);
	while (fgets(line, 100, fp2))
		n++;
	n--;
	if (files2 != NULL)
		max = n + *maxrows2;
	else
		max = n;
	fseek(fp2, 0, SEEK_SET);
	if (files2 == NULL)
		students = (struct file2*)malloc(sizeof(struct file2)*(n));
	else
	{
		files2 = (struct file2*)realloc(files2, max*sizeof(struct file2));
		students = files2;
	}
	fgets(line, 100, fp2);
	j = 0;
	x = 0;
	while (i+*maxrows2 < max)
	{
		x = 0;
		fgets(line, 100, fp2);
		//printf("%s", line);
		while (line[x] != ',')
			roll[x] = line[x++];
		roll[x] = '\0';
		flag++;
		x++;
		int r = strtonum(roll) - 1;
		//students[r].num = max;i
		while (line[x] != '\n' && line[x] != EOF)
		{
			j = 0;
			switch (flag % 5)
			{
			case 1:	while (line[x] != ',')
				students[r].phone[j++] = line[x++];
				students[r].phone[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 2:while (line[x] != ',')
				students[r].address[j++] = line[x++];
				students[r].address[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 3:while (line[x] != ',')
				students[r].city[j++] = line[x++];
				students[r].city[j] = '\0';
				flag++;
				x++;
				j = 0;
				break;
			case 4:while (line[x] != ','&&line[x] != '\n')
				students[r].pincode[j++] = line[x++];
				students[r].pincode[j] = '\0';
				j = 0;
				flag++;
				break;
			}
		}
		i++;
		//printf("%d %s %s %s %s\n", students[r].num,students[r].phone, students[r].address, students[r].city, students[r].pincode);
	}
	*maxrows2 = max;
	return students;
}
/*Function to import Schema-3*/
struct joint* join(struct file1 *files1,struct file2 *files2,int *maxrows1,int *maxrows2,int *maxrows3)
{
	struct joint *students = NULL;
	if (files1 == NULL || files2 == NULL)
	{
		printf("Both schemas not imported.\n");
		return students;
	}
	int n = *maxrows1 < *maxrows2 ? *maxrows2 : *maxrows1;
	*maxrows3 = n;
	students = (struct joint*)malloc(sizeof(struct joint)*n);
	int i = 0;
	while (i < n)
	{
		strcpy(students[i].name, files1[i].name);
		strcpy(students[i].m1, files1[i].m1);
		strcpy(students[i].m2, files1[i].m2);
		strcpy(students[i].m3, files1[i].m3);
		strcpy(students[i].m4, files1[i].m4);
		strcpy(students[i].avg, files1[i].avg);
		strcpy(students[i].cgpa, files1[i].cgpa);
		strcpy(students[i].phone, files2[i].phone);
		strcpy(students[i].address, files2[i].address);
		strcpy(students[i].city, files2[i].city);
		strcpy(students[i].pincode, files2[i].pincode);
		//printf("%d %s %s %s %s %s %s %s %s %s %s %s\n", i+1, students[i].name, students[i].m1, students[i].m2, students[i].m3, students[i].m4, students[i].avg, students[i].cgpa, students[i].phone, students[i].address, students[i].city, students[i].pincode);
		i++;
	}
	return students;
}
/*Function to Flush Schema-3 File*/
void flushfilejoint(struct joint *students, FILE *fp3,int *maxrows)
{
	int n, j;
	n = *maxrows;
	char roll[4];
	fputs("RollNo,Name,M1,M2,M3,M4,Avg,CGPA,Phone,Address,City,Pincode\n",fp3);
	for (j = 0; j < n;j++)
	{
		sprintf(roll, "%d", j + 1);
		fputs(roll, fp3);
		fputc(',', fp3);
		fputs(students[j].name, fp3);
		fputc(',', fp3);
		fputs(students[j].m1, fp3);
		fputc(',', fp3);
		fputs(students[j].m2, fp3);
		fputc(',', fp3);
		fputs(students[j].m3, fp3);
		fputc(',', fp3);
		fputs(students[j].m4, fp3);
		fputc(',', fp3);
		fputs(students[j].avg, fp3);
		fputc(',', fp3);
		fputs(students[j].cgpa, fp3);
		fputc(',', fp3);
		fputs(students[j].phone, fp3);
		fputc(',', fp3);
		fputs(students[j].address, fp3);
		fputc(',', fp3);
		fputs(students[j].city, fp3);
		fputc(',', fp3);
		fputs(students[j].pincode, fp3);
		fputc('\n', fp3);
	}
}
/*Function to flush Schema-1 File*/
void flushfile1(struct file1 *students, FILE *fp3, int *maxrows)
{
	int n, j;
	n = *maxrows;
	char roll[4];
	fputs("RollNo,Name,M1,M2,M3,M4,Avg,CGPA\n",fp3);
	for (j = 0; j <n; j++)
	{
		sprintf(roll, "%d", j + 1);
		fputs(roll, fp3);
		fputc(',', fp3);
		fputs(students[j].name, fp3);
		fputc(',', fp3);
		fputs(students[j].m1, fp3);
		fputc(',', fp3);
		fputs(students[j].m2, fp3);
		fputc(',', fp3);
		fputs(students[j].m3, fp3);
		fputc(',', fp3);
		fputs(students[j].m4, fp3);
		fputc(',', fp3);
		fputs(students[j].avg, fp3);
		fputc(',', fp3);
		fputs(students[j].cgpa, fp3);
		fputc('\n', fp3);
	}
}
/*Function to flush Schema-2 File*/
void flushfile2(struct file2 *students, FILE *fp3, int *maxrows)
{
	int n, j;
	n = *maxrows;
	char roll[4];
	fputs("RollNo,Phone,Address,City,Pincode\n",fp3);
	for (j = 0; j < n; j++)
	{
		sprintf(roll, "%d", j + 1);
		fputs(roll, fp3);
		fputc(',', fp3);
		fputs(students[j].phone, fp3);
		fputc(',', fp3);
		fputs(students[j].address, fp3);
		fputc(',', fp3);
		fputs(students[j].city, fp3);
		fputc(',', fp3);
		fputs(students[j].pincode, fp3);
		fputc('\n', fp3);
	}
}
/*Function to print line of Schema-1*/
void printline(int *flag, struct file1 *files1,int x)
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
}
/*Function to query Schema-1*/
void query1(struct file1 *files1, char *required, int *maxrows, char *condition)
{
	char op[4], val[10],name[20];
	int flag[8], i = 0, x;
	x = 0;
	for (i = 0; i < 8; i++)
		flag[i] = 0;
	if (strstr(condition, "contains")||strstr(condition,"matches"))
	{
		i = 0; x = 0;
		while (condition[i] != '"')
			i++;
		i++;
		while (condition[i] != '"')
			name[x++] = condition[i++];
		name[x] = '\0';
		//printf("%s", name);
	}
	if (condition[0]!='\0'&&!strstr(condition,"contains")&&!strstr(condition,"matches"))
	{
		i = 0;
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
	}
	if (!strcmp(required, "*"))
	{
		printf("RollNo\tName\t\tM1\tM2\tM3\tM4\tAvg\tCGPA\n");
		for (i = 0; i < 8; i++)
			flag[i] = 1;
	}
	else
	{
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
	}
	if (condition[0]=='\0')
	{
		for (x = 0; x < *maxrows; x++)
			printline(flag, files1, x);
		printf("\n");
	}
	else
	{
		if (strstr(condition, "avg"))
		{
			if (!strcmp(op, "="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].avg) == strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].avg) <= strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].avg) < strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].avg) > strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].avg) >= strtonum(val))
						printline(flag, files1, i);
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
						printline(flag, files1, i);
				}
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
				{
					if (i + 1 <= strtonum(val))
						printline(flag, files1, i);
				}
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
				{
					if (i + 1 < strtonum(val))
						printline(flag, files1, i);
				}
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
				{
					if (i + 1 > strtonum(val))
						printline(flag, files1, i);
				}
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
				{
					if (i + 1 >= strtonum(val))
						printline(flag, files1, i);
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
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m1) <= strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m1) < strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m1) > strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m1) >= strtonum(val))
						printline(flag, files1, i);
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
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m2) <= strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m2) < strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m2) > strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m2) >= strtonum(val))
						printline(flag, files1, i);
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
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m3) <= strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m3) < strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m3) > strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m3) >= strtonum(val))
						printline(flag, files1, i);
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
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m4) <= strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m4) < strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m4) > strtonum(val))
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m4) >= strtonum(val))
						printline(flag, files1, i);
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
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strcmp(files1[i].cgpa, val) <= 0)
						printline(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strcmp(files1[i].cgpa, val) < 0)
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strcmp(files1[i].cgpa, val) > 0)
						printline(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strcmp(files1[i].cgpa, val) >= 0)
						printline(flag, files1, i);
			}
			else
			{
				printf("Invalid Operator found!\n");
				return;
			}
		}
		else if (strstr(condition, "contains"))
		{
			for (i = 0; i < *maxrows; i++)
				if (strstr(files1[i].name, name))
					printline(flag, files1, i);
		}
		else if (strstr(condition, "matches"))
		{
			for (i = 0; i < *maxrows; i++)
					if (!strcmp(files1[i].name, name))
						printline(flag, files1, i);
		}
		printf("Query Successful!\n");
	}
}
/*Function to print line of Schema-2*/
void printline2(int *flag, struct file2 *files1, int x)
{
	if (flag[0])
		printf("%d\t", x + 1);
	if (flag[1])
		printf("%s\t", files1[x].phone);
	if (flag[2])
		printf("%s\t", files1[x].address);
	if (flag[3])
		printf("%s\t", files1[x].city);
	if (flag[4])
		printf("%s\t", files1[x].pincode);
	printf("\n");
}
/*Function to query Schema-2*/
void query2(struct file2 *files2, char *required,char *condition,int *maxrows)
{
	int flag[5], i = 0, x;
	char name[20];
	x = 0;
	for (i = 0; i < 5; i++)
		flag[i] = 0;
	if (strstr(condition, "contains") || strstr(condition, "matches"))
	{
		i = 0; x = 0;
		while (condition[i] != '"')
			i++;
		i++;
		while (condition[i] != '"')
			name[x++] = condition[i++];
		name[x] = '\0';
	}
	if (!strcmp(required, "*"))
	{
		printf("RollNo\tPhone\tAddress\t\t\tCity\tPincode\n");
		for (i = 0; i < 5; i++)
			flag[i] = 1;
	}
	else
	{
		if (strstr(required, "rollno"))
		{
			printf("RollNo\t");
			flag[0] = 1;
		}
		if (strstr(required, "phone"))
		{
			printf("Phone\t");
			flag[1] = 1;
		}
		if (strstr(required, "address"))
		{
			printf("Address\t");
			flag[2] = 1;
		}
		if (strstr(required, "city"))
		{
			printf("City\t");
			flag[3] = 1;
		}
		if (strstr(required, "pincode"))
		{
			printf("Pincode\n");
			flag[4] = 1;
		}
	}
	if (condition[0] == '\0')
	{
		for (x = 0; x < *maxrows; x++)
			printline2(flag, files2, x);
		printf("\n");
	}
	else
	{
		 if (strstr(condition, "contains"))
		 {
			 if (strstr(condition, "phone"))
			 {
				 for (i = 0; i < *maxrows; i++)
					 if (strstr(files2[i].phone, name))
						 printline2(flag, files2, i);
			 }
			 else if (strstr(condition, "address"))
			 {
				 for (i = 0; i < *maxrows; i++)
					 if (strstr(files2[i].address, name))
						 printline2(flag, files2, i);
			 }
			 else if (strstr(condition, "city"))
			 {
				 for (i = 0; i < *maxrows; i++)
					 if (strstr(files2[i].city, name))
						 printline2(flag, files2, i);
			 }
			 else if (strstr(condition, "pincode"))
			 {
				 for (i = 0; i < *maxrows; i++)
					 if (strstr(files2[i].pincode, name))
						 printline2(flag, files2, i);
			 }
			 else
				 printf("Invalid Column\n");
		 }
		 else if (strstr(condition, "matches"))
		 {
			 if (strstr(condition, "phone"))
			 {
				 for (i = 0; i < *maxrows; i++)
					 if (!strcmp(files2[i].phone, name))
						 printline2(flag, files2, i);
			 }
			 else if (strstr(condition, "address"))
			 {
				 for (i = 0; i < *maxrows; i++)
					 if (!strcmp(files2[i].address, name))
						 printline2(flag, files2, i);
			 }
			 else if (strstr(condition, "city"))
			 {
				 for (i = 0; i < *maxrows; i++)
					 if (!strcmp(files2[i].city, name))
						 printline2(flag, files2, i);
			 }
			 else if (strstr(condition, "pincode"))
			 {
				 for (i = 0; i < *maxrows; i++)
					 if (!strcmp(files2[i].pincode, name))
						 printline2(flag, files2, i);
			 }
			 else
				 printf("Invalid Column\n");
		 }
	}
}
/*Function to print line of Schema-3*/
void printline3(int *flag, struct joint *files1, int x)
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
	if (flag[8])
		printf("%s\t", files1[x].phone);
	if (flag[9])
		printf("%s\t", files1[x].address);
	if (flag[10])
		printf("%s\t", files1[x].city);
	if (flag[11])
		printf("%s\t", files1[x].pincode);
	printf("\n");
}
/*Function to query Schema-3*/
void query3(struct joint *files1, char *required,char *condition,int *maxrows)
{
	char op[4], val[10], name[20];
	int flag[12], i = 0, x;
	x = 0;
	for (i = 0; i < 12; i++)
		flag[i] = 0;
	if (strstr(condition, "contains") || strstr(condition, "matches"))
	{
		i = 0; x = 0;
		while (condition[i] != '"')
			i++;
		i++;
		while (condition[i] != '"')
			name[x++] = condition[i++];
		name[x] = '\0';
		//printf("%s", name);
	}
	if (condition[0] != '\0'&&!strstr(condition, "contains") && !strstr(condition, "matches"))
	{
		i = 0;
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
	}
	if (!strcmp(required, "*"))
	{
		printf("RollNo\tName\t\tM1\tM2\tM3\tM4\tAvg\tCGPA\tPhone\t\tAddress\t\t\t\tCity\tPincode\n");
		for (i = 0; i < 12; i++)
			flag[i] = 1;
	}
	else
	{
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
		if (strstr(required, "phone"))
		{
			printf("Phone\t");
			flag[8] = 1;
		}
		if (strstr(required, "address"))
		{
			printf("Address\t");
			flag[9] = 1;
		}
		if (strstr(required, "city"))
		{
			printf("City\t");
			flag[10] = 1;
		}
		if (strstr(required, "pincode"))
		{
			printf("Pincode\n");
			flag[11] = 1;
		}
	}
	if (condition[0] == '\0')
	{
		for (x = 0; x < *maxrows; x++)
			printline3(flag, files1, x);
		printf("\n");
	}
	else
	{
		if (strstr(condition, "avg"))
		{
			if (!strcmp(op, "="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].avg) == strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].avg) <= strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].avg) < strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].avg) > strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].avg) >= strtonum(val))
						printline3(flag, files1, i);
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
						printline3(flag, files1, i);
				}
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
				{
					if (i + 1 <= strtonum(val))
						printline3(flag, files1, i);
				}
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
				{
					if (i + 1 < strtonum(val))
						printline3(flag, files1, i);
				}
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
				{
					if (i + 1 > strtonum(val))
						printline3(flag, files1, i);
				}
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
				{
					if (i + 1 >= strtonum(val))
						printline3(flag, files1, i);
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
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m1) <= strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m1) < strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m1) > strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m1) >= strtonum(val))
						printline3(flag, files1, i);
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
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m2) <= strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m2) < strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m2) > strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m2) >= strtonum(val))
						printline3(flag, files1, i);
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
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m3) <= strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m3) < strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m3) > strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m3) >= strtonum(val))
						printline3(flag, files1, i);
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
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m4) <= strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m4) < strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m4) > strtonum(val))
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strtonum(files1[i].m4) >= strtonum(val))
						printline3(flag, files1, i);
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
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strcmp(files1[i].cgpa, val) <= 0)
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, "<"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strcmp(files1[i].cgpa, val) < 0)
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strcmp(files1[i].cgpa, val) > 0)
						printline3(flag, files1, i);
			}
			else if (!strcmp(op, ">="))
			{
				for (i = 0; i < *maxrows; i++)
					if (strcmp(files1[i].cgpa, val) >= 0)
						printline3(flag, files1, i);
			}
			else
			{
				printf("Invalid Operator found!\n");
				return;
			}
		}
		else if (strstr(condition, "contains"))
		{
			if (strstr(condition, "name"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strstr(files1[i].name, name))
						printline3(flag, files1, i);
			}
			else if (strstr(condition, "phone"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strstr(files1[i].phone, name))
						printline3(flag, files1, i);
			}
			else if (strstr(condition, "address"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strstr(files1[i].address, name))
						printline3(flag, files1, i);
			}
			else if (strstr(condition, "city"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strstr(files1[i].city, name))
						printline3(flag, files1, i);
			}
			else if (strstr(condition, "pincode"))
			{
				for (i = 0; i < *maxrows; i++)
					if (strstr(files1[i].pincode, name))
						printline3(flag, files1, i);
			}
			else
				printf("Invalid Column\n");
		}
		else if (strstr(condition, "matches"))
		{
			if (strstr(condition, "name"))
			{
				for (i = 0; i < *maxrows; i++)
					if (!strcmp(files1[i].name, name))
						printline3(flag, files1, i);
			}
			else if (strstr(condition, "phone"))
			{
				for (i = 0; i < *maxrows; i++)
					if (!strcmp(files1[i].phone, name))
						printline3(flag, files1, i);
			}
			else if (strstr(condition, "address"))
			{
				for (i = 0; i < *maxrows; i++)
					if (!strcmp(files1[i].address, name))
						printline3(flag, files1, i);
			}
			else if (strstr(condition, "city"))
			{
				for (i = 0; i < *maxrows; i++)
					if (!strcmp(files1[i].city, name))
						printline3(flag, files1, i);
			}
			else if (strstr(condition, "pincode"))
			{
				for (i = 0; i < *maxrows; i++)
					if (!strcmp(files1[i].pincode, name))
						printline3(flag, files1, i);
			}
			else
				printf("Invalid Column\n");
		}
		printf("Query Successful!\n");
	}
}
/*Main Function for Console*/
int main()
{
	FILE *fp;
	char cmd[150], ch, filename[50], command[15],required[40],condition[50];
	int schema, x, num1 = 0, num2 = 0, num = 0;
	struct file1 *files1=NULL;
	struct file2 *files2=NULL;
	struct joint *files=NULL;
	int maxrows1 = 0, maxrows2 = 0, maxrows3 = 0;
	while (1)
	{
		printf("\nDBENGINE>");
		gets(cmd);
		for (int i = 0; i < strlen(cmd);)
		{
			x = 0;
			while (cmd[i] != ' ')
				command[x++] = cmd[i++];
			command[x] = '\0';
			i++;
			if (!strcmp(command, "import"))
			{
				x = 0;
				while (cmd[i] != ' ')
					filename[x++] = cmd[i++];
				filename[x] = '\0';
				//printf("%s", filename);
				i = i + 2;
				schema = cmd[i] - 48;
				//printf("%d", schema);
				switch (schema)
				{
				case 1:files1 = import1(files1,filename,&maxrows1); printf("Import Successful\n"); break;
				case 2:files2 = import2(files2,filename,&maxrows2); printf("Import Successful\n", num1); break;
				default:printf("Invalid Schema\n");
				}
			}
			else if (!strcmp(command, "exit"))
				return 1;
			else if (!strcmp(command, "join"))
			{
				files = join(files1,files2,&maxrows1,&maxrows2,&maxrows3);
				printf("Join Sucessful!\n", num);
			}
			else if (!strcmp(command, "flush"))
			{
				i++;
				int fno = cmd[i] - 48;
				printf("Enter Desired FileName::");
				filename[0] = '\0';
				gets(filename);
				fp = fopen(filename, "w");
				switch (fno)
				{
				case 1:flushfile1(files1, fp, &maxrows1); break;
				case 2:flushfile2(files2, fp, &maxrows2); break;
				case 3:flushfilejoint(files, fp, &maxrows3); break;
				}
				printf("File Flushed Successfully!\n");
			}
			else if (!strcmp(command, "select"))
			{
				
				x = 0;
				while (cmd[i] != ' ')
					required[x++] = cmd[i++];
				required[x] = '\0';
				i += 7;
				int s = cmd[i++] - 48;
				x = 0;
				condition[0] = '\0';
				if (cmd[i] != '\0')
				{
					i += 7;
					while (i < strlen(cmd) && cmd[i] != '\0')
						condition[x++] = cmd[i++];
					condition[x] = '\0';
				}
				if (cmd[i] == '\0')
				{
					switch (s)
					{
					case 1:query1(files1, required,&maxrows1,condition); break;
					case 2:query2(files2, required,condition,&maxrows2); break;
					case 3:query3(files, required,condition,&maxrows3); break;
					}
				}
			}
			else
				printf("Invalid Command.\n");
			break;
		}
	}
}