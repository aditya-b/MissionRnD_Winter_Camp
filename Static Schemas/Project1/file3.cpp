#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student
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
int strtonums(char *str)
{
	int n = 0,i=0;
	while (str[i]!='\0')
		n = n * 10 + (str[i++]-48);
	return n;
}
int mn()
{
	int n = 0, i = 0, j = 0, x = 0, flag = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0, avg = 0, cgpa = 0, d,r;
	FILE *fp, *fp2, *fp3;
	char roll[4], name[20];
	fp = fopen("D:/Winter Camp/studentsmarklistwithavg.csv", "r");
	fp2 = fopen("D:/Winter Camp/studentinfolist.csv", "r");
	fp3 = fopen("D:/Winter Camp/MergewithStructs.csv", "w");
	char *line = (char*)malloc(sizeof(char) * 100);
	while (fgets(line, 100, fp))
		n++;
	n--;
	fseek(fp, 0, SEEK_SET);
	struct student *students = (struct student*)malloc(sizeof(struct student)*(n));
	fgets(line, 100, fp);
	while (i < n)
	{
		fgets(line, 100, fp);
		x = 0;
		printf("%s",line);
		while (line[x] != ',')
			roll[x] = line[x++];
		flag++;
		roll[x] = '\0';
		x++;
		r= strtonums(roll)-1;
		while (line[x] != '\n'&&line[x] != EOF)
		{
			j = 0;
			switch (flag % 8)
			{
			case 1:	while (line[x] != ',')
				students[r].name[j++] = line[x++];
				students[r].name[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 2:while (line[x] != ',')
				students[r].m1[j++] = line[x++];
				students[r].m1[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 3:while (line[x] != ',')
				students[r].m2[j++] = line[x++];
				students[r].m2[j] = '\0';
				flag++;
				x++;
				j = 0;
				break;
			case 4:while (line[x] != ',')
				students[r].m3[j++] = line[x++];
				students[r].m3[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 5:while (line[x] != ',')
				students[r].m4[j++] = line[x++];
				students[r].m4[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 6:while (line[x] != ',')
				students[r].avg[j++] = line[x++];
				students[r].avg[j] = '\0';
				j = 0;
				x++;
				flag++;
				break;
			case 7:while (line[x] != ','&&line[x] != '\n')
				students[r].cgpa[j++] = line[x++];
				students[r].cgpa[j] = '\0';
				j = 0;
				flag++;
				break;
			}
		}
		i++;
		printf("%s %s %s %s\n", students[r].m1, students[r].m2, students[r].m3, students[r].m4);
	}
	i = 0;
	fgets(line, 100, fp2);
	printf("%s", line);
	j = 0;
	x = 0;
	while (i < n)
	{
		x = 0;
		fgets(line, 100, fp2);
		printf("%s", line);
		while (line[x] != ',')
			roll[x] = line[x++];
		roll[x] = '\0';
		flag++;
		x++;
		int r = strtonums(roll)-1;
		students[r].address[0] = '\0';
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
	}
	fputs("RollNo,Name,M1,M2,M3,M4,Avg,CGPA,Phone,Address,City,Pincode\n", fp3);
	for (j = 0; j < n; j++)
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
